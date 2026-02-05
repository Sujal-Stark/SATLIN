//
// Created by sujal-stark on 1/28/26.
//

#pragma once
#include<QTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

#include "../Widgets/EmojiWidget.h"
#include "../Util/Constants.h"
#include "../ManagerSources/IconManager.h"


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
    QPushButton *saveButton = new QPushButton();
    QPushButton *confirmButton = new QPushButton();
    QPushButton *cancelButton = new QPushButton();

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
