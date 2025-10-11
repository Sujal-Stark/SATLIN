//
// Created by sujal-stark on 9/28/25.
//

#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTableWidget>

#include "ClipBoardUI.h"
#include "EmojiGenerator.h"

class EmojiBoardUI final : public QWidget{
public:
                                    // Method Declaration
    explicit EmojiBoardUI();

private:
                                    // Method Declaration
    void constructUI() const;
    void signalConnector() const;
    void propertyHandler() const;
    void emojiReceivedAction(const QSharedPointer<std::map<int, std::vector<QString>>>& emojiWidgets);

                                    // Attribute Declaration
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
};
