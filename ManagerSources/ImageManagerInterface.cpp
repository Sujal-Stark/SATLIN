//
// Created by sujal-stark on 11/5/25.
//

#include <utility>
#include <QFileDialog>
#include <qpointer.h>

#include "../Util/Constants.h"
#include "ImageManagerInterface.h"

ImageManagerInterface::ImageManagerInterface() = default;

void ImageManagerInterface::setInputImage(const QImage &qImage, const QString& currentHash) {
    if (qImage.isNull())throw std::invalid_argument(
        "const QImage &qImage is null"
    );

    if (currentHash.isNull())throw std::invalid_argument(
        "const QString& currentHash is null"
    );

    QPointer<QLabel> imageLabel = this->createPixmapLabel(currentHash, qImage);
    this->addThumbnailToMap(imageLabel, currentHash);
}

void ImageManagerInterface::setInputImage(const QString& path) {
    if (path.isNull())throw std::invalid_argument(
        "const string& path is null"
    );

    QPointer<QLabel> imageLabel = this->createPixmapLabel(path, QPixmap(path));
    this->addThumbnailToMap(imageLabel, qHash(path));
}

QPointer<QLabel> ImageManagerInterface::getPixmapLabel(const QString& imageHash) {
    if (imageHash.isNull())throw std::invalid_argument(
        "Provided Hash value is Null."
    );

    if (!this->thumbnailContainer.empty() && this->thumbnailContainer.contains(imageHash)) {
        return this->thumbnailContainer.at(imageHash);
    }

    return  nullptr;
}

QPointer<QLabel> ImageManagerInterface::getPixmapLabel(const size_t imageHash) {
    if (
        !pathBasedThumbnailCollector.empty() &&
        this->pathBasedThumbnailCollector.contains(imageHash)
    ) {
        return this->pathBasedThumbnailCollector.at(imageHash);
    }

    return nullptr;
}

QPointer<QLabel> ImageManagerInterface::createLabel(const QPixmap &pixmap) {
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

    return imageLabel;
}

QPointer<QLabel> ImageManagerInterface::createPixmapLabel(const QString& hash, const QImage& image) {
    this->storeImageObject(image, hash);// Stores QImage objects for saving purposes

    const QPixmap currentPixmap = generateThumbnail(image);
    QPointer<QLabel> label =  createLabel(currentPixmap);
    // defines how to access Image Object from QLabel
    label->setProperty(Constants::MODE, IMAGE_ACCESS_VIA_COPY);
    label->setProperty(Constants::OBJECT_HASH_KEY, hash);

    return label;
}

QPointer<QLabel> ImageManagerInterface::createPixmapLabel(const QString &path, const QPixmap& pixmap) {
    this->storeFilePath(path); // Stores file path for saving purposes

    const QPixmap currentPixmap = generateThumbnail(pixmap);
    QPointer label = createLabel(currentPixmap);

    // defines how to access Image Object from QLabel
    label->setProperty(Constants::MODE, IMAGE_ACCESS_VIA_PATH);
    label->setProperty(Constants::TEXT_HASH_KEY, QVariant::fromValue(qHash(path)));

    return label;
}

void ImageManagerInterface::addThumbnailToMap(
        const QPointer<QLabel> &pixmapLabel, const QString& currentHash
    ) {
    /*Adds the new PixMapLabel to the Hash if it's new.*/

    this->thumbnailContainer[currentHash] = pixmapLabel;
}

void ImageManagerInterface::addThumbnailToMap(
        const QPointer<QLabel> &pixmapLabel, const size_t currentHash
    ) {
    /* Adds the new PixMapLabel to the Hash if it's new.*/

    this->pathBasedThumbnailCollector[currentHash] = pixmapLabel;
}

QPixmap ImageManagerInterface::generateThumbnail(const QImage &qImage) {
    QPixmap pixmap = QPixmap::fromImage(qImage);
    return pixmap.scaled(
        Constants::IMAGE_THUMBNAIL_WIDTH, Constants::IMAGE_THUMBNAIL_HEIGHT,
        Qt::AspectRatioMode::KeepAspectRatio
    ); // Object is implicitly moved. Not Copied
}

QPixmap ImageManagerInterface::generateThumbnail(const QPixmap& pixmap) {
    return pixmap.scaled(
        Constants::IMAGE_THUMBNAIL_WIDTH, Constants::IMAGE_THUMBNAIL_HEIGHT,
        Qt::AspectRatioMode::KeepAspectRatio
    ); // Object is implicitly moved. Not Copied
}

void ImageManagerInterface::removeCopyItem(const QString &imageHash) {
    this->thumbnailContainer.erase(imageHash);
    this->qImageHashSet.erase(imageHash);
}

void ImageManagerInterface::removePathItem(const size_t imageHash) {
    this->pathBasedThumbnailCollector.erase(imageHash);
    this->imagePathSet.erase(imageHash);
}

void ImageManagerInterface::saveActionPerformed(const QString &imageHash) {
    if (this->qImageHashSet.contains(imageHash)) {
        const QString fileName = QFileDialog::getSaveFileName(
            this, Constants::SAVE_FILE_LABEL,QDir::homePath(),
            "Images (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)"
        );

        if (fileName.isNull())return; // User cancel's saving.

        QPixmap pixmap = QPixmap::fromImage(*this->qImageHashSet[imageHash]);

        if(!pixmap.save(fileName)) {
            qWarning()<<"Unable to save!!!";
        }
    }
}

void ImageManagerInterface::storeImageObject(const QImage& image, const QString& hash) {
    if (!this->qImageHashSet.contains(hash)) {
        this->qImageHashSet[hash] = make_unique<QImage>(image);
    }
}

void ImageManagerInterface::storeFilePath(const QString &path) {
    size_t hash = qHash(path);

    if (!this->imagePathSet.contains(hash)) {
        this->imagePathSet[hash] = make_unique<QString>(path);
    }
}

QImage ImageManagerInterface::releaseImageData(const QString &imageHash) const {
    if (imageHash.isNull())throw invalid_argument("Not a valid hash.");

    if (this->qImageHashSet.contains(imageHash)) {
        return *this->qImageHashSet.at(imageHash).get();
    }

    return {};
}

QImage ImageManagerInterface::releaseImageData(const size_t imageHash) const {
    if (this->imagePathSet.contains(imageHash))return  QImage(
        *this->imagePathSet.at(imageHash).get()
    );

    return {};
}
