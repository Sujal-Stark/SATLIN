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

    // IMAGE
    qDeleteAll(this->imageHashCollector);
    this->imageHashCollector.clear();

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
    const QString &imageHash, const QString &filePath, const QString &extension,
    const int saveStatus, const QString &timeStamp
) {
    if (imageHash.isEmpty() || filePath.isEmpty() || extension.isEmpty()) return false;
    if (saveStatus > 1 || saveStatus < 0)return  false;
    if (timeStamp.isEmpty())return false;
    const qint32 sizeOfImage = ToolKit::getFileSize(filePath);

    addItemToDatabase(*this->imageTblName, imageHash, filePath, sizeOfImage, saveStatus, extension, timeStamp);

    if (this->imageHashExists(imageHash))return false;

    this->imageHashCollector.insert(
        imageHash, new ImageContainer(
            filePath, sizeOfImage, saveStatus, extension, timeStamp
        )
    );

    std::optional<ImageContainer*> cont = getImageContainer(imageHash);
    return true;
}

bool ItemRepository::imageHashExists(const QString& imageHash) {
    qDebug() << this->doesHashExists(*this->imageTblName, imageHash.toStdString());
    const QMap<QString, ImageContainer*>::iterator it = this->imageHashCollector.find(imageHash);

    return it != this->imageHashCollector.end();
}

bool ItemRepository::removeImageItemHash(const QString &imageHash) {

    const QMap<QString, ImageContainer*>::iterator it = this->imageHashCollector.find(imageHash);
    if (it == this->imageHashCollector.end())return false;
    delete it.value();
    this->imageHashCollector.erase(it);
    return true;
}

std::optional<ImageContainer*> ItemRepository::getImageContainer(const QString& imageHash) {
    if (imageHash.isEmpty())return {nullptr};

    this->openDatabase(SQLITE_OPEN_READONLY);

    const std::string query = "SELECT * FROM " + *this->imageTblName +
        " WHERE Hash = '" + imageHash.toStdString()  + "';";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(this->dbPointer, query.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        return {nullptr};
    }

    if (sqlite3_step(statement) != SQLITE_ROW) return {nullptr};

    ImageContainer* container = new ImageContainer(
        QString(reinterpret_cast<const char *>(sqlite3_column_text(statement, 1))),
        sqlite3_column_int(statement, 2),
        sqlite3_column_int(statement, 3),
        QString(reinterpret_cast<const char *>(sqlite3_column_text(statement, 4))),
        QString(reinterpret_cast<const char *>(sqlite3_column_text(statement, 5)))
    );

    sqlite3_close(this->dbPointer);

    return {container};
}

void ItemRepository::showImageContainer() const {
    qDebug()<<"Showing current Image Hashes....";
    for (const auto& it : this->imageHashCollector.keys()) {
        qDebug()<<it;
    }
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

bool ItemRepository::openDatabase(const int flags) {
    return sqlite3_open_v2(this->dbFilePath->c_str(), &this->dbPointer, flags, nullptr) == SQLITE_OK;
}

bool ItemRepository::addItemToDatabase(
    const std::string &tblName, const QString &hash, const QString &path,
    const qint32 size, const int status, const QString &ext, const QString &timeStamp
) {
    if (!this->openDatabase(SQLITE_OPEN_READWRITE))throw std::runtime_error(
        std::string("Unable to open DB ") + sqlite3_errmsg(this->dbPointer)
    );

    const std::string query = "INSERT INTO " + tblName +
        "(Hash, FilePath, FileSize, SaveStat, Ext, TimeStamp) " +
            "VALUES( '" + hash.toStdString() + "', '" + path.toStdString() + "', " + std::to_string(size) + ", " +
                std::to_string(status) +  ", '" + ext.toStdString() + "', '" + timeStamp.toStdString() + "' );";

    char* errorMessage = nullptr;

    if (
        sqlite3_exec(this->dbPointer, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK
    ) throw std::runtime_error(
        std::string("Unable to enter clipboard item ") + sqlite3_errmsg(this->dbPointer)
    );

    sqlite3_close(this->dbPointer);

    return true;
}

bool ItemRepository::doesHashExists(const std::string &tblName, const std::string &hash) {
    if (tblName.empty() || hash.empty())throw std::runtime_error("Invalid arguments!!");

    if (!this->openDatabase(SQLITE_OPEN_READWRITE)) throw std::runtime_error(
        std::string("Unable to open DB, ") + sqlite3_errmsg(this->dbPointer)
    );

    const std::string query = std::string("SELECT COUNT(*) FROM ") + tblName +
        " WHERE Hash = '" + hash + "';";

    sqlite3_stmt* statement;

    if (
        sqlite3_prepare_v2(this->dbPointer, query.c_str(), -1, &statement, nullptr) != SQLITE_OK
    )throw std::runtime_error("Data retrieval process failed!!");

    int count = 0;

    if (sqlite3_step(statement) == SQLITE_ROW)count = sqlite3_value_int(sqlite3_column_value(statement, 0));
    else throw std::runtime_error("Data retrieval process failed!!");

    sqlite3_finalize(statement);
    sqlite3_close(this->dbPointer);

    return count == 1;
}

bool ItemRepository::removeItemFromDB(const std::string &tblName, const std::string &hash) {
    if (hash.empty())throw std::runtime_error("Invalid Hash argument!!");

    if (!this->openDatabase(SQLITE_OPEN_READWRITE)) throw std::runtime_error(
        std::string("Unable to open Db ") + sqlite3_errmsg(this->dbPointer)
    );

    const std::string query = "DELETE FROM " + tblName + " WHERE Hash = '" + hash + "';";

    char* errorMessage;

    const bool out = sqlite3_exec(
        this->dbPointer, query.c_str(), nullptr, nullptr, &errorMessage
    ) == SQLITE_OK;

    sqlite3_close(this->dbPointer);

    return out;
}

void ItemRepository::checkExecutionCompletion(void *db) {
    if (db == nullptr) throw std::runtime_error("Database is not created/found!!");
    this->dbPointer = static_cast<sqlite3*>(db);

    delete checker;

    checker = nullptr;
}
