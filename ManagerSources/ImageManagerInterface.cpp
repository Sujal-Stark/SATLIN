//
// Created by sujal-stark on 11/5/25.
//

#include <QCryptographicHash>
#include <utility>

#include "ImageManagerInterface.h"
#include "../Util/Constants.h"

ImageManagerInterface::ImageManagerInterface() = default;

void ImageManagerInterface::setInputImage(const QImage &qImage, QString currentHash) {
    this->currentImage = qImage;
    this->currentHash = std::move(currentHash);
    this->addImageToMap();
}

QLabel *ImageManagerInterface::getCurrentPixmapLabel() {
    /*
     * Returns the current HashMap Object if the hash is valid
     */
    return !this->hashImage.empty()? this->hashImage[this->currentHash] : nullptr;
}


QLabel *ImageManagerInterface::createPixmapLabel() const {
    /*
     * Generates a thumbnail for the image and if the image is new then create a label for it
     */
    const QImage thumbnailImage = generateThumbnail(currentImage);

    // Redundancy Checking
    const QPixmap currentPixmap = QPixmap::fromImage(thumbnailImage);
    auto *imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    imageLabel->setContentsMargins(5, 5, 5, 5);
    imageLabel->setFixedSize(Constants::TEXT_CARD_WIDTH, currentPixmap.height() + 5);
    imageLabel->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(145, 191, 250, 0);"
        );
    imageLabel->setPixmap(currentPixmap);

    return imageLabel; // Returning output pixmap
}

void ImageManagerInterface::addImageToMap() {
    /*
     * Adds the new PixMapLabel to the Hash if it's new.
     */
    QLabel *pixLabel = this->createPixmapLabel();
    this->hashImage[currentHash] = pixLabel;
}

QImage ImageManagerInterface::generateThumbnail(const QImage &qImage) {
    // Expects Not Null Image
    return qImage.scaled(
        Constants::IMAGE_THUMBNAIL_WIDTH, Constants::IMAGE_THUMBNAIL_HEIGHT,
        Qt::AspectRatioMode::KeepAspectRatio
    );
}

bool ImageManagerInterface::removeItem(const QString &imageHash) {
    /*
     * Takes out the reference of the QLabel and delete with its content
     */
    if (this->hashImage.contains(imageHash)) {
        QLabel *imageLabel = this->hashImage[imageHash];
        this->hashImage.erase(imageHash);
        imageLabel->clear(); // removes the pixmap as well
        imageLabel->deleteLater(); // delete the label as well
        return  true;
    }
    return  false; // if the hash value doesn't exist
}

