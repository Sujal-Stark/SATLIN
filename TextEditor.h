//
// Created by sujal-stark on 1/28/26.
//

#pragma once
#include<QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include "EmojiWidget.h"
#include "Constants.h"


class TextEditor : public QWidget{
    Q_OBJECT

                                            // Components
    // Layouts
    QVBoxLayout *masterOuterLayout = new QVBoxLayout();
    QVBoxLayout *masterLayout = new QVBoxLayout();

    QHBoxLayout *textHolderLayout = new QHBoxLayout();
    QHBoxLayout *controlLayout = new QHBoxLayout();

    // QFrames
    QFrame *mainFrame = new QFrame();

    // Input Section
    QTextEdit *inputArea = new QTextEdit();

    // buttons
    QPushButton *saveButton = new QPushButton(Constants::SAVE_LABEL);
    QPushButton *confirmButton = new QPushButton(Constants::CONFIRM_LABEL);
    QPushButton *cancelButton = new QPushButton(Constants::CANCEL_LABEL);

                                            // Members
    // General
    void assignProperties() const;
    void construct() const;
    void setCustomStyle();
    void establishConnections();
    void cancelButtonAction();
    void saveButtonAction();
    void confirmButtonAction();
    void closingAction();
    static void writeTextFile(const QString &fileName, const QString &content);
    void dynamicWidgetIntegration();

                                        // Attributes
    // General
    int operationModeSignal = -1; // 0 -> save button 1 -> Edit Button

    // Text Related
    QString incomingText = nullptr;

public:
    explicit TextEditor();
    void receiveText(const QString &text, int operationMode);
};
