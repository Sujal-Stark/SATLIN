//
// Created by sujal-stark on 2/7/26.
//

#pragma once

#include <QMimeData>
#include <filesystem>
#include <QWidget>
#include <QUrl>
#include <QApplication>

#include "ItemRepository.h"
#include "../Util/HashGenerator.h"

using namespace std;

class MimeDataAnalyzer : public QWidget{
    Q_OBJECT
    // General
    shared_ptr<ItemRepository> itemRepository = nullptr;
    const string TEMP_IMAGE_PATH = "/items/images";
    const string TEMP_AUDIO_PATH = "/items/audios";
    const string TEMP_VIDEO_PATH = "/items/videos";

    /**
     * All the necessary signals are bonded with their corresponding
     * methods in this createConnections method. Must be used inside
     * constructor to create necessary connections First.
     */
    void createConnections() const;

    /**
     * Given a filesystem::path variable this method verifies the
     * existence of the given path in the system.
     */
    static bool isValidPath(const filesystem::path& address);

    /**
     * Given a const string& variable this method verifies if
     * the string is a Web URL or not.
     */
    static bool isValidURL(const string& text);

    /**
     * This method returns the time stamp in microseconds
     * at which the item is copied and processed as a long - long
     * number.
     */
    static long long timeStamp();

    /**
     * This method creates folders to store incoming items as files
     * inside some specific folders created.
     */
    void createTemporaryFileLocation() const;

    /**
     * Removes all The files from Temporary Locations to save memory.
     */
    void removeTemporaryFiles() const;

    // Text
    /**
     * This method operates over text items coming from MimeData.
     * It checks for a text to contain different file's path, web
     * urls, and sends corresponding signals with meta-data to the
     * required Class.
     */
    [[nodiscard]]static bool analyzeText(const string& text);

    // Image
    const QString DEFAULT_IMAGE_EXTENSION = ".png";
    /**
     * Given an QImage Object (nonempty) this method provides a unique
     * name and tries to save the image object in specific folder.
     * The output of the operation is returned.
     */
    [[nodiscard]] QString saveImageFile(const QImage& imageData) const;

    /**
     * Checks if the given string is a valid extension of supported
     * image file extension or not. Irrespective of case.
     */
    [[nodiscard]] static bool isImageFile(string ext);

    // Video
    /**
     * Checks if the given string is a valid extension of supported
     * video file extension or not. Irrespective of case.
     */
    [[nodiscard]] static bool isVideoFile(string ext);

    // Audio
    /**
     * Checks if the given string is a valid extension of supported
     * audio file extension or not. Irrespective of case.
     */
    [[nodiscard]] static bool isAudioFile(string ext);

    signals:
    void textReleaseSignal(QString text, QString hash);

    // image
    void imageFilePathReleaseSignal(QString text, QString ext, int saveStatus);
    void imageObjectReleaseSignal(QSharedPointer<QImage> qImage);

    // video
    void videoFilePathReleaseSignal(QString text, QString ext, int saveStatus);

    // audio
    void audioFilePathReleaseSignal(QString text, QString ext, int saveStatus);

public:
    MimeDataAnalyzer();
    /**
     * It also receives an ItemRepository object and use it for preventing
     * deduplication
     */
    void driverReceiver(const shared_ptr<ItemRepository>& repo);

    /**
     * it receives a QMimeData Object and operate on it.
     */
    void analyzeMimeObject(const QMimeData& mime);

    // Image
    /**
     * Accepts the raw image data from the ClipBoard and
     * tries to convert into QImageObject. If unable to convert
     * then it returns an empty QImage Object
     */
    static QImage convertToQImage(const QMimeData& mime_data);
};
