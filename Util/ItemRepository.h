//
// Created by sujal-stark on 2/25/26.
//

#pragma once

#include <qmap.h>
#include <qscopedpointer.h>
#include <QString>
#include <QSet>
#include <sqlite3.h>

#include "DatabaseConnectivityCheckerThread.h"
#include "DataModels.h"

using namespace std;

class ItemRepository : public QObject{
    Q_OBJECT

    sqlite3* dbPointer = nullptr;

    std::string* dbFilePath = nullptr;
    std::string* textTblName = new std::string("TextTable");
    std::string* imageTblName = new std::string("ImageTable");
    std::string* videoTblName = new std::string("VideoTable");
    std::string* audioTblName = new std::string("AudioTable");

    DatabaseConnectivityCheckerThread* checker = nullptr;

    /**
     * Stores The TextItem's Hash value for redundancy checking.
     */
    QMap<QString, TextContainer*> textHashCollector;

    /**
     * @brief Stores metadata corresponding to audio file via it's hash value.
     * The metadata used: saveStatus, fileSize, filePath, extension, timeStamp.
     */
    QMap<QString, AudioContainer*> audioHashCollector;

    /**
     * @brief Performs Clean up after database creation. Like Deleting the worker thread.
     * transferring ownership of the database.
     * @param db Pointer to sqlite3 structure.
     */
    void checkExecutionCompletion(void* db); // slot

    /**
     * @brief Open or create a sqlite3 database file in the given location, using
     * user given modes called flags.
     * @param flags Modes for operation defined under sqlite3.h
     */
    void openDatabase(int flags);

    /**
     * @brief Closes the database file in the given location. Throws a runtime error
     * if unsuccessful.
     */
    void closeDB() const;

    /**
     * @brief Creates an entry in the database with the given parameters. If unsuccessful then
     * throws runtime_error. Checking validity of external parameters isn't the responsibility of
     * this method.
     * @param tblName the table in which the entry will be going.
     * @param hash the primary key of the table.
     * @param path absolute file path of the item in system.
     * @param size file size.
     * @param status saved or not.
     * @param ext the extension of the file.
     * @param timeStamp Copy timestamp.
     * @return on successful insertion, returns True.
     */
    bool addItemToDatabase(
        const std::string& tblName, const std::string& hash, const std::string& path,
        int64_t size, int8_t status, const std::string& ext, const std::string& timeStamp
    );

    /**
     * @brief For the given table name and hash value this method checks if that hash value
     * exists in the database or not. Throws runtime_error if query fails. Checking validity
     * of external parameters is not the responsibility of this method.
     * @param tblName The table in which the hash will be checked
     * @param hash the primary key for the table
     * @return returns true if hash value is found.
     */
    bool doesHashExists(const std::string& tblName, const std::string& hash);

    /**
     * @brief For the given table name and hash value this method removes the entry from the table.
     * Throws runtime_error if query fails. Checking validity of the external parameter is not the
     * responsibility of this method.
     * @param tblName The table from which entry will be deleted.
     * @param hash The primary key for the table
     * @return On successful deletion returns true.
     */
    bool removeItemFromDB(const std::string& tblName, const std::string& hash);

public:
    ItemRepository();

    /**
     * @brief Removes All logged information about media when Application is closed.
     * to avoid temporary files after use.
     */
    ~ItemRepository() override;

    // Text
    /**
     * @brief Adds the Hash values of text item into the CollectorSet only if
     * the Hash Value is valid and not empty. Other-wise it returns False
     * as Failed in adding.
     * @param text Actual text copied into the system
     * @param saveStatus stores either the text is temporarily saved or permanently.
     * @param size Size of the Text in Byte.
     * @param ext Stores text extension [available in Constants]
     * @param timeStamp The time at which the text is copied into the clipboard.
     * @param textHash Hexadecimal Hash value to uniquely identify a Text.
     */
    [[nodiscard]] bool addNewTextItemHash(
        const QString& text, int saveStatus, qint32 size,
        const QString& ext, const QString& timeStamp, const QString& textHash
    );

    /**
     * @brief Given a textHash (const QString&) this method checks if repository
     * already contains this hash value or not.
     */
    [[nodiscard]] bool containsTextHash(const QString& textHash) const;

    /**
     * @brief Given a textHash(const QString&) this method removes the text hash
     * value from the repository if it is found.
     */
    [[nodiscard]] bool removeTextItemHash(const QString& textHash);

    [[nodiscard]] bool replaceTextHash(const QString& newTextHash, const QString& oldTextHash, const QString& text);

    [[nodiscard]] std::optional<TextContainer*> getTextContainer(const QString &textHash);

    /**
     * @brief Primarily used for debugging. It prints how many hash values are present
     * inside QSet.
     */
    void showTextContainer() const;

    // Image
    /**
     * @brief Checks either the parameters are valid or not and saves the information
     * as ImageContainer(DataModels.h) Structure. If the ImageHash is already present
     * in the repository then it can't be added again.
     * @param imageHash Hexadecimal hash of the image file
     * @param filePath Stores temporary location of image file
     * @param extension Stores image extension [available in Constants]
     * @param saveStatus stores either the image is temporarily saved or permanently.
     * @param  timeStamp The time at which the image is copied into the clipboard.
     * Format -> HH:MM:SS:DD:MM:YYYY
     */
    [[nodiscard]] bool addNewImageItem(
        const std::string& imageHash, const std::string& filePath, const std::string& extension,
        int8_t saveStatus, const std::string& timeStamp
    );

    /**
     * @brief Updates any or all the parameters that are listed. Throws Runtime arguments error
     * if hash value is not found or empty. Pass nullptr for the fields which will remain same.
     * @param imageHash Hexadecimal hash value of the image file
     * @param filePath updated absolute file path of the image or nullptr
     * @param ext updated extension of image file or nullptr
     * @param fileSize updated file size of image file in Bytes or -1
     * @param saveStatus updated save status of the image or -1
     * @param timeStamp updated time stamp of the image or nullptr
     * @return Returns true on the successful update on image file
     */
    [[nodiscard]] bool updateImageMetaInfo(
        const std::string& imageHash, const std::string& filePath, const std::string& ext,
        int64_t fileSize, int8_t saveStatus, const std::string& timeStamp
    );

    /**
     * @brief Check's validity of imageHash parameter. If found valid then
     * manually deletes the imageContainer(DataModels.h) structure and
     * removes the corresponding hash value.
     * @param imageHash Hexadecimal hash of the image file.
     */
    [[nodiscard]] bool removeImageItemHash(const std::string& imageHash);

    /**
     * @brief Checks if the Given hash value exists or not in the Corresponding
     * Map Object.
     * @param imageHash Hexadecimal hash value of Image Object.
     */
    [[nodiscard]] bool imageHashExists(const std::string& imageHash);

    /**
     * @brief Checks validity of ImageHash. If valid then returns the container pointer.
     * @param imageHash Hexadecimal hash value of Image Object.
     */
    [[nodiscard]] std::optional<ImageContainer*> getImageContainer(const std::string& imageHash);

    /**
     * @brief primarily used for debugging. It prints the data for all the Images that are copied
     * by the user.
     */
    void showImageContainer();

    // AUDIO
    /**
     * @brief Checks either the parameters are valid or not and saves the information
     * as AudioContainer(DataModels.h) Structure. If the hash is already present
     * in the repository then it can't be added again.
     * @param saveStat stores either the audio is temporarily saved or permanently.
     * @param size the Kilobyte size of the audio file
     * @param filePath Stores temporary location of audio file
     * @param ext Stores audio extension [available in Constants]
     * @param  timeStamp The time at which the audio is copied into the clipboard.
     * Format -> HH:MM:SS:DD:MM:YYYY
     * @param hash Hexadecimal hash of the audio file
     */
    [[nodiscard]] bool addNewAudioItem(
        int saveStat, qint32 size, const QString &filePath,
        const QString &ext, const QString &timeStamp, const QString &hash
    );

    /**
     * @brief Checks if the Given hash value exists or not in the Corresponding Map Object.
     * @param hash Hexadecimal hash value of audio Object.
     */
    [[nodiscard]] bool audioHashExists(const QString& hash);

    /**
     * @brief Check's if the given hash value exists in the corresponding map or not.
     * if found then the hash and corresponding metadata is removed.
     * @param hash Hexadecimal hash value of audio Object.
     */
    [[nodiscard]] bool removeAudioItemHash(const QString& hash);

    /**
     * @brief Checks validity of AudioHash. If valid then returns the container pointer.
     * @param audioHash Hexadecimal hash value of Audio Object.
     */
    [[nodiscard]] std::optional<AudioContainer*> getAudioContainer(const QString& audioHash);

    /**
     * @brief primarily used for debugging. It prints how many hash values are present
     * inside QMap.
     */
    void showAudioContainers() const;
};
