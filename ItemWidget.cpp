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
        this->textItemClickedSignal(this->text().toStdString());
    }
}
