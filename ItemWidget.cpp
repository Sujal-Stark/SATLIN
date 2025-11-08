//
// Created by sujal-stark on 9/22/25.
//

#include "ItemWidget.h"
#include<Qt>
#include<QPixmap>
#include<iostream>

#include "Constants.h"

using namespace std;

void ItemWidget::mousePressEvent(QMouseEvent *event){
    // identifies the content of item and then send it as signal
    if (event->button() == Qt::MouseButton::LeftButton) {
        if (OBJECT_RECOGNITION_FLAG_ARRAY[Constants::TEXT_SIGNAL_INDEX]) {
            emit this->textItemClickedSignal(this->text().toStdString());
            OBJECT_RECOGNITION_FLAG_ARRAY[Constants::TEXT_SIGNAL_INDEX] = false; // reset
        }
        else if (OBJECT_RECOGNITION_FLAG_ARRAY[Constants::IMAGE_SIGNAL_INDEX]) {
            emit this->imageItemClickedSignal(this->pixmap());
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


