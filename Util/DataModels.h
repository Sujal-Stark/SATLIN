//
// Created by sujal-stark on 3/4/26.
//

#pragma once
#include <QString>

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
    QString filePath;
    QString extension;
    QString timeStamp;
};

/**
 * @brief This Structure stores the meta-data of an Audio file copied or address based.
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
