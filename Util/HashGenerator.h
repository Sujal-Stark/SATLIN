//
// Created by sujal-stark on 2/25/26.
//

#pragma once
#include <QString>

#include "../ManagerSources/ImageManagerInterface.h"


class HashGenerator {
public:
    /**
     * Given a FilePath this method returns a QString which represents
     * a unique hash value of the file path. The hash is in hexadecimal
     * format. This method uses SHA256 hashing algorithm.
     */
    static QString generateTextHash(const QString& text);
    static QString generateTextHash(const string& text);

    /**
     * Given an imageObject(const QImage&) this method generates a SHA256
     * hash value based some chunks from the image itself and combine
     * it's meta-data like byteSize, width, height as additional safety.
     */
    static QString generateImageObjectHash(const QImage& imageObject);
};
