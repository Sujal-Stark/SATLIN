//
// Created by sujal-stark on 9/22/25.
//

#include "ItemWidget.h"
#include<Qt>
#include<QPixmap>
#include<iostream>

using namespace std;

void ItemWidget::mousePressEvent(QMouseEvent *event){
    // identifies the content of item and then send it as signal
    if (event->button() == Qt::MouseButton::LeftButton) {
        emit this->textItemClickedSignal(this->text().toStdString());
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
}

