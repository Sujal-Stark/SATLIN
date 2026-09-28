//
// Created by sujal-stark on 2/25/26.
//

#include "ItemRepository.h"

#include <iostream>
#include <QDebug>
#include <QStandardPaths>

#include "ToolKit.h"


#define SQLITE_USE 0

ItemRepository::ItemRepository() {
    this->dbFilePath = new std::string(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString() + "/ItemDatabase.db"
    );

    this->checker = new DatabaseConnectivityCheckerThread();

    this->checker->set(
        this->dbFilePath, this->textTblName, this->imageTblName,
        this->videoTblName, this->audioTblName
    );


    connect(
        this->checker, &DatabaseConnectivityCheckerThread::executionCompleted,
        this, &ItemRepository::checkExecutionCompletion
    );

    this->checker->start();
}

ItemRepository::~ItemRepository() {
    // TEXT
    this->textHashCollector.clear();

    // AUDIO
    qDeleteAll(this->audioHashCollector);
    this->audioHashCollector.clear();
}

bool ItemRepository::addNewTextItemHash(
    const QString& text, const int saveStatus, const qint32 size,
    const QString& ext, const QString& timeStamp, const QString& textHash
) {

    if (textHash.isNull())return  false;
    if (this->textHashCollector.contains(textHash)) return false;

    this->textHashCollector.insert(
        textHash, new TextContainer(
            text, saveStatus, size, ext, timeStamp
        )
    );

    return true;
}

bool ItemRepository::containsTextHash(const QString &textHash) const {
    return this->textHashCollector.contains(textHash);
}

bool ItemRepository::removeTextItemHash(const QString &textHash) {
    return this->textHashCollector.remove(textHash);
}

bool ItemRepository::replaceTextHash(
    const QString &newTextHash, const QString &oldTextHash, const QString& text
) {
    if (this->textHashCollector.contains(newTextHash))return false;

    TextContainer* container = this->textHashCollector.find(oldTextHash).value();

    container->text = text;
    container->textSize = text.length() * sizeof(char);

    if (this->textHashCollector.remove(oldTextHash)) {
        this->textHashCollector.insert(
            newTextHash, container
        );

        return true;
    }

    return false;
}

std::optional<TextContainer*> ItemRepository::getTextContainer(const QString &textHash) {
    if (textHash.isNull())return {nullptr};

    const QMap<QString, TextContainer*>::iterator it = this->textHashCollector.find(textHash);

    if (it == this->textHashCollector.end())return {nullptr};

    return {it.value()};
}

void ItemRepository::showTextContainer() const {
    qDebug()<<"Showing Current Text Hashes....";
    for (const auto& it : this->textHashCollector) {
        qDebug()<<it;
    }
}

// IMAGE
bool ItemRepository::addNewImageItem(
    const std::string& imageHash, const std::string& filePath, const std::string& extension,
    const int8_t saveStatus, const std::string& timeStamp
) {
    if (imageHash.empty() || filePath.empty() || extension.empty()) return false;
    if (saveStatus > 1 || saveStatus < 0)return  false;
    if (timeStamp.empty())return false;
    const qint32 sizeOfImage = ToolKit::getFileSize(filePath);

    if (this->imageHashExists(imageHash))return false;

    return  addItemToDatabase(
        *this->imageTblName, imageHash, filePath, sizeOfImage, saveStatus, extension, timeStamp
    );
}

bool ItemRepository::updateImageMetaInfo(
    const std::string& imageHash, const std::string& filePath, const std::string& ext,
    int64_t fileSize, int8_t saveStatus, const std::string& timeStamp
) {
    if (imageHash.empty())throw std::runtime_error("Invalid hash value is given!!!");

    const std::optional<ImageContainer*> it = this->getImageContainer(imageHash);

    if (!it.has_value())return false;

    const ImageContainer* container = it.value();

    const std::string& path = filePath.empty()? filePath : container->filePath;
    const std::string& extension = ext.empty()? ext : container->extension;
    if (fileSize == -1)fileSize = container->fileSize;
    if (saveStatus == -1) saveStatus = container->saveStatus;
    const std::string& stamp = timeStamp.empty()? timeStamp : container->timeStamp;

    this->openDatabase(SQLITE_OPEN_READWRITE);

    const std::string query = "UPDATE " + *this->imageTblName + " SET FilePath = '" + path + "', "
    + "FileSize = " + std::to_string(fileSize) + ", " + "saveStat = " + std::to_string(saveStatus) + ", "
    + "Ext = '" + extension + "', " + "TimeStamp = '" + stamp + "' "
    + "WHERE Hash = '" + imageHash + "';";

    char* errorMessage = nullptr;

    if (sqlite3_exec(this->dbPointer, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        throw std::runtime_error(std::string("Unable to update entry! ") + errorMessage);
    }

    sqlite3_free(errorMessage);

    this->closeDB();

    delete container;
    return true;
}

bool ItemRepository::imageHashExists(const std::string& imageHash) {
    if (imageHash.empty()) throw std::runtime_error("Invalid Image hash!!");
    return this->doesHashExists(*this->imageTblName, imageHash);
}

bool ItemRepository::removeImageItemHash(const std::string& imageHash) {
    if (imageHash.empty()) throw std::runtime_error("Invalid Image Hash!!");
    return this->removeItemFromDB(*this->imageTblName, imageHash);
}

std::optional<ImageContainer*> ItemRepository::getImageContainer(const std::string& imageHash) {
    if (imageHash.empty())return {nullptr};

    this->openDatabase(SQLITE_OPEN_READONLY);

    const std::string query = "SELECT * FROM " + *this->imageTblName +
        " WHERE Hash = '" + imageHash  + "';";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(this->dbPointer, query.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Unable to find image entry!!");
    }

    if (sqlite3_step(statement) == SQLITE_DONE) return {nullptr};

    ImageContainer* container = new ImageContainer(
        std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1))),
        sqlite3_column_int(statement, 2),
        static_cast<int8_t>(sqlite3_column_int(statement, 3)),
        std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 4))),
        std::string(reinterpret_cast<const char *>(sqlite3_column_text(statement, 5)))
    );

    sqlite3_finalize(statement);

    this->closeDB();

    return {container};
}

void ItemRepository::showImageContainer() {
    qDebug()<<"Showing current Image Hashes....";

    this->openDatabase(SQLITE_OPEN_READONLY);

    const std::string query = "SELECT * FROM " + *this->imageTblName + ";";

    sqlite3_stmt* statement;

    if (sqlite3_prepare_v2(this->dbPointer, query.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Unable to show image logs!!");
    }

    while (sqlite3_step(statement) != SQLITE_DONE) {
        for (int i = 0; i < sqlite3_column_count(statement); i++) {
            qDebug()
            << sqlite3_column_name(statement, i)
            << ": "
            << reinterpret_cast<const char *>(sqlite3_column_text(statement, i));
        }
        qDebug() << "=================================================";
    }

    sqlite3_finalize(statement);

    this->closeDB();
}

// AUDIO
bool ItemRepository::addNewAudioItem(
    const int saveStat, const qint32 size, const QString &filePath,
     const QString &ext, const QString &timeStamp, const QString &hash
) {
    if (filePath.isEmpty() || ext.isEmpty() || timeStamp.isEmpty() || hash.isEmpty())return false;
    if (saveStat < 0 || saveStat > 1)return false;

    if (audioHashExists(hash))return false;
    this->audioHashCollector.insert(
        hash, new AudioContainer(
            saveStat, size, filePath, ext, timeStamp
        )
    );

    return true;
}

bool ItemRepository::audioHashExists(const QString &hash) {
    return this->audioHashCollector.find(hash) != this->audioHashCollector.end();
}

bool ItemRepository::removeAudioItemHash(const QString &hash) {
    if (hash.isEmpty())throw invalid_argument("Invalid hash");

    const QMap<QString, AudioContainer*>::iterator it = this->audioHashCollector.find(hash);
    if (it == this->audioHashCollector.end())return  false;

    delete it.value();
    this->audioHashCollector.erase(it);

    return true;
}

std::optional<AudioContainer *> ItemRepository::getAudioContainer(const QString &audioHash) {
    if (audioHash.isEmpty())throw invalid_argument("Invalid hash");

    const QMap<QString, AudioContainer*>::iterator it = this->audioHashCollector.find(audioHash);
    if (it == this->audioHashCollector.end())return  {nullptr};
    return {it.value()};
}

void ItemRepository::showAudioContainers() const {
    qDebug()<<"Showing Audio containers..";

    for (const QString& it : this->audioHashCollector.keys()) {
        qDebug()<<"Keys: "<<it;
    }
}

// Internal Methods
void ItemRepository::openDatabase(const int flags) {
    if (sqlite3_open_v2(this->dbFilePath->c_str(), &this->dbPointer, flags, nullptr) != SQLITE_OK) {
        throw std::runtime_error(
            std::string("Unable to open the database!! ") + sqlite3_errmsg(this->dbPointer)
        );
    }
}

// Internal Methods
void ItemRepository::closeDB() const {
    if (sqlite3_close_v2(this->dbPointer) != SQLITE_OK) {
        throw std::runtime_error(
            std::string("Unable to close Database!! ") + sqlite3_errmsg(this->dbPointer)
        );
    }
}

// Internal Methods
bool ItemRepository::addItemToDatabase(
    const std::string& tblName, const std::string& hash, const std::string& path,
    const int64_t size, const int8_t status, const std::string& ext, const std::string& timeStamp
) {
    this->openDatabase(SQLITE_OPEN_READWRITE);

    const std::string query = "INSERT INTO " + tblName +
        "(Hash, FilePath, FileSize, SaveStat, Ext, TimeStamp) " +
            "VALUES( '" + hash + "', '" + path + "', " + std::to_string(size) + ", " +
                std::to_string(status) +  ", '" + ext + "', '" + timeStamp + "' );";

    char* errorMessage = nullptr;

    if (
        sqlite3_exec(this->dbPointer, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK
    ) throw std::runtime_error(
        std::string("Unable to enter clipboard item ") + sqlite3_errmsg(this->dbPointer)
    );

    sqlite3_free(errorMessage);

    this->closeDB();

    return true;
}

// Internal Methods
bool ItemRepository::doesHashExists(const std::string& tblName, const std::string& hash) {
    this->openDatabase(SQLITE_OPEN_READONLY);

    const std::string query = std::string("SELECT * FROM ") + tblName + " WHERE Hash = '" + hash + "';";

    sqlite3_stmt* statement;

    if (
        sqlite3_prepare_v2(this->dbPointer, query.c_str(), -1, &statement, nullptr) != SQLITE_OK
    )throw std::runtime_error("Data retrieval process failed!!");

    const bool output = sqlite3_step(statement) == SQLITE_ROW;

    sqlite3_finalize(statement);

    this->closeDB();

    return output;
}

// Internal Methods
bool ItemRepository::removeItemFromDB(const std::string &tblName, const std::string &hash) {
    this->openDatabase(SQLITE_OPEN_READWRITE);

    const std::string query = "DELETE FROM " + tblName + " WHERE Hash = '" + hash + "';";

    char* errorMessage;

    const bool out = sqlite3_exec(
        this->dbPointer, query.c_str(), nullptr, nullptr, &errorMessage
    ) == SQLITE_OK;

    sqlite3_free(errorMessage);

    this->closeDB();

    return out;
}

// Internal Slot
void ItemRepository::checkExecutionCompletion(void *db) {
    if (db == nullptr) throw std::runtime_error("Database is not created/found!!");
    this->dbPointer = static_cast<sqlite3*>(db);

    delete checker;

    checker = nullptr;
}
