//
// Created by sujal-stark on 8/12/25.
//

#pragma once

#include <QVBoxLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <string>
#include <QApplication>
#include <queue>
#include <QFrame>
#include <QHashFunctions>
#include <set>

// Custom Import
#include "Constants.h"
#include "ItemWidget.h"


using namespace std;

class ClipBoardUI final : public QWidget{
    private:
    set<size_t> currentTextHash; //check's newly arrived string already present or not

                                // Method Declaration
    void constructUI() const;
    [[nodiscard]] string getCurrentCopiedText() const;
    ItemWidget* createTextLabel();
    void addNewTextToQueue();
    void showTextOnScreen();
    void widgetBehaviourSelection() const;
    void itemWidgetClickedAction(const string &content) const;
    void setActions();

    public:
    explicit ClipBoardUI();
    QClipboard *clipBoard;
    queue<ItemWidget *> textQueue;

                                // Method declaration


                                // Attribute Declaration
    // Frames
    QFrame *textHolderFrame = new QFrame();
    QFrame *imageHolderFrame = new QFrame();
    QFrame *audioHolderFrame = new QFrame();
    QFrame *videoHolderFrame = new QFrame();

    // Layout
    QVBoxLayout *masterLayout = new QVBoxLayout();

    QVBoxLayout *textSectionLayout = new QVBoxLayout();
    QVBoxLayout *textScrollAreaInnerLayout = new QVBoxLayout();

    QVBoxLayout *imageSectionLayout = new QVBoxLayout();
    QVBoxLayout *imageScrollAreaInnerLayout = new QVBoxLayout();

    QVBoxLayout *videoSectionLayout = new QVBoxLayout();
    QVBoxLayout *videoScrollAreaInnerLayout = new QVBoxLayout();

    QVBoxLayout *audioSectionLayout = new QVBoxLayout();
    QVBoxLayout *audioScrollAreaInnerLayout = new QVBoxLayout();

    // ScrollArea
    QScrollArea *textSectionScrollArea = new QScrollArea();
    QScrollArea *imageSectionScrollArea = new QScrollArea();
    QScrollArea *videoSectionScrollArea = new QScrollArea();
    QScrollArea *audioSectionScrollArea = new QScrollArea();

    // Tab Widget
    QTabWidget *clipTabWidget = new QTabWidget();

    // QWidget
    QWidget *textSection = new QWidget();
    QWidget *imageSection = new QWidget();
    QWidget *videoSection = new QWidget();
    QWidget *audioSection = new QWidget();
};