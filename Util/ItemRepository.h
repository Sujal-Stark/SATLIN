//
// Created by sujal-stark on 2/25/26.
//

#pragma once

#include <qmap.h>
#include <qscopedpointer.h>
#include <QString>
#include <QSet>

#include "DataModels.h"

using namespace std;

class ItemRepository {
    /**
     * Stores The TextItem's Hash value for redundancy checking.
     */
    QSet<QString> textHashCollector;

    /**
     * @brief Stores metadata Corresponding to image items via it's hash value.
     * The meta used: file path(QString), extension(QString), saveStatus(int),
     * timeStamp(QString). These metadata are wrapped inside ImageContainer
     * data model.
     */
    QMap<QString, ImageContainer*> imageHashCollector;

    /**
     * @brief Stores metadata corresponding to audio file via it's hash value.
     * The metadata used: saveStatus, fileSize, filePath, extension, timeStamp.
     */
    QMap<QString, AudioContainer*> audioHashCollector;

public:
    ItemRepository();

    /**
     * @brief Removes All logged information about media when Application is closed.
     * to avoid temporary files after use.
     */
    ~ItemRepository();

    // Text
    /**
     * @brief Adds the Hash values of text item into the CollectorSet only if
     * the Hash Value is valid and not empty. Other-wise it returns False
     * as Failed in adding.
     * @param textHash Hexadecimal Hash value to uniquely identify a Text.
     */
    [[nodiscard]] bool addNewTextItemHash(const QString& textHash);

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
        const QString& imageHash, const QString& filePath, const QString& extension,
        int saveStatus, const QString& timeStamp
    );

    /**
     * @brief Check's validity of imageHash parameter. If found valid then
     * manually deletes the imageContainer(DataModels.h) structure and
     * removes the corresponding hash value.
     * @param imageHash Hexadecimal hash of the image file.
     */
    [[nodiscard]] bool removeImageItemHash(const QString& imageHash);

    /**
     * @brief Checks if the Given hash value exists or not in the Corresponding
     * Map Object.
     * @param imageHash Hexadecimal hash value of Image Object.
     */
    [[nodiscard]] bool imageHashExists(const QString& imageHash);

    /**
     * @brief Checks validity of ImageHash. If valid then returns the container pointer.
     * @param imageHash Hexadecimal hash value of Image Object.
     */
    [[nodiscard]] const ImageContainer* getImageContainer(const QString& imageHash);

    /**
     * @brief primarily used for debugging. It prints how many hash values are present
     * inside QMap.
     */
    void showImageContainer() const;

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
    [[nodiscard]] const AudioContainer* getAudioContainer(const QString& audioHash);

    /**
     * @brief primarily used for debugging. It prints how many hash values are present
     * inside QMap.
     */
    void showAudioContainers() const;
};
