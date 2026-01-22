//
// Created by sujal-stark on 12/29/25.
//

#include "EmojiWidget.h"

EmojiWidget::EmojiWidget(const QString &text, QWidget *parent) {
    this->setText(text);
    this->setParent(parent);
    this->show();
}


