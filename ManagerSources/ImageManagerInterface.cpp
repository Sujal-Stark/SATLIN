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
    /*
     * Accepts a valid QImage(const reference) and store it's thumbnail
     * as QLabel object in Thumbnail container. This single method is
     * responsible for all necessary operations to access a new QLabel object
     * which can be directly used in UI. Throws invalid_argument exception if
     * const QImage& qImage or const QString& currentHash is null.
     */
    if (qImage.isNull())throw std::invalid_argument(
        "const QImage &qImage is null"
    );

    if (currentHash.isNull())throw std::invalid_argument(
        "const QString& currentHash is null"
    );

    QPointer<QLabel> imageLabel = this->createPixmapLabel(currentHash, qImage);
    this->addThumbnailToMap(imageLabel, currentHash);
}

void ImageManagerInterface::setInputImage(const string& path) {
    /*
     * Accepts a valid file path(const reference) and store it's thumbnail
     * as QLabel object in Thumbnail container. This single method is
     * responsible for all necessary operations to access a new QLabel object
     *  which can be directly used in UI. Throws invalid_argument exception
     *  if const string& path is null.
     */

    if (path.empty())throw std::invalid_argument(
        "const string& path is null"
    );

    const QString filePath = QString::fromStdString(path);
    QPointer<QLabel> imageLabel = this->createPixmapLabel(filePath, QPixmap(filePath));
    this->addThumbnailToMap(imageLabel, qHash(filePath));
}

QPointer<QLabel> ImageManagerInterface::getPixmapLabel(const QString& imageHash) {
    /*
     * given a valid hash code (const QString&) this method provides
     * corresponding QPointer<QLabel> Object. If given hash value is a null ptr then
     * an invalid_argument exception is thrown.
     */

    if (imageHash.isNull())throw std::invalid_argument(
        "Provided Hash value is Null."
    );

    if (!this->thumbnailContainer.empty() && this->thumbnailContainer.contains(imageHash)) {
        return this->thumbnailContainer.at(imageHash);
    }

    return  nullptr;
}

QPointer<QLabel> ImageManagerInterface::getPixmapLabel(const size_t imageHash) {
    /*
     * given a valid hash code (const size_t&) this method provides The QLabel* Object.
     * User can use the label after dereferencing the pointer.
     */

    if (
        pathBasedThumbnailCollector.empty() &&
        this->pathBasedThumbnailCollector.contains(imageHash)
    )return this->pathBasedThumbnailCollector.at(imageHash);

    return nullptr;
}

QPointer<QLabel> ImageManagerInterface::createLabel(const QPixmap &pixmap) {
    /*
     * Creates The ImageLabel, sets pixmap object to it and manages Label's
     * Styles.
     */
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
    /*
     * Generates a thumbnail for the image(cheap copy of the content) and creates
     *  a label for it. Also stores the original QImage(Original Content)
     *  as a unique_ptr<QImage>.
     */

    this->storeImageObject(image, hash);// Stores QImage objects for saving purposes

    const QPixmap currentPixmap = generateThumbnail(image);
    QLabel* label =  createLabel(currentPixmap);

    // defines how to access Image Object from QLabel
    label->setProperty(Constants::MODE, IMAGE_ACCESS_VIA_COPY);
    label->setProperty(Constants::OBJECT_HASH_KEY, hash);

    return label;
}

QPointer<QLabel> ImageManagerInterface::createPixmapLabel(const QString &path, const QPixmap& pixmap) {
    /*
     * Generates a thumbnail(cheap copy) for the image and creates a label for it.
     * Also stores the original Path(File path) as a unique_ptr<QString>.
     */

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
    /*
     * Given a const QImage, This method reduces the size to imageWidget's
     * required size, and returns the reduced one.
     */

    QPixmap pixmap = QPixmap::fromImage(qImage);
    return pixmap.scaled(
        Constants::IMAGE_THUMBNAIL_WIDTH, Constants::IMAGE_THUMBNAIL_HEIGHT,
        Qt::AspectRatioMode::KeepAspectRatio
    ); // Object is implicitly moved. Not Copied
}

QPixmap ImageManagerInterface::generateThumbnail(const QPixmap& pixmap) {
    /*
     * Given a const QPixmap, This method reduces the size to imageWidget's
     * required size, and returns the reduced one.
     */

    return pixmap.scaled(
        Constants::IMAGE_THUMBNAIL_WIDTH, Constants::IMAGE_THUMBNAIL_HEIGHT,
        Qt::AspectRatioMode::KeepAspectRatio
    ); // Object is implicitly moved. Not Copied
}

void ImageManagerInterface::removeCopyItem(const QString &imageHash) {
    /*
     * Deletes pointers from thumbnailContainer & qImageHashSet with the given key.
     * QPointer removes QLabel's reference, unique_ptr removes qImage object safely.
     */

    this->thumbnailContainer.erase(imageHash);
    this->qImageHashSet.erase(imageHash);
}

void ImageManagerInterface::removePathItem(const size_t imageHash) {
    /*
     * Deletes pointers from pathBasedThumbnailCollector & imagePathSet with the given key.
     * QPointer removes QLabel's reference, unique_ptr removes path object safely.
     */

    this->pathBasedThumbnailCollector.erase(imageHash);
    this->imagePathSet.erase(imageHash);
}

void ImageManagerInterface::saveActionPerformed(const QString &imageHash) {
    /*
     * Selects directory, file name for the image to be saved.
     * and saved using QPixmap save method.
     */
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
    /*
     * Check's if the hash corresponding to pixmap already exists or not.
     * If not then stores the QImage File.
     */

    if (!this->qImageHashSet.contains(hash)) {
        this->qImageHashSet[hash] = make_unique<QImage>(image);
    }
}

void ImageManagerInterface::storeFilePath(const QString &path) {
    /*
     * Check's if the hash corresponding to filePath already exists or not.
     * If not then stores the File Path.
     */

    size_t hash = qHash(path);

    if (!this->imagePathSet.contains(hash)) {
        this->imagePathSet[hash] = make_unique<QString>(path);
    }
}

