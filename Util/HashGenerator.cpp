//
// Created by sujal-stark on 2/25/26.
//

#include "HashGenerator.h"
#include <QCryptographicHash>

QString HashGenerator::generateTextHash(const QString &text) {
    if (text.isNull())return nullptr;

    return QCryptographicHash::hash(
        text.toUtf8(), QCryptographicHash::Sha256
    ).toHex();
}

QString HashGenerator::generateTextHash(const string &text) {
    if (text.empty())return  nullptr;

    return QCryptographicHash::hash(
        QString::fromStdString(text).toUtf8(), QCryptographicHash::Sha256
    ).toHex();
}

QString HashGenerator::generateImageObjectHash(const QString& imagePath) {
    return generateImageObjectHash(QImage(imagePath));
}

QString HashGenerator::generateImageObjectHash(const QImage &imageObject) {
    const char* bits = reinterpret_cast<const char*>(imageObject.bits());
    const qsizetype size = imageObject.sizeInBytes();

    const qsizetype chunkSize = qMin(static_cast<qsizetype>(1024), size/3);

    QByteArray chunks;
    chunks.append(bits, chunkSize); // first portion
    chunks.append(bits + size/2, chunkSize); // Middle Portion
    chunks.append(bits + size - chunkSize, chunkSize); // last portion

    const QString partialHash = QCryptographicHash::hash(
        chunks, QCryptographicHash::Sha256
    ).toHex();

    return QString("%1_%2_%3_%4").arg(imageObject.width())
    .arg(imageObject.height()).arg(size).arg(partialHash);
}
