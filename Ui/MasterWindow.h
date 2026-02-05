//
// Created by sujal-stark on 8/11/25.
//

#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QTabWidget>
#include "ClipBoardUI.h"
#include "EmojiBoardUI.h"

class MasterWindow final : public QMainWindow {
    Q_OBJECT
    private:
                                    // Method Declaration
    void constructUI();

    void setCustomStyle();

    public:
    explicit MasterWindow(QWidget *parent = nullptr);
                                    // Method Declaration

                                    // Widgets Definition
    // QWidgets
    QWidget *mainWidget = new QWidget();

    ClipBoardUI *clipBoard = new ClipBoardUI(); // handles Clip board UI
    QWidget *emojiBoard = new EmojiBoardUI(); // handles emoji Section

    // Tab Widgets
    QTabWidget *outerTabWidget = new QTabWidget(); // holds clip Board and Emoji Section

    // Layouts
    QVBoxLayout *masterLayout = new QVBoxLayout();
};
