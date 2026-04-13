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
     * @brief All the necessary signals are bonded with their corresponding
     * methods in this createConnections method. Must be used inside
     * constructor to create necessary connections First.
     */
    void createConnections() const;

    /**
     * @brief Given a filesystem::path variable this method verifies the
     * existence of the given path in the system.
     */
    static bool isValidPath(const filesystem::path& address);

    /**
     * @brief Given a const string& variable this method verifies if
     * the string is a Web URL or not.
     */
    static bool isValidURL(const string& text);

    /**
     * @brief This method returns the time stamp in microseconds
     * at which the item is copied and processed as a long - long
     * number.
     */
    static long long timeStamp();

    /**
     * @brief Returns the time stamp in readable format. The Time is presented
     * as HH/MM/SS/DATE format.
     */
    static QString timeStampReadable();

    /**
     * @brief This method creates folders to store incoming items as files
     * inside some specific folders created.
     */
    void createTemporaryFileLocation() const;

    /**
     * @brief Removes all The files from Temporary Locations to save memory.
     */
    void removeTemporaryFiles() const;

    // Text
    /**
     * @brief This method operates over text items coming from MimeData.
     * It checks for a text to contain different file's path, web
     * urls, and sends corresponding signals with meta-data to the
     * responsible Class.
     * @param text The Original Text copied with System's clipboard.
     */
    [[nodiscard]] bool analyzeText(const string& text);

    // Image
    /**
     * @brief Primarily used for Images which are copied as objects. Png Extension
     * is given to avoid lossy conversion.
     */
    const QString DEFAULT_IMAGE_EXTENSION = ".png";

    /**
     * @brief this method provides a unique name and tries to save the
     * image object in specific folder. The Full filepath of the Image is returned.
     * Throws runtime_error if the image file is failed to be saved.
     * @param imageData QImage File to store.
     */
    [[nodiscard]] QString saveImageFile(const QImage& imageData) const;

    /**
     * @brief Checks if the given string is a valid extension of supported
     * image file extension or not. Irrespective of case.
     */
    [[nodiscard]] static bool isImageFile(string ext);

    // Video
    /**
     * @brief Checks if the given string is a valid extension of supported
     * video file extension or not. Irrespective of case.
     */
    [[nodiscard]] static bool isVideoFile(string ext);

    // Audio
    /**
     * @brief Checks if the given string is a valid extension of supported
     * audio file extension or not. Irrespective of case.
     */
    [[nodiscard]] static bool isAudioFile(string ext);

    signals:
    void textReleaseSignal(QString text, QString hash);

    // image
    void imageFilePathReleaseSignal(QString filePath, QString imageHash, int saveStaus);

    // video
    void videoFilePathReleaseSignal(QString text, QString ext, int saveStatus);

    // audio
    /**
     * @brief Sends The metadata related to the audio file to the caller class.
     * @param saveStatus Represents if a audio File is already saved or just copied.
     * @param fileSize KiloByte size of the audio file.
     * @param filePath Absolute file path of the audio File.
     * @param ext Extension type
     * @param timeStamp The time at which this audio file is copied to the system
     * @param hash Hexadecimal hash value assigned to the audio file.
     */
    void audioFilePathReleaseSignal(
        int saveStatus, qint32 fileSize, QString filePath,
        QString ext, QString timeStamp, QString hash
    );

public:
    MimeDataAnalyzer();
    /**
     * It also receives an ItemRepository object and use it for preventing
     * deduplication
     */
    void driverReceiver(const shared_ptr<ItemRepository>& repo);

    /**
     * @brief It's most initial method that runs to identify Media Type.
     * And perform necessary operations to store temporary Files, create Logs
     * And finally Send signals to further processing.
     * @param mime Current instance of Mime Object.
     */
    void analyzeMimeObject(const QMimeData& mime);

    // Image
    /**
     * @brief Accepts the raw image data from the ClipBoard and
     * tries to convert into QImageObject. If unable to convert
     * then it returns an empty QImage Object
     */
    static QImage convertToQImage(const QMimeData& mime_data);

    /**
     * @brief Check's if the file path is valid or not. Then removes
     * the file from system. IF failed throws runtime_error exception.
     * @param filePath complete address of image file.
     */
    [[nodiscard]] static bool deleteImageFile(const QString& filePath);

    /**
     * Removes The audio file from system using its File path.
     * @param filePath Absolute file path of Audio File.
     * @return Returns True for success of this operation
     */
    [[nodiscard]] static bool deleteAudioFile(const QString& filePath);
};
