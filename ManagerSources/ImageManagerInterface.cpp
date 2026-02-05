//
// Created by sujal-stark on 11/5/25.
//

#include <utility>
#include <QFileDialog>

#include "ImageManagerInterface.h"
#include "../Util/Constants.h"

ImageManagerInterface::ImageManagerInterface() = default;

void ImageManagerInterface::setInputImage(const QImage &qImage, QString currentHash) {
    this->currentImage = qImage;
    this->currentHash = std::move(currentHash);
    this->addThumbnailToMap();
}

QLabel *ImageManagerInterface::getCurrentPixmapLabel() {
    /*
     * Returns the current HashMap Object if the hash is valid
     */
    return !this->hashImage.empty()? this->hashImage[this->currentHash] : nullptr;
}


QLabel *ImageManagerInterface::createPixmapLabel() {
    /*
     * Generates a thumbnail for the image and if the image is new then create a label for it.
     * Also stores the original QImage as a Pixmap.
     */
    this->storePixmap(this->currentImage);
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

void ImageManagerInterface::addThumbnailToMap() {
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
     * Takes out the reference of the QLabel and delete with its content.
     * corresponding QPixmap from the qPixmapHash.
     */
    if (this->hashImage.contains(imageHash)) {
        QLabel *imageLabel = this->hashImage[imageHash];
        this->hashImage.erase(imageHash);
        imageLabel->clear(); // removes the pixmap as well
        imageLabel->deleteLater(); // delete the label as well
        if (this->qPixmapHash.contains(imageHash)) {
            this->qPixmapHash.erase(imageHash);
        }
        return  true;
    }
    return  false; // if the hash value doesn't exist
}

void ImageManagerInterface::saveActionPerformed(const QString &imageHash) {
    /*
     * Selects directory, file name for the image to be saved.
     * and saved using QPixmap save method.
     */
    if (this->qPixmapHash.contains(imageHash)) {
        QString fileName = QFileDialog::getSaveFileName(
            this, Constants::SAVE_FILE_LABEL,QDir::homePath(),
            "Images (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)"
        );

        QPixmap pixmap = *this->qPixmapHash[imageHash]; // dereferencing qPixMap
        pixmap.save(fileName); // output not required.
    }
}

void ImageManagerInterface::storePixmap(const QImage& image) {
    /*
     * Check's if the hash corresponding to pixmap already exists or not.
     * If not then stores the hash.
     */
    if (!this->qPixmapHash.contains(this->currentHash)) {
        this->qPixmapHash[this->currentHash] = make_unique<QPixmap>(
            QPixmap::fromImage(image)
        );
    }
}

