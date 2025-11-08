//
// Created by sujal-stark on 8/11/25.
//

#pragma once

#include <QString>
#include <string>

using namespace std;

namespace  Constants {
    inline const QString APPLICATION_NAME = "Satlin";

    inline const QString CLIP_BOARD = "Clip Board";
    inline const QString EMOJI = "Emoji";

    inline const QString TEXT_SECTION = "text";
    inline constexpr int TEXT_SIGNAL_INDEX = 0;

    inline const QString IMAGE_SECTION = "image";
    inline constexpr int IMAGE_SIGNAL_INDEX = 1;

    inline const QString VIDEO_SECTION = "video";
    inline constexpr int VIDEO_SIGNAL_INDEX = 2;

    inline const QString AUDIO_SECTION = "audio";
    inline constexpr int AUDIO_SIGNAL_INDEX = 3;

    inline constexpr int WINDOW_WIDTH = 600;
    inline constexpr int WINDOW_HEIGHT = 400;

    inline constexpr int MIN_WINDOW_WIDTH = 400;
    inline constexpr int MIN_WINDOW_HEIGHT = 300;

    inline constexpr int TEXT_CARD_WIDTH = 520; // width of text copied Item
    inline constexpr int WIDGET_MARGIN = 10;

    inline const QString RECENT = "Recent";
    inline const QString REACTION = "Smileys & Reactions";
    inline const QString ANIMALS = "Animals";
    inline const QString FOODS = "Foods & Drinks";
    inline const QString PLACES = "Places & tourism";
    inline const QString ACTIVITY = "Activity";
    inline const QString OBJECTS_HEADER = "Objects";
    inline const QString SYMBOLS = "Symbols";

    inline constexpr int EMOJI_CELL_WIDTH = 82;
    inline constexpr int EMOJI_CELL_HEIGHT = 82;


    // Fonts
    inline const string EMOJI_FONT = "Noto Color Emoji";
    inline constexpr int EMOJI_FONT_SIZE = 30;

    // Image
    inline constexpr int IMAGE_THUMBNAIL_WIDTH = 200;
    inline constexpr int IMAGE_THUMBNAIL_HEIGHT = 200;
};