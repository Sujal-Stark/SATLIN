//
// Created by sujal-stark on 8/11/25.
//

#include <QMainWindow>

#include "MasterWindow.h"
#include "Constants.h"

MasterWindow::MasterWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(Constants::APPLICATION_NAME);
    resize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    setMinimumSize(Constants::MIN_WINDOW_WIDTH, Constants::MIN_WINDOW_HEIGHT);
    setCentralWidget(mainWidget);
    constructUI();
    setCustomStyle();
}

void MasterWindow::constructUI() {
    mainWidget->setLayout(masterLayout);

    masterLayout->addWidget(this->outerTabWidget);
    this->outerTabWidget->tabBar()->setUsesScrollButtons(false);
    this->outerTabWidget->tabBar()->setExpanding(true);

    outerTabWidget->addTab(clipBoard, Constants::CLIP_BOARD);
    outerTabWidget->addTab(emojiBoard, Constants::EMOJI);
}

void MasterWindow::setCustomStyle() {
    this->setStyleSheet(
        "background-color: rgba(28, 27, 28, 255);"
    );
    outerTabWidget->setStyleSheet(
        "QTabBar::tab {"
            "height: 40px;"
            "font-size: 16px;"
            "width: 300px;"
        "}"
    );
}


