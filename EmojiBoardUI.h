//
// Created by sujal-stark on 9/28/25.
//

#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>

class EmojiBoardUI final : public QWidget{
public:
                                    // Method Declaration
    explicit EmojiBoardUI();

private:
                                    // Method Declaration
    void constructUI() const;

                                    // Attribute Declaration
    // Layout
    QVBoxLayout *masterLayout = new QVBoxLayout();

    QVBoxLayout *recentSectionLayout = new QVBoxLayout();
    QGridLayout *recentSectionGrid = new QGridLayout();

    QVBoxLayout *reactionSectionLayout = new QVBoxLayout();
    QGridLayout *reactionSectionGrid = new QGridLayout();

    QVBoxLayout *animalSectionLayout = new QVBoxLayout();
    QGridLayout *animalSectionGrid = new QGridLayout();

    QVBoxLayout *foodSectionLayout = new QVBoxLayout();
    QGridLayout *foodSectionGrid = new QGridLayout();

    QVBoxLayout *placesSectionLayout = new QVBoxLayout();
    QGridLayout *placesSectionGrid = new QGridLayout();

    // ScrollArea
    QScrollArea *recentSectionScrollArea = new QScrollArea();
    QScrollArea *reactionSectionScrollArea = new QScrollArea();
    QScrollArea *animalSectionScrollArea = new QScrollArea();
    QScrollArea *foodSectionScrollArea = new QScrollArea();
    QScrollArea *placesSectionScrollArea = new QScrollArea();

    // Frames
    QFrame *recentSectionFrames = new QFrame();
    QFrame *reactionSectionFrames = new QFrame();
    QFrame *animalSectionFrames = new QFrame();
    QFrame *foodSectionFrames = new QFrame();
    QFrame *placesSectionFrames = new QFrame();


    // Main Tab
    QTabWidget *emojiPanel = new QTabWidget();

    // Emoji tabs
    QWidget *emojiRecentSection = new QWidget();
    QWidget *emojiReactionSection = new QWidget();
    QWidget *emojiAnimalSection = new QWidget();
    QWidget *emojiFoodSection = new QWidget();
    QWidget *emojiPlaceSection = new QWidget();
    // QWidget *emojiActivitySection = new QWidget();
    // QWidget *emojiObjectsSection = new QWidget();
    // QWidget *emojiSymbolSection = new QWidget();
};
