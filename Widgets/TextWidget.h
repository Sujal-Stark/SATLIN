//
// Created by sujal-stark on 4/14/26.
//

#pragma once

#include "ItemWidget.h"
#include "../ManagerSources/ImageManagerInterface.h"
#include "../Ui/TextEditor.h"
#include "../ManagerSources/TextManagerInterface.h"
#include "../Util/ItemRepository.h"

class TextWidget : public ItemWidget {
    Q_OBJECT
    shared_ptr<TextManagerInterface> textManagerInterface = nullptr;

    QPointer<QLabel>textLabel = nullptr;

protected:
                                            // Methods

    /**
     * Removes Current Hash value.
     * Sends a Signal to ClipBoardInterface to release clipboard content.
     * Set this widget for deletion.
     */
    void deleteButtonClicked() override;

    /**
     * Expects a valid filePath and text content. This method dump the content as Text
     * into the file. and Saves it. If the file already exists then this method
     * removes all the previous content.
     */
    void saveButtonClicked() override;

    /**
     * Sends the current text from text label to the TextManagerInterface.
     * Establish connection with textEditedSignal of TextManagerInterface
     * with editTextReceivedAction.
     */
    void editButtonClicked() override;

    /**
     * Receives edited Text from TextManagerInterface. Removes the old hash value
     * that textLabel possess and stores the new hash value. A signal is sent to
     * clipboard interface to set the edited text as clipboard content. disconnects
     * signals from TextEditorInterface with this method.
     */
    void editedTextReceivedAction(const QString& editedText);

signals:
    /**
     * Sends the TextLabel's content to the ClipBoardInterface when the
     * widget is clicked.
     */
    void textItemClickedSignal(QString text);

    /**
     * Sends a signal to clipboardInterface to release the Clipboard's
     * content.
     */
    void clipboardCleanSignal();

protected:
    /**
     * As the Widget is Clicked this method made changes in Widget's style.
     * Sends a signal to ClipBoardInterface to set current item in clipBoard.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * Reverts the style to default as the press is released.
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    explicit TextWidget();

    /**
     * Creates a textLabel from the given Text and show the textLabel
     * in the UI.
     */
    void assignText(const QString& text, const QString& textHash); // holds text

    /**
     * Accepts Drivers Like TextManagerInterface and ItemRepository.
     * Saves TextManagersInterface's pointer and assign ItemRepository
     * to the TextManagerInterface. Connect with TextManagerInterface's
     * signal.
     */
    void setTextManagerInterfaceInputs(
        const shared_ptr<TextManagerInterface>& interface,
        const shared_ptr<ItemRepository>& repo
    );
};
