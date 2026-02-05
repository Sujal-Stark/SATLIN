//
// Created by sujal-stark on 2/4/26.
//

#include "IconManager.h"

QIcon IconManager::saveIcon() {
    return QIcon(":/Download");
}

QIcon IconManager::confirmIcon() {
    return QIcon(":/Check");
}

QIcon IconManager::cancelIcon() {
    return QIcon(":/Cancel");
}

QIcon IconManager::editIcon() {
    return QIcon(":/Edit");
}

QIcon IconManager::textIcon() {
    return QIcon(":/Text");
}

QIcon IconManager::photoIcon() {
    return QIcon(":/Photo");
}

QIcon IconManager::videoIcon() {
    return QIcon(":/Video");
}

QIcon IconManager::audioIcon() {
    return QIcon(":/Audio");
}

QIcon IconManager::clipboardIcon() {
    return QIcon(":/Clipboard");
}

QIcon IconManager::emojiPanelIcon() {
    return QIcon(":/EmojiPanel");
}
