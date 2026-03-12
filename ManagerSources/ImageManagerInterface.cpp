//
// Created by sujal-stark on 11/5/25.
//

#include <utility>
#include <QFileDialog>
#include <qpointer.h>

#include "../Util/Constants.h"
#include "ImageManagerInterface.h"

ImageManagerInterface::ImageManagerInterface() = default;

void ImageManagerInterface::assignDrivers(const shared_ptr<ItemRepository> &repo) {
    if (repo == nullptr)throw invalid_argument("ItemRepository Pointer points to null");
    this->itemRepository = repo;
}

QPointer<QLabel> ImageManagerInterface::getImageLabel(
    const QString& path, const QString& currentHash, const int mode
) {
    if (path.isEmpty() || currentHash.isEmpty())throw std::invalid_argument(
        "Invalid Input Parameters."
    );

    const QPixmap pixmap = generateThumbnail(path);
    return  createPixmapLabel(pixmap, currentHash, mode);
}

QPointer<QLabel> ImageManagerInterface::createPixmapLabel(
    const QPixmap& pixmap, const QString& imageHash, const int mode
) {
    QPointer imageLabel = new QLabel();

    imageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    imageLabel->setContentsMargins(2, 2, 2, 2);
    imageLabel->setFixedSize(Constants::TEXT_CARD_WIDTH, pixmap.height() + 5);
    imageLabel->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(145, 191, 250, 0);"
        );
    imageLabel->setPixmap(pixmap);

    // Assigning properties
    imageLabel->setProperty(Constants::TEXT_HASH_KEY, imageHash);
    imageLabel->setProperty(Constants::MODE, mode);

    return imageLabel;
}

QPixmap ImageManagerInterface::generateThumbnail(const QString& filePath) {
    return QPixmap(filePath).scaled(
        Constants::IMAGE_THUMBNAIL_WIDTH, Constants::IMAGE_THUMBNAIL_HEIGHT,
        Qt::AspectRatioMode::KeepAspectRatio
    );
}

bool ImageManagerInterface::removeImageItem(const QString& imageHash) const {
    return this->itemRepository->removeImageItemHash(imageHash);
}

void ImageManagerInterface::saveActionPerformed(const QString &imageHash, const int mode) {
    if (mode == SAVE_STATUS_FALSE)return; // why remove when already exists

    const QString fileName = QFileDialog::getSaveFileName(
            this, Constants::SAVE_FILE_LABEL,QDir::homePath(),
            "Images (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)"
        );

    if (fileName.isNull())return; // User cancels saving.

    const ImageContainer *container = this->itemRepository->getImageContainer(imageHash);
    if (container == nullptr)return;

    if(
        const QPixmap pixmap = QPixmap(container->filePath);
        !pixmap.save(fileName)
    )qWarning()<<"Unable to save!!!";
}

QImage ImageManagerInterface::releaseImageData(const QString &imageHash) const {
    if (imageHash.isNull())throw invalid_argument("invalid hash value.");

    const ImageContainer* container = this->itemRepository->getImageContainer(imageHash);
    if (container == nullptr)return {};

    return QImage(container->filePath);
}

const QString &ImageManagerInterface::getImageFileName(const QString &imageHash) const {
    const ImageContainer* ctr = this->itemRepository->getImageContainer(imageHash);
    if (ctr == nullptr)return {};
    return ctr->filePath;
}
