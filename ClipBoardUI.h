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
#include <QLabel>
#include <QFrame>


using namespace std;

class ClipBoardUI final : public QWidget{
    private:
                                // Method Declaration
    void constructUI() const;
    string getCurrentCopiedText() const;
    QLabel* createTextLabel() const;
    void addNewTextToQueue();
    void showTextOnScreen();
    void widgetBehaviourSelection() const;

    public:
    explicit ClipBoardUI();
    QClipboard *clipBoard;
    queue<QLabel *> textQueue;

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