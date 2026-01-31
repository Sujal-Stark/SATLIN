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
#include "TextEditor.h"


using namespace std;

class ClipBoardUI final : public QWidget{
    // General
    void constructUI() const;
    void widgetBehaviourSelection() const;
    void setActions() const; // used to group all connections
    void setCustomStyle();

    // Text Section
    set<size_t> currentTextHash; //check's newly arrived string already present or not
    TextManagerInterface *text_manager_interface = new TextManagerInterface();
    TextEditor *text_editor = new TextEditor();
    void showTextItemOnScreen(ItemWidget *item) const;
    void textItemClickedAction(const QString &content) const;

    // Image Section Related
    set<QString> currentImageHash;
    ImageManagerInterface *image_manager_interface = new ImageManagerInterface();
    void showImageOnScreen(ItemWidget *image) const;
    void imageItemClickedAction(const QPixmap &content) const;
    static QString getImageObjectHash(const QImage &qImage); // creates Hash for current image
    static QImage convertToQImage(const QMimeData *mime_data);

    // Signal Reception
    void handleIncomingItems(); // get copied item from clip board
    void accept_Text_Hash_Removal(size_t textHash);
    void accept_Image_Hash_Removal(const QString &imageHash);

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