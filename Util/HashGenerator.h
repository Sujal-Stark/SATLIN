//
// Created by sujal-stark on 2/25/26.
//

#pragma once
#include <QString>

#include "../ManagerSources/ImageManagerInterface.h"


class HashGenerator {
public:
    /**
     * @brief Given a FilePath this method returns a QString which represents
     * a unique hash value of the file path. The hash is in hexadecimal
     * format. This method uses SHA256 hashing algorithm.
     * @param text The Original text copied by application.
     */
    static QString generateTextHash(const QString& text);
    static QString generateTextHash(const string& text);

    /**
     * @brief generates a SHA256 hash value based some chunks from the
     * image itself and combine it's meta-data like byteSize, width,
     * height as additional safety.
     * @param imagePath file path of the image.
     */
    static QString generateImageObjectHash(const QString& imagePath);

    /**
     * @brief generates a SHA256 hash value based some chunks from the
     * image itself and combine it's meta-data like byteSize, width,
     * height as additional safety.
     * @param imageObject Image Object.
     */
    static QString generateImageObjectHash(const QImage& imageObject);
};
