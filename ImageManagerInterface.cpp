//
// Created by sujal-stark on 11/5/25.
//

#include <QCryptographicHash>

#include "ImageManagerInterface.h"
#include "Constants.h"

void ImageManagerInterface::setCopiedImage(const QImage &qImage) {
    this->copiedImage = qImage;
}

ItemWidget *ImageManagerInterface::getPixmap() const {
    return !imageQueue.empty()? imageQueue.back() : nullptr;
}


ItemWidget *ImageManagerInterface::createPixmapLabel() {
    if (!this->copiedImage.isNull()) {
        const QImage thumbnailImage = generateThumbnail(copiedImage);
        // Redundancy Checking
        if(
            const QString hash = getImageObjectHash(thumbnailImage);
            !this->hashImage.contains(hash)
        ) {
            this->hashImage[hash] = new QImage(this->copiedImage);

            // Object Creation
            const QPixmap currentPixmap = QPixmap::fromImage(thumbnailImage);
            auto *imageItemWidget = new ItemWidget(currentPixmap);
            auto *pixmapLabel = imageItemWidget->getImageHolder(); // Label Creation
            pixmapLabel->setStyleSheet(
                "border: 1px solid white;"
                "border-radius: 5px;"
                "background-color: rgba(145, 191, 250, 0);"
            );
            pixmapLabel->show();
            imageItemWidget->setObjectType(Constants::IMAGE_SIGNAL_INDEX); // setting flag
            return imageItemWidget; // Returning output pixmap
        }
    }
    return nullptr;
}

void ImageManagerInterface::addImageToQueue() {
    if (
        const auto pixmap = this->createPixmapLabel();
        pixmap != nullptr
    )this->imageQueue.push(pixmap);
}

QString ImageManagerInterface::getImageObjectHash(const QImage &qImage) {
    const uint hash = qHashBits(qImage.bits(), qImage.sizeInBytes());
    return QString::number(hash, 16);
}

QImage ImageManagerInterface::generateThumbnail(const QImage &qImage) {
    // Expects Not Null Image
    return qImage.scaled(
        Constants::IMAGE_THUMBNAIL_WIDTH, Constants::IMAGE_THUMBNAIL_HEIGHT,
        Qt::AspectRatioMode::KeepAspectRatio
    );
}

