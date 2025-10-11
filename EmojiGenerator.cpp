//
// Created by sujal-stark on 9/28/25.
//

#include "EmojiGenerator.h"
#include "QDebug"
#include "sstream"
#include "map"

void EmojiGenerator::run() {
    const vector<QString> smileys = generateSmileyEmojis();
    const auto finalData = QSharedPointer<
        std::map<int, std::vector<QString>>
    >::create();
    (*finalData)[1] = smileys;
    emit this->emojiGeneratedSignal(finalData);
}

vector<QString> EmojiGenerator::generateSmileyEmojis() {
    // 128512 is the starting emoji && 128591 is the ending emoji
    constexpr int start = 128512, finish = 128591;
    vector<QString> smileys(finish - start + 1); // store the output
    for (int i = start; i <= finish; i++) {
        stringstream ss;
        ss<<hex<<uppercase<<i; // hex code creation
        QString emoCode = QString::fromUtf8(ss.str());
        smileys[i - start] = stringToEmoji(emoCode);
    }
    return smileys;
}

QString EmojiGenerator::stringToEmoji(const QString &emojiCode) {
    bool ok = false;
    const auto finalCode = static_cast<char32_t>(emojiCode.toInt(&ok, 16)); //char32_t
    if (ok)return QString::fromUcs4(&finalCode, 1);
    return QString::fromStdString("");
}
