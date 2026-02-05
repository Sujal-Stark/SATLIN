//
// Created by sujal-stark on 9/28/25.
//

#pragma once

#include<QThread>

// custom imports
#include "../Ui/ClipBoardUI.h"

class EmojiGenerator final : public QThread{
    Q_OBJECT
    signals:
    void emojiGeneratedSignal(
        int count, int tab, const QSharedPointer<QString>& emojiLabel
    ); // sends emoji back

private:
                            // Properties
    bool emojiPanelPopulationFlag[8] = {false}; // to avoid repopulation
    int emojiTab = -1; // store the current emoji tab that is open
    vector<vector<int>> emojiCodes; // accepts the emoji code from EmojiBoardUI

    void generateSmileyEmojis(const int tabIndex, const vector<vector<int>> &emojiCodeList) ;
    static QString stringToEmoji(const QString &emojiCode);

protected:
    void run() override;

public:
    void acceptEmojiGeneratingResources(int tabIndex, const vector<vector<int>> &emojiCodeList);
};
