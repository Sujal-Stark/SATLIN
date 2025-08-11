//
// Created by sujal-stark on 8/11/25.
//

#ifndef SATLIN_CONSTANTS_H
#define SATLIN_CONSTANTS_H

#include <QString>

using namespace std;

namespace  Constants {
    inline const QString APPLICATION_NAME = "Satlin";

    inline const QString CLIP_BOARD = "Clip Board";
    inline const QString EMOJI = "Emoji";

    inline const QString TEXT_SECTION = "text";
    inline const QString IMAGE_SECTION = "image";
    inline const QString VIDEO_SECTION = "video";
    inline const QString AUDIO_SECTION = "audio";

    inline constexpr int WINDOW_WIDTH = 600;
    inline constexpr int WINDOW_HEIGHT = 400;

    inline constexpr int MIN_WINDOW_WIDTH = 400;
    inline constexpr int MIN_WINDOW_HEIGHT = 300;
};


#endif //SATLIN_CONSTANTS_H