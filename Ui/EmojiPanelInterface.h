//
// Created by sujal-stark on 9/28/25.
//

#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QString>

#include "ClipBoardInterface.h"
#include "../Util/EmojiGenerator.h"
#include "../Util/Constants.h"

class EmojiPanelInterface final : public QWidget{
public:
                                    // Method Declaration
    explicit EmojiPanelInterface();

private:
                                    // Method Declaration
    void tabWidgetChangedAction(int tabIndex);
    void constructUI() const;
    void signalConnector() const;
    void propertyHandler();
    void emojiReceivedAction(int count, int tab, const QSharedPointer<QString> &emojiLabel);
    void setCustomStyle();

                                    // Attribute Declaration
    // resource
    const vector<vector<vector<int>>> emojiCodes = {
        {

        },// 0
        {
            {128512, 128591}, {129296, 129306}, {129325, 129329}
        }, // 1
        {
            {128000, 128127}, {129409, 129423}
        }, // 2
        {
        }, // 3
        {
        }, // 4
        {
        }, // 5
        {
        }, // 6
        {
        }, // 7
    };
    // Threads
    EmojiGenerator eGenerator;

    // Layout
    QVBoxLayout *masterLayout = new QVBoxLayout();

    QVBoxLayout *recentSectionLayout = new QVBoxLayout();
    QTableWidget *recentSectionGrid = new QTableWidget();

    QVBoxLayout *reactionSectionLayout = new QVBoxLayout();
    QTableWidget *reactionSectionGrid = new QTableWidget();

    QVBoxLayout *animalSectionLayout = new QVBoxLayout();
    QTableWidget *animalSectionGrid = new QTableWidget();

    QVBoxLayout *foodSectionLayout = new QVBoxLayout();
    QTableWidget *foodSectionGrid = new QTableWidget();

    QVBoxLayout *placesSectionLayout = new QVBoxLayout();
    QTableWidget *placesSectionGrid = new QTableWidget();

    QVBoxLayout *activitySectionLayout = new QVBoxLayout();
    QTableWidget *activitySectionGrid = new QTableWidget();

    QVBoxLayout *objectSectionLayout = new QVBoxLayout();
    QTableWidget *objectSectionGrid = new QTableWidget();

    QVBoxLayout *symbolSectionLayout = new QVBoxLayout();
    QTableWidget *symbolSectionGrid = new QTableWidget();

    // ScrollArea
    QScrollArea *recentSectionScrollArea = new QScrollArea();
    QScrollArea *animalSectionScrollArea = new QScrollArea();
    QScrollArea *foodSectionScrollArea = new QScrollArea();
    QScrollArea *placesSectionScrollArea = new QScrollArea();
    QScrollArea *activitySectionScrollArea = new QScrollArea();
    QScrollArea *objectSectionScrollArea = new QScrollArea();
    QScrollArea *symbolSectionScrollArea = new QScrollArea();

    // Frames
    QFrame *recentSectionFrames = new QFrame();
    QFrame *animalSectionFrames = new QFrame();
    QFrame *foodSectionFrames = new QFrame();
    QFrame *placesSectionFrames = new QFrame();
    QFrame *activitySectionFrames = new QFrame();
    QFrame *objectSectionFrames = new QFrame();
    QFrame *symbolSectionFrames = new QFrame();

    // Main Tab
    QTabWidget *emojiPanel = new QTabWidget();

    // Emoji tabs
    QWidget *emojiRecentSection = new QWidget(); // 0
    QWidget *emojiReactionSection = new QWidget(); // 1
    QWidget *emojiAnimalSection = new QWidget(); // 2
    QWidget *emojiFoodSection = new QWidget(); // 3
    QWidget *emojiPlaceSection = new QWidget(); // 4
    QWidget *emojiActivitySection = new QWidget(); // 5
    QWidget *emojiObjectsSection = new QWidget(); // 6
    QWidget *emojiSymbolSection = new QWidget(); // 7

    // fonts
    QFont emojiFont;
};
