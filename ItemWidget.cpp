//
// Created by sujal-stark on 9/22/25.
//

#include "ItemWidget.h"
#include<Qt>
#include<QPixmap>
#include<iostream>
#include <utility>

#include "Constants.h"

using namespace std;

ItemWidget::ItemWidget() = default;

void ItemWidget::assignProperties() {
    /*
     * Default properties related to this widget will be added here. It will only hold common properties
     * for all types of media
     */
    this->setLayout(this->masterLayout);
    this->setFixedWidth(Constants::ITEM_WIDGET_WIDTH); // for constant width
}

void ItemWidget::setTextManagerInterfaceInput(TextManagerInterface *interface) {
    this->text_manager_interface = interface;
}

void ItemWidget::setImageManagerInterfaceInput(ImageManagerInterface *interface) {
    this->image_manager_interface = interface;
}

void ItemWidget::assignText(const QString &text, const size_t textHash) {
    this->assignProperties();

    this->text_manager_interface->setInputText(text, textHash);
    this->image_Text_HolderLabel = this->text_manager_interface->getCurrentCopiedText();

    if (this->image_Text_HolderLabel != nullptr) {
        this->image_Text_HolderLabel->show();
        this->masterLayout->addWidget(this->image_Text_HolderLabel, Qt::AlignmentFlag::AlignCenter);
    }
}

void ItemWidget::assignImage(const QImage &image, QString imageHash) {
    this->assignProperties();

    this->image_manager_interface->setInputImage(image, std::move(imageHash)); // ref
    this->image_Text_HolderLabel = this->image_manager_interface->getCurrentPixmapLabel();

    if (image_Text_HolderLabel != nullptr) {
        this->image_Text_HolderLabel->show();
        this->masterLayout->addWidget(this->image_Text_HolderLabel, Qt::AlignmentFlag::AlignCenter);
    }

}

void ItemWidget::mousePressEvent(QMouseEvent *event){
    // identifies the content of item and then send it as signal
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (OBJECT_RECOGNITION_FLAG_ARRAY[Constants::TEXT_SIGNAL_INDEX]) {
            emit this->textItemClickedSignal(this->image_Text_HolderLabel->text());
            OBJECT_RECOGNITION_FLAG_ARRAY[Constants::TEXT_SIGNAL_INDEX] = false; // reset
        }
        else if (OBJECT_RECOGNITION_FLAG_ARRAY[Constants::IMAGE_SIGNAL_INDEX]) {
            emit this->imageItemClickedSignal(this->image_Text_HolderLabel->pixmap());
            OBJECT_RECOGNITION_FLAG_ARRAY[Constants::IMAGE_SIGNAL_INDEX] = false; // reset
        }
    }

    // changes the label color
    this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(145, 191, 250, 20);"
    );
}

void ItemWidget::mouseReleaseEvent(QMouseEvent *event) {
    // revert the color changes due to mouse press
    this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(145, 191, 250, 0);"
    );
    OBJECT_RECOGNITION_FLAG_ARRAY[OBJECT_RECOGNITION_FLAG_INDEX] = true; // set
}

void ItemWidget::setObjectType(const int objectFlag) {
    OBJECT_RECOGNITION_FLAG_ARRAY[objectFlag] = true; // set
    OBJECT_RECOGNITION_FLAG_INDEX = objectFlag;
}


