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

    inline const QString EDIT_LABEL = "Edit";
    inline const QString DELETE_LABEL = "Delete";
    inline const QString SAVE_LABEL = "Save";
    inline const QString CANCEL_LABEL = "Cancel";

    inline const QString TEXT_SECTION = "Text";
    inline constexpr int TEXT_SIGNAL_INDEX = 0;

    inline const QString IMAGE_SECTION = "Image";
    inline constexpr int IMAGE_SIGNAL_INDEX = 1;

    inline const QString VIDEO_SECTION = "Video";
    inline constexpr int VIDEO_SIGNAL_INDEX = 2;

    inline const QString AUDIO_SECTION = "Audio";
    inline constexpr int AUDIO_SIGNAL_INDEX = 3;

    inline constexpr int WINDOW_WIDTH = 600;
    inline constexpr int WINDOW_HEIGHT = 400;

    inline constexpr int MIN_WINDOW_WIDTH = 400;
    inline constexpr int MIN_WINDOW_HEIGHT = 300;

    inline constexpr int TEXT_CARD_WIDTH = 490; // width of text copied Item
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
    inline constexpr int EMOJI_FONT_SIZE = 45;

    // Text Editor
    inline const QString TEXT_EDITOR_WINDOW_TITLE = "Text Editor";
    inline const QString SAVE_FILE_LABEL = "Save File";
    inline const QString CONFIRM_LABEL = "Confirm";
    inline constexpr int TEXT_EDITOR_WIDTH = 500;
    inline constexpr int TEXT_EDITOR_HEIGHT = 500;

    // Image
    inline constexpr int IMAGE_THUMBNAIL_WIDTH = 200;
    inline constexpr int IMAGE_THUMBNAIL_HEIGHT = 200;

    // ClipBoard UI

    // ItemWidget
    inline constexpr int ITEM_WIDGET_WIDTH = 530;
    inline constexpr int ITEM_MAIN_FRAME_WIDTH = ITEM_WIDGET_WIDTH - 20;
    inline constexpr int ITEM_WIDGET_EDIT_BUTTON_WIDTH = 60;
    inline constexpr int ITEM_WIDGET_EDIT_BUTTON_HEIGHT = 25;
};