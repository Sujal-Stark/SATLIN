//
// Created by sujal-stark on 9/22/25.
//

#pragma once

#include<QMouseEvent>
#include<QPushButton>
#include<QHBoxLayout>

#include "../CustomWidgets/RegularButton.h"
#include "../Util/Constants.h"
#include "../ManagerSources/ImageManagerInterface.h"
#include "../Ui/TextEditor.h"
#include "../ManagerSources/TextManagerInterface.h"
#include "../Util/ItemRepository.h"

class ItemWidget : public QWidget{
    Q_OBJECT

protected:
    // QLabels
    QLabel* savePropertyCard = new QLabel();
    QLabel* extensionCard = new QLabel();
    QLabel* timeStampCard = new QLabel();

    // QButtons
    RegularButton *deleteButton = new RegularButton(nullptr);
    RegularButton *editButton = new RegularButton(nullptr);
    RegularButton *saveButton = new RegularButton(nullptr);

    // Layouts
    QVBoxLayout *masterLayout = new QVBoxLayout();
    QVBoxLayout *masterInnerLayout = new QVBoxLayout();

    QHBoxLayout *metaInfoHolder = new QHBoxLayout();
    QHBoxLayout *contentHolder = new QHBoxLayout();
    QHBoxLayout *buttonHolder = new QHBoxLayout();

    // Frames
    QFrame *mainFrame = new QFrame();

    // Animations
    QPropertyAnimation* expandContractAnimation = new QPropertyAnimation(this, "size");

                                            // Methods
    /**
     * @brief For the QPushButtons and their subclass objects
     * declared in this class, their properties are chosen inside
     * this method.
     */
    virtual void stylizeButtons();

    /**
     * @brief For the QLabels and their subclass objects
     * declared in this class, their properties are chosen inside
     * this method.
     */
    virtual void stylizeLabels();

    /**
     * @brief For the QFrames and their subclass objects
     * declared in this class, their properties are chosen inside
     * this method.
     */
    void stylizeFrames() const;

    /**
     * @brief For any Animation class and their subclass objects
     * declared in this class, their properties are chosen inside
     * this method.
     */
    virtual void customizeAnimationBehaviors();

    /**
     * @brief UI styles for this class is defined inside this method.
     */
    void createStyle();

    /**
     * Builds connections with UI elements with actionable methods.
     */
    virtual void establishConnections();

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
     * @brief Sends the current text from text label to the TextManagerInterface.
     * Establish connection with textEditedSignal of TextManagerInterface
     * with editTextReceivedAction.
     */
    virtual void editButtonClicked() = 0;

    /**
     * @brief This method is used by this class and its child widgets
     * to use QWidget Objects declare in the class and create UI tree
     * with them.
     */
    virtual void construct();

public:
    ItemWidget();

    /**
     *
     * @param fWidth Initial width value for this widget
     * @param fHeight Initial height value for this widget
     * @brief By using this method the user is animating
     * current widget from size (0, 0) to size(fWidth, fHeight).
     * For this animation the widget will take 500 millisecond time.
     */
    virtual void popUpAnimation(int fWidth, int fHeight);
};