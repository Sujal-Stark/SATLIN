//
// Created by sujal-stark on 9/28/25.
//

#include "EmojiGenerator.h"
#include "QDebug"
#include "sstream"

void EmojiGenerator::run() {
    if (!this->emojiPanelPopulationFlag[this->emojiTab]) {
        this->emojiPanelPopulationFlag[this->emojiTab] = true; // makes sure copy shall not occur
        generateSmileyEmojis(this->emojiTab, this->emojiCodes);
    }
}

void EmojiGenerator::generateSmileyEmojis(const int tabIndex, const vector<vector<int>> &emojiCodeList) {
    QFont emojiFont(Constants::EMOJI_FONT.data());
    emojiFont.setPointSize(Constants::EMOJI_FONT_SIZE);
    int cnt = 0;
    for (vector<int> currList : emojiCodeList) {
        const int start = currList[0], finish = currList[1];
        for (int i = start; i <= finish; i++) {
            stringstream ss;
            ss<<hex<<uppercase<<i; // hex code creation
            QString emoCode = QString::fromUtf8(ss.str());
            emit this->emojiGeneratedSignal(
            cnt, tabIndex, QSharedPointer<QString>::create(
                    stringToEmoji(emoCode)
                )
            );
            cnt++;
        }
    }
}

QString EmojiGenerator::stringToEmoji(const QString &emojiCode) {
    bool ok = false;
    const auto finalCode = static_cast<char32_t>(emojiCode.toInt(&ok, 16)); //char32_t
    if (ok)return QString::fromUcs4(&finalCode, 1);
    return QString::fromStdString("");
}

void EmojiGenerator::acceptEmojiGeneratingResources(
    const int tabIndex, const vector<vector<int> > &emojiCodeList
) {
    this->emojiTab = tabIndex;
    this->emojiCodes = emojiCodeList;
}

