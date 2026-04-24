//
// Created by sujal-stark on 9/22/25.
//

#pragma once

#include<QMouseEvent>
#include<QPushButton>
#include<QHBoxLayout>

#include "../Util/Constants.h"
#include "../ManagerSources/ImageManagerInterface.h"
#include "../Ui/TextEditor.h"
#include "../ManagerSources/TextManagerInterface.h"
#include "../Util/ItemRepository.h"

class ItemWidget : public QWidget{
    Q_OBJECT

protected:
    // QButtons
    QPushButton *deleteButton = new QPushButton();
    QPushButton *editButton = new QPushButton();
    QPushButton *saveButton = new QPushButton();

    // Layouts
    QVBoxLayout *masterLayout = new QVBoxLayout();
    QVBoxLayout *masterInnerLayout = new QVBoxLayout();

    QHBoxLayout *contentHolder = new QHBoxLayout();
    QHBoxLayout *buttonHolder = new QHBoxLayout();

    // Frames
    QFrame *mainFrame = new QFrame();

                                            // Methods
    void stylizeButtons() const;
    void stylizeFrames() const;

    /**
     * Builds connections with UI elements with actionable methods.
     */
    void establishConnections();

    /**
     * Removes Current Hash value.
     * Sends a Signal to ClipBoardInterface to release clipboard content.
     * Set this widget for deletion.
     */
    virtual void deleteButtonClicked() = 0;

    /**
     * Expects a valid filePath and text content. This method dump the content as Text
     * into the file. and Saves it. If the file already exists then this method
     * removes all the previous content.
     */
    virtual void saveButtonClicked() = 0;

    /**
     * Sends the current text from text label to the TextManagerInterface.
     * Establish connection with textEditedSignal of TextManagerInterface
     * with editTextReceivedAction.
     */
    virtual void editButtonClicked() = 0;

public:
    ItemWidget();
    void construct() const;
};