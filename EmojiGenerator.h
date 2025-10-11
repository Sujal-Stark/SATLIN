//
// Created by sujal-stark on 9/28/25.
//

#pragma once

#include<QThread>

// custom imports
#include "ClipBoardUI.h"

class EmojiGenerator final : public QThread{
    Q_OBJECT
    signals:
    void emojiGeneratedSignal(
        QSharedPointer<std::map<int, std::vector<QString>>> emojiWidgets
    ); // sends emoji back

private:
    static vector<QString> generateSmileyEmojis() ; // 1
    static QString stringToEmoji(const QString &emojiCode);

protected:
    void run() override;
};
