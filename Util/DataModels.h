//
// Created by sujal-stark on 3/4/26.
//

#pragma once
#include <QString>
#include <QDebug>

struct TextContainer {
    QString text;
    int saveStatus;
    qint32 textSize;
    QString extension;
    QString timeStamp;
};

inline QDebug operator<<(QDebug debug, const TextContainer* container) {
    if (container) {
        debug << "TextContainer["
        << " Text: " + container->text
        << " extension: " + container->extension
        << " save status: " + QString::fromStdString(std::to_string(container->saveStatus))
        << " size: " + QString::fromStdString(std::to_string(container->textSize)) << " kb"
        << " time stamp: " + container->timeStamp
        << " ]";
    }else debug<<"NULL";

    return debug;
}

/**
 * @brief This Structure Stores The metadata of an Image File Copied or address based.
 * used for clubbing all necessary information of Image all together.
 * @param saveStatus Expresses either a ImageFile is stored temporarily or permanently
 * @param filePath System Address of the Image File.
 * @param extension The extension of Image.
 * @param timeStamp Time it's copied.
 */
struct ImageContainer {
    int saveStatus;
    qint32 fileSize;
    QString filePath;
    QString extension;
    QString timeStamp;
};

/**
 * @brief This Structure stores the metadata of an Audio file copied or address based.
 * Used for clubbing all necessary information of audio file all together.
 * @param saveStatus Expresses either an audio file stored permanently or temporarily.
 * @param fileSize The Kilobyte size of audio File.
 * @param filePath System Address of the audio File.
 * @param extension The extension of audio.
 * @param timeStamp Time it's copied.
 */
struct AudioContainer {
    int saveStatus;
    qint32 fileSize;
    QString filePath;
    QString extension;
    QString timeStamp;
};