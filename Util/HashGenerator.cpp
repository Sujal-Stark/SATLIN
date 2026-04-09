//
// Created by sujal-stark on 2/25/26.
//

#include "HashGenerator.h"
#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>

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


QString HashGenerator::generateAudioObjectHash(const QString &address) {
    QFile file = QFile(address);
    file.open(QIODevice::ReadOnly);

    const QFileInfo info = QFileInfo(address);
    const qint32 fileSize = file.size();

    const qint32 chunkSize = qMin(100 * 1024, fileSize/3);

    auto SHA_256 = [](const QByteArray& data) -> QByteArray {
        return QCryptographicHash::hash(data, QCryptographicHash::Sha256);
    };

    file.seek(0);
    const QByteArray first4 = file.read(4);
    const QByteArray hash1 = SHA_256(file.read(chunkSize));

    file.seek(fileSize/2 - chunkSize/2);
    const QByteArray hash2 = SHA_256(file.read(chunkSize));

    file.seek(fileSize - chunkSize);
    const QByteArray hash3 = SHA_256(file.read(chunkSize));

    file.seek(fileSize - 4);
    const QByteArray hash4 = SHA_256(first4 + file.read(4));

    const QByteArray finalHash = SHA_256(hash1 + hash2 + hash3 + hash4);

    return QString("%1_%2_%3").arg(finalHash.toHex()).arg(QString::number(fileSize))
    .arg(QString::number(info.birthTime().toMSecsSinceEpoch()));
}
