//
// Created by sujal-stark on 8/12/25.
//

#ifndef SATLIN_CLIPBOARDUI_H
#define SATLIN_CLIPBOARDUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QScrollArea>


class ClipBoardUI final : public QWidget{
    private:
                                // Method Declaration
    void constructUI();

    public:
    explicit ClipBoardUI();
                                // Method declaration


                                // Attribute Declaration
    // Layout
    QVBoxLayout *masterLayout = new QVBoxLayout();

    QVBoxLayout *textSectionLayout = new QVBoxLayout();
    QVBoxLayout *imageSectionLayout = new QVBoxLayout();
    QVBoxLayout *videoSectionLayout = new QVBoxLayout();
    QVBoxLayout *audioSectionLayout = new QVBoxLayout();

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


#endif //SATLIN_CLIPBOARDUI_H