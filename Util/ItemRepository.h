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
     * @brief Stores metaData Corresponding to image items via it's hash value.
     * The meta used: file path(QString), extension(QString), saveStatus(int),
     * timeStamp(QString). These metadata are wrapped inside ImageContainer
     * data model.
     */
    QMap<QString, ImageContainer*> imageHashCollector;

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

    /**
     * @brief Primarily used for debugging. It prints how many hash values are present
     * inside QSet.
     */
    void showTextContainer() const;
};
