//
// Created by sujal-stark on 2/7/26.
//

#include "MimeDataAnalyzer.h"

#include <qurl.h>

#include "Constants.h"
#include <QStandardPaths>
#include <chrono>
#include <sstream>
#include <stdexcept>

using namespace std;

MimeDataAnalyzer::MimeDataAnalyzer() {
    createTemporaryFileLocation();
    this->createConnections();
};

void MimeDataAnalyzer::createConnections() const {
    connect(
        qApp, &QApplication::aboutToQuit,
        this, &MimeDataAnalyzer::removeTemporaryFiles
    );
}

void MimeDataAnalyzer::driverReceiver(const shared_ptr<ItemRepository>& repo) {
    this->itemRepository = repo;
}

void MimeDataAnalyzer::analyzeMimeObject(const QMimeData& mime) {
    if (mime.hasText()) {
        if(
            const string text = mime.text().toStdString();
            !this->analyzeText(text)
        ) {
            if (
                const QString currHash = HashGenerator::generateTextHash(text);
                this->itemRepository->addNewTextItemHash(currHash)
            )emit textReleaseSignal(mime.text(), currHash);
        }
    }

    if (mime.hasImage()) {
        const QImage image = convertToQImage(mime);
        if(image.isNull())return;

        const QString imageHash = HashGenerator::generateImageObjectHash(image);
        if (this->itemRepository->imageHashExists(imageHash))return;

        const QString fileName = saveImageFile(image);
        if (fileName.isNull())return;

        if (
            this->itemRepository->addNewImageItem(
                imageHash, fileName, QString::fromStdString(Constants::PNG),
                1, timeStampReadable()
            )
        )emit imageFilePathReleaseSignal(fileName, imageHash, 1);
    }
}

QImage MimeDataAnalyzer::convertToQImage(const QMimeData& mime_data) {
    QVariant imageVariant = mime_data.imageData();

    if (imageVariant.isValid() && imageVariant.canConvert<QImage>()) {
        return qvariant_cast<QImage>(imageVariant);
    }

    return {};
}

bool MimeDataAnalyzer::isValidPath(const filesystem::path& address) {
    return filesystem::exists(address);
}

bool MimeDataAnalyzer::isValidURL(const string &text) {
    const QUrl url = QUrl(QString::fromStdString(text));
    return url.isValid() && (url.scheme() == Constants::HTTP || url.scheme() == Constants::HTTPS);
}


bool MimeDataAnalyzer::isImageFile(string ext) {
    ranges::transform(ext, ext.begin(), ::tolower);
    return ext == Constants::JPG || ext == Constants::JPEG
    || ext == Constants::PNG || ext == Constants::WEBP || ext == Constants::TIFF;
}

QString MimeDataAnalyzer::saveImageFile(const QImage& imageData) const {
    QString fileName = QString::fromStdString(
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toStdString()
            + this->TEMP_IMAGE_PATH + "/IMAGE_" + to_string(timeStamp()) + Constants::PNG
        );
    if(!imageData.save(fileName))throw runtime_error("Unable to store Image");
    return fileName;
}

bool MimeDataAnalyzer::deleteImageFile(const QString &filePath) {
    try {
        return filesystem::remove(filePath.toStdString());
    }catch (filesystem::filesystem_error& e) {
        qWarning()<<"Failed to remove Image file. "<<e.what();
        return false;
    }
}

bool MimeDataAnalyzer::isVideoFile(string ext) {
    ranges::transform(ext, ext.begin(), ::tolower);
    return ext == Constants::MP4 || ext == Constants::MKV
    || ext == Constants::AVI || ext == Constants::WEBM;
}

bool MimeDataAnalyzer::isAudioFile(string ext) {
    ranges::transform(ext, ext.begin(), ::tolower);
    return ext == Constants::MP3 || ext == Constants::WAV
    || ext == Constants::AAC || ext == Constants::FLAC|| ext == Constants::OGG
    || ext == Constants::WMA || ext == Constants::M4A;
}

bool MimeDataAnalyzer::analyzeText(const string &text) {
    stringstream stream = stringstream(text);
    string line;
    bool flag = true;

    while (getline(stream, line, '\n')) {
        if (line.empty())continue;
        filesystem::path address = filesystem::path(line);

        if (filesystem::exists(address)) {
            string ext = address.extension().string();
            const QString filePath = QString::fromStdString(line);

            if (isImageFile(ext)) {
                if (
                    QString imageHash = HashGenerator::generateImageObjectHash(filePath);
                    this->itemRepository->addNewImageItem(
                        imageHash, filePath, ext.data(), 0, timeStampReadable()
                    )
                )emit imageFilePathReleaseSignal(filePath, imageHash, 0);
            }

            else if (isVideoFile(ext)) {
                // emit videoFilePathReleaseSignal(
                //     filePath, ext.data(), 0
                // );
            }

            else if (isAudioFile(ext)) {
                // emit audioFilePathReleaseSignal(
                //     filePath, ext.data(), 0
                // );
            }

            else qWarning()<<"Different File detected";
        }

        else if (isValidURL(line)) {

        }

        else flag = false;
    }

    return flag;
}

void MimeDataAnalyzer::createTemporaryFileLocation() const {
    const string base = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation
    ).toStdString();

    filesystem::create_directories(base + this->TEMP_IMAGE_PATH);
    filesystem::create_directories(base + this->TEMP_AUDIO_PATH);
    filesystem::create_directories(base + this->TEMP_VIDEO_PATH);
}

void MimeDataAnalyzer::removeTemporaryFiles() const {
    const string base = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation
    ).toStdString();

    filesystem::remove_all(base + this->TEMP_IMAGE_PATH);
    filesystem::remove_all(base + this->TEMP_AUDIO_PATH);
    filesystem::remove_all(base + this->TEMP_VIDEO_PATH);
}

long long MimeDataAnalyzer::timeStamp() {
    return chrono::duration_cast<chrono::microseconds>(
        chrono::system_clock::now().time_since_epoch()
    ).count();
}

QString MimeDataAnalyzer::timeStampReadable() {
    const time_t currentTime = chrono::system_clock::to_time_t(
        chrono::system_clock::now()
    );

    ostringstream oss;
    const tm *stamp = localtime(&currentTime);
    oss<<put_time(stamp, "%H%M%S%D");

    return QString::fromStdString(oss.str());
}