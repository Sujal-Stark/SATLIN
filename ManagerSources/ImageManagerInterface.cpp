//
// Created by sujal-stark on 11/5/25.
//

#include <utility>
#include <QFileDialog>
#include <qpointer.h>
#include <ranges>

#include "../Util/Constants.h"
#include "ImageManagerInterface.h"
#include "../Util/ToolKit.h"

ImageManagerInterface::ImageManagerInterface() = default;

void ImageManagerInterface::establishConnections() {
    // This method is not used for now.
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
    imageLabel->setFixedSize(Constants::TEXT_CARD_WIDTH, Constants::IMAGE_CARD_HEIGHT);

    imageLabel->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(145, 191, 250, 0);"
        );
    imageLabel->setPixmap(pixmap);

    // Assigning properties
    imageLabel->setProperty(Constants::SHA_STRING_KEY, imageHash);
    imageLabel->setProperty(Constants::MODE, mode);

    return imageLabel;
}

QPixmap ImageManagerInterface::generateThumbnail(const QString& filePath) {
    return QPixmap(filePath).scaled(
        Constants::TEXT_CARD_WIDTH - 20, Constants::IMAGE_CARD_HEIGHT - 20,
        Qt::AspectRatioMode::KeepAspectRatio
    );
}

bool ImageManagerInterface::removeItem(const QString& hash) const {
    return this->itemRepository->removeImageItemHash(hash);
}

bool ImageManagerInterface::saveActionPerformed(const QString &imageHash) {
    const std::optional<ImageContainer*> obj = this->itemRepository->getImageContainer(imageHash);
    if (!obj.has_value())return false;

    ImageContainer* container = obj.value();

    const QString fileName = QFileDialog::getSaveFileName(
        this, Constants::SAVE_FILE_LABEL, QDir::homePath(),
        "Images (*.png *.jpg *.jpeg *.bmp *.gif);;All Files (*)"
        );

    if (fileName.isNull())return false; // User cancels saving.

    const std::string file = fileName.toStdString();

    const std::filesystem::path filePath(file);
    const QString currentFilePath = container->filePath;

    if (filePath.extension() == Constants::PNG) {
        filesystem::rename(currentFilePath.toStdString(), file);
    }else {
        if (
            const QPixmap pixmap = QPixmap(currentFilePath);
            pixmap.isNull() || !pixmap.save(fileName)
        )return false;
    }

    container->filePath = fileName;
    container->saveStatus = SAVE_STATUS_TRUE;
    container->fileSize = ToolKit::getFileSize(fileName);
    return true;
}

QImage ImageManagerInterface::releaseImageData(const QString &imageHash) const {
    if (imageHash.isNull())throw invalid_argument("invalid hash value.");

    const std::optional<ImageContainer*> container = this->itemRepository->getImageContainer(imageHash);
    if (!container.has_value())return {};

    return QImage(container.value()->filePath);
}

const QString &ImageManagerInterface::getImageFileName(const QString &imageHash) const {
    const std::optional<ImageContainer*> ctr = this->itemRepository->getImageContainer(imageHash);
    if (ctr.has_value())return ctr.value()->filePath;
    return {};
}

bool ImageManagerInterface::replaceHash(const QString &oldHash, const QString &newHash) const {
    // This method is not required for now.
    return true;
}

void ImageManagerInterface::populateInfoLabels(
    const QString &imageHash, QLabel * const extCard,
    QLabel * const fileSizeCard, QLabel * const timeStampCard, RegularButton* const saveButton
) const {
    const std::optional<ImageContainer*> container = this->itemRepository->getImageContainer(imageHash);

    if (!container.has_value())throw std::runtime_error(
        "Unable to retrieve data from repository"
    );

    const ImageContainer* cont = container.value();

    extCard->setText(cont->extension);

    fileSizeCard->setText(QString::fromStdString(std::to_string(cont->fileSize) + " kb"));

    timeStampCard->setText(cont->timeStamp);

    if (cont->saveStatus == 0) {
        saveButton->setIcon(
            IconManager::confirmIcon()
        );
    }
}
