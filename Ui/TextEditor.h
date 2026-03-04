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
    QPushButton *confirmButton = new QPushButton();
    QPushButton *cancelButton = new QPushButton();

                                            // Members
    // General
    void assignProperties() const;
    void construct() const;

    void setCustomStyle();

    /**
     * Build Connections with UI Components and Member Classes
     * with the Actionable methods.
     */
    void establishConnections();

    /**
     * If the editing is canceled in between then this method calls
     * closing actions. It sends an textEditedSignal to
     * TextManagerInterface with a nullPtr.
     */
    void cancelButtonAction();

    /**
     * Sends The edited text to the TextEditorInterface and
     * calls closingAction()
     */
    void confirmButtonAction();

    /**
     * Performs Termination of the TextEditor. Clears The QTextEdit Object.
     * Closes the window.
     */
    void closingAction();

    signals:
    /**
     * When the text is edited this signal transfer's the edited text
     * to TextManagerInterface.
     */
    void textEditedSignal(QString editedText);

public:
    explicit TextEditor();

    /**
     * Receives a QString from TextManagerInterface to perform
     * further editing.
     */
    void receiveText(const QString &text) const;
};
