//
// Created by sujal-stark on 9/22/25.
//

#include "ItemWidget.h"
#include<Qt>
#include<QPixmap>
#include<iostream>
#include <utility>

#include "../Ui/ClipBoardUI.h"
#include "../Util/Constants.h"

using namespace std;

ItemWidget::ItemWidget() {
    /*
     * Default properties related to this widget will be added here. It will only hold common properties
     * for all types of media
     */
    this->setLayout(this->masterLayout);
    this->setFixedWidth(Constants::ITEM_WIDGET_WIDTH); // for constant width
    this->stylizeButtons();
    this->stylizeFrames();
    this->construct();
    this->establishConnections();
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
};

void ItemWidget::stylizeButtons() const {
    this->editButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->editButton->setIcon(IconManager::editIcon());

    this->deleteButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->deleteButton->setIcon(IconManager::cancelIcon());

    this->saveButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->saveButton->setIcon(IconManager::saveIcon());
}

void ItemWidget::stylizeFrames() const {
    this->mainFrame->setFixedWidth(
        Constants::ITEM_MAIN_FRAME_WIDTH
    );
}

void ItemWidget::construct() const {
    this->masterLayout->addWidget(this->mainFrame, Qt::AlignmentFlag::AlignCenter);
    this->mainFrame->setLayout(this->masterInnerLayout);

    this->masterInnerLayout->addLayout(this->contentHolder);
    this->contentHolder->addStretch();

    this->masterInnerLayout->addLayout(this->buttonHolder);
    this->buttonHolder->setSpacing(10);
    this->buttonHolder->addStretch();
    this->buttonHolder->addWidget(this->saveButton, Qt::AlignmentFlag::AlignRight);
    this->buttonHolder->addWidget(this->deleteButton, Qt::AlignmentFlag::AlignRight);
    this->buttonHolder->addWidget(this->editButton, Qt::AlignmentFlag::AlignRight);
}

void ItemWidget::establishConnections() {
    connect(
        this->deleteButton, &QPushButton::clicked,
        this, &ItemWidget::deleteButtonClicked
    );
    connect(
        this->saveButton, &QPushButton::clicked,
        this, &ItemWidget::saveButtonClicked
    );
    connect(
        this->editButton, &QPushButton::clicked,
        this, &ItemWidget::editButtonClicked
    );
}

void ItemWidget::setTextManagerInterfaceInputs(
        TextManagerInterface *interface, TextEditor *textEditor
    ) {
    this->text_manager_interface = interface;

    // Text Editor
    this->text_editor = textEditor;
    connect(
        this->text_editor, &TextEditor::textEditedSignal,
        this, &ItemWidget::textEditedSignalReceivedAction
    );
}

void ItemWidget::setImageManagerInterfaceInput(ImageManagerInterface *interface) {
    this->image_manager_interface = interface;
}

void ItemWidget::assignText(const QString &text, const size_t textHash) {
    this->OBJECT_RECOGNITION_FLAG_INDEX = Constants::TEXT_SIGNAL_INDEX;
    this->text_item_hash = textHash;

    this->text_manager_interface->setInputText(text, textHash);
    this->image_Text_HolderLabel = this->text_manager_interface->getCurrentCopiedText();

    if (this->image_Text_HolderLabel != nullptr) {
        this->image_Text_HolderLabel->show();
        this->contentHolder->addWidget(this->image_Text_HolderLabel, Qt::AlignmentFlag::AlignCenter);
    }
}

void ItemWidget::assignImage(const QImage &image, QString imageHash) {
    this->OBJECT_RECOGNITION_FLAG_INDEX = Constants::IMAGE_SIGNAL_INDEX;
    this->image_item_Hash = imageHash;

    this->image_manager_interface->setInputImage(image, std::move(imageHash)); // ref
    this->image_Text_HolderLabel = this->image_manager_interface->getCurrentPixmapLabel();

    if (image_Text_HolderLabel != nullptr) {
        this->image_Text_HolderLabel->show();
        this->contentHolder->addWidget(this->image_Text_HolderLabel, Qt::AlignmentFlag::AlignCenter);
    }

}

void ItemWidget::mousePressEvent(QMouseEvent *event){
    // identifies the content of item and then send it as signal
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (this->OBJECT_RECOGNITION_FLAG_INDEX == Constants::TEXT_SIGNAL_INDEX) {
            emit this->textItemClickedSignal(this->image_Text_HolderLabel->text());
        }
        else if (this->OBJECT_RECOGNITION_FLAG_INDEX == Constants::IMAGE_SIGNAL_INDEX) {
            emit this->imageItemClickedSignal(this->image_Text_HolderLabel->pixmap());
        }
    }

    // changes the label color
    this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(54, 54, 54, 150);"
    );
}

void ItemWidget::mouseReleaseEvent(QMouseEvent *event) {
    // revert the color changes due to mouse press
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
}

void ItemWidget::deleteButtonClicked() {
    if (this->OBJECT_RECOGNITION_FLAG_INDEX == Constants::TEXT_SIGNAL_INDEX) {
        this->text_manager_interface->removeItem(this->text_item_hash);
        emit this->text_Hash_Removal_Request_Signal(this->text_item_hash);
        this->deleteLater();
    }else if (this->OBJECT_RECOGNITION_FLAG_INDEX == Constants::IMAGE_SIGNAL_INDEX) {
        this->image_manager_interface->removeItem(this->image_item_Hash);
        emit this->image_Hash_Removal_Request_Signal(this->image_item_Hash);
        this->deleteLater();
    }else if (this->OBJECT_RECOGNITION_FLAG_INDEX == Constants::VIDEO_SIGNAL_INDEX) {

    }else if (this->OBJECT_RECOGNITION_FLAG_INDEX == Constants::AUDIO_SIGNAL_INDEX) {

    }
}

void ItemWidget::saveButtonClicked() const {
    if (this->OBJECT_RECOGNITION_FLAG_INDEX == Constants::TEXT_SIGNAL_INDEX) {
        const QString text = this->image_Text_HolderLabel->text();
        this->text_editor->receiveText(text, 0); // 0 -> save Action
        this->text_editor->show();
    }
}

void ItemWidget::editButtonClicked() const {
    if (this->OBJECT_RECOGNITION_FLAG_INDEX == Constants::TEXT_SIGNAL_INDEX) {
        const QString text = this->image_Text_HolderLabel->text();
        this->text_editor->receiveText(text, 1); // 1 -> edit operation
        this->text_editor->show();
    }
}

void ItemWidget::textEditedSignalReceivedAction(const QSharedPointer<QString>& editedText) {
    /*
     * Receives edited Text(AS a QSharedPointer) and send it to the Text manager interface.
     */
    size_t nextHash = qHash(*editedText);

    if (
        this->text_manager_interface->receiveTextForSwapping(
            editedText, this->text_item_hash, nextHash
        )
    ) {
        this->textHashReplacementSignal(this->text_item_hash, nextHash);
        this->text_item_hash = nextHash;
        emit textItemClickedSignal(this->image_Text_HolderLabel->text());
        this->update();
    }
}