//
// Created by sujal-stark on 7/26/26.
//

#include "RegularButton.h"

RegularButton::RegularButton() {
    this->customizeAnimationBehavior();
    this->customizeWidget();
}

RegularButton::RegularButton(QWidget *parent) : QPushButton(parent) {
    this->customizeAnimationBehavior();
    this->customizeWidget();
}

RegularButton::RegularButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent){
    this->customizeAnimationBehavior();
    this->customizeWidget();
}

void RegularButton::customizeWidget() {
    QSizePolicy pol = this->sizePolicy();
    pol.setHorizontalPolicy(QSizePolicy::Maximum);
    pol.setVerticalPolicy(QSizePolicy::Maximum);
    this->setSizePolicy(pol);
}

void RegularButton::customizeAnimationBehavior() const {
    this->resizeOnHover->setDuration(100);
}

void RegularButton::setSizeHint(const int width, const int height) {
    if (width < 0 || height < 0)throw std::invalid_argument(
        "Invalid arguments are given"
    );

    this->SIZE_HINT = QSize(width, height);
}

QSize RegularButton::sizeHint() const {
    return this->SIZE_HINT;
}

void RegularButton::setResizeHoverAnimationParameters(
    const int maxWidth, const int maxHeight,
    const int minWidth, const int minHeight
) {
    if (
        maxWidth < 0 || maxHeight < 0 ||
        minWidth < 0 || minHeight < 0 ||
        minWidth <= maxWidth || minHeight <= maxHeight
    )throw std::invalid_argument("invalid size given");

    this->MAX_SIZE = QSize(maxWidth, maxHeight);
    this->MIN_SIZE = QSize(minWidth, minHeight);
}

void RegularButton::enterEvent(QEnterEvent *event) {
    this->resizeOnHover->setEndValue(this->MAX_SIZE);
    this->resizeOnHover->start();
}

void RegularButton::leaveEvent(QEvent *event) {
    this->resizeOnHover->setEndValue(this->MIN_SIZE);
    this->resizeOnHover->start();
}
