//
// Created by sujal-stark on 8/12/25.
//

#pragma once

#include <QApplication>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QScrollArea>
#include <QFrame>

#include <string>
#include <queue>
#include <set>

// Custom Import
#include "Constants.h"
#include "ImageManagerInterface.h"
#include "ItemWidget.h"
#include "TextManagerInterface.h"


using namespace std;

class ClipBoardUI final : public QWidget{
    set<size_t> currentTextHash; //check's newly arrived string already present or not
    set<QString> currentImageHash;
    TextManagerInterface *text_manager_interface = new TextManagerInterface();
    ImageManagerInterface *image_manager_interface = new ImageManagerInterface();

                                // Method Declaration
    void constructUI() const;
    void widgetBehaviourSelection() const;
    void showItemOnScreen(ItemWidget *item) const;
    void showImageOnScreen(ItemWidget *image) const;
    void textItemClickedAction(const QString &content) const;
    void imageItemClickedAction(const QPixmap &content) const;
    void setActions() const; // used to group all connections
    void handleIncomingItems(); // get copied item from clip board
    static QString getImageObjectHash(const QImage &qImage); // creates Hash for current image
    void setCustomStyle();

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