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
        // Redundancy Checking
        if(
            const QString hash = getImageObjectHash(this->copiedImage);
            !this->hashImage.contains(hash)
        ) {
            this->hashImage.insert(hash);

            // Object Creation
            const QPixmap currentPixmap = QPixmap::fromImage(this->copiedImage).scaled(
                Constants::IMAGE_THUMBNAIL_WIDTH,
                Constants::IMAGE_THUMBNAIL_HEIGHT,
                Qt::AspectRatioMode::KeepAspectRatio
            );

            auto *pixmapLabel = new ItemWidget(""); // Label Creation
            pixmapLabel->setFixedSize(Constants::TEXT_CARD_WIDTH, currentPixmap.height() + 5);
            pixmapLabel->setContentsMargins(5, 5, 5, 5);
            pixmapLabel->setAlignment(Qt::AlignmentFlag::AlignVCenter);
            pixmapLabel->setStyleSheet(
                "border: 1px solid white;"
                "border-radius: 5px;"
                "background-color: rgba(145, 191, 250, 0);"
            );
            pixmapLabel->hide();
            pixmapLabel->setPixmap(currentPixmap);

            pixmapLabel->setObjectType(Constants::IMAGE_SIGNAL_INDEX); // setting flag
            return pixmapLabel; // Returning output pixmap
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
    const QByteArray dataStream(
        reinterpret_cast<const char *>(qImage.bits()), qImage.sizeInBytes()
    );
    const QByteArray hashCode = QCryptographicHash::hash(
        dataStream, QCryptographicHash::Md4
    );
    return QString::fromUtf8(hashCode.toHex());
}
