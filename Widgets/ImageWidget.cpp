//
// Created by sujal-stark on 2/18/26.
//

#include "ImageWidget.h"
#include "../Util/Constants.h"

ImageWidget::ImageWidget() {
    this->setLayout(this->masterLayout);
    this->setFixedWidth(Constants::ITEM_WIDGET_WIDTH);
    this->stylizeButtons();
    this->stylizeFrames();
    this->construct();
    this->establishConnections();
    this->stylize();
};

void ImageWidget::establishConnections() {
    connect(
        this->deleteButton, &QPushButton::clicked,
        this, &ImageWidget::deleteButtonClicked
    );
    connect(
        this->saveButton, &QPushButton::clicked,
        this, &ImageWidget::saveButtonClicked
    );
    connect(
        this->editButton, &QPushButton::clicked,
        this, &ImageWidget::editButtonClicked
    );
}

void ImageWidget::stylizeButtons() const {
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

void ImageWidget::stylizeFrames() const {
    this->mainFrame->setFixedWidth(
        Constants::ITEM_MAIN_FRAME_WIDTH
    );
}

void ImageWidget::construct() const {
    this->masterLayout->addWidget(this->mainFrame, Qt::AlignmentFlag::AlignCenter);
    this->mainFrame->setLayout(this->masterInnerLayout);

    this->masterInnerLayout->addLayout(this->contentHolder);
    this->contentHolder->addStretch();

    this->masterInnerLayout->addLayout(this->buttonHolder);
    this->buttonHolder->setSpacing(10);
    this->buttonHolder->addStretch();
    this->buttonHolder->addWidget(this->deleteButton, Qt::AlignmentFlag::AlignRight);
    this->buttonHolder->addWidget(this->editButton, Qt::AlignmentFlag::AlignRight);
    this->buttonHolder->addWidget(this->saveButton, Qt::AlignmentFlag::AlignRight);
}

// Widget Internal operations
void ImageWidget::assignImage(const QString& path, const QString& imageHash, const int mode) {
    this->imageLabel = ImageManagerInterface::getImageLabel(path, imageHash, mode);

    if (this->imageLabel != nullptr) {
        this->imageLabel->show();
        this->contentHolder->addWidget(
            this->imageLabel, Qt::AlignmentFlag::AlignCenter
        );
    }
}

void ImageWidget::assignDrivers(const shared_ptr<ImageManagerInterface>& interface) {
    if (interface == nullptr)throw invalid_argument("Invalid Drivers.");
    this->imageManagerInterface = interface;
}

// Defining Actions
void ImageWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::MouseButton::LeftButton) {
        const QImage img = this->imageManagerInterface->releaseImageData(
            this->imageLabel->property(Constants::SHA_STRING_KEY).toString()
        );
        if (!img.isNull())emit this->imageItemClickedSignal(img);
    }

    // changes the label color
    this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(54, 54, 54, 150);"
    );
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event) {
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
}

void ImageWidget::deleteButtonClicked() {
    const QString hash = this->imageLabel->property(Constants::SHA_STRING_KEY).toString();
    if (
        const QString filePath = this->imageManagerInterface->getImageFileName(hash);
        this->imageManagerInterface->removeImageItem(hash) && !filePath.isEmpty()
    )emit this->imageRemovedConfirmation(
        hash, filePath, this->imageLabel->property(Constants::MODE).toInt()
    );
    else qWarning()<<"Image Deletion failed";

    this->deleteLater(); // self-destruction of widget
}

void ImageWidget::saveButtonClicked() const {
    this->imageManagerInterface->saveActionPerformed(
        this->imageLabel->property(Constants::SHA_STRING_KEY).toString(),
        this->imageLabel->property(Constants::MODE).toInt()
    );
}

void ImageWidget::editButtonClicked() const {
    /* Image Editing will be introduced later.*/

    qDebug()<<this->imageLabel->text();
}

void ImageWidget::stylize() {
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
}
