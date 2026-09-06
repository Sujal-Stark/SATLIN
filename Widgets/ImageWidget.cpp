//
// Created by sujal-stark on 2/18/26.
//

#include "ImageWidget.h"
#include "../Util/Constants.h"

ImageWidget::ImageWidget() {
    ItemWidget::construct();
    ItemWidget::establishConnections();
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

    this->imageManagerInterface->populateInfoLabels(
        imageHash, this->extensionCard, this->sizeCard,
        this->timeStampCard, this->saveButton
    );
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
    /*this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(54, 54, 54, 150);"
    );*/
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *event) {
    /*this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );*/
}

void ImageWidget::deleteButtonClicked() {
    const QString hash = this->imageLabel->property(Constants::SHA_STRING_KEY).toString();
    if (
        const QString filePath = this->imageManagerInterface->getImageFileName(hash);
        this->imageManagerInterface->removeItem(hash) && !filePath.isEmpty()
    )emit this->imageRemovedConfirmation(
        hash, filePath, this->imageLabel->property(Constants::MODE).toInt()
    );
    else qWarning()<<"Image Deletion failed";

    this->deleteLater(); // self-destruction of widget
}

void ImageWidget::saveButtonClicked() {
    if (imageLabel->property(Constants::MODE) == 0) return;

    if(
        QString hash = this->imageLabel->property(Constants::SHA_STRING_KEY).toString(); this->imageManagerInterface->saveActionPerformed(hash)
    ) {
        this->imageLabel->setProperty(Constants::MODE, 0);
        this->imageManagerInterface->populateInfoLabels(
            hash, this->extensionCard, this->sizeCard, this->timeStampCard, this->saveButton
        );
    }
}

void ImageWidget::editButtonClicked() {
    /* Image Editing will be introduced later.*/

    qDebug()<<this->imageLabel->text();
}