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
 * @param extension The Default extension of Image.
 * @param timeStamp Time it's copied.
 */
struct ImageContainer {
    int saveStatus;
    QString filePath;
    QString extension;
    QString timeStamp;
};
