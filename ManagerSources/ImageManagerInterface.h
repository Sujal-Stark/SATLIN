//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <qimage.h>
#include  <QLabel>
#include <stdexcept>

using namespace std;

class ImageManagerInterface : public QWidget{
    // For Object based tracking
    unordered_map<QString, QPointer<QLabel>>thumbnailContainer;
    unordered_map<QString, unique_ptr<QImage>> qImageHashSet;

    // For File path based tracking
    unordered_map<size_t, QPointer<QLabel> >pathBasedThumbnailCollector;
    unordered_map<size_t, unique_ptr<QString>> imagePathSet;

    /**
     * Generates a thumbnail for the image(cheap copy of the content) and creates
     *  a label for it. Also stores the original QImage(Original Content)
     *  as a unique_ptr<QImage>.
     */
    [[nodiscard]] QPointer<QLabel> createPixmapLabel(const QString& hash, const QImage& image);

    /**
     * Generates a thumbnail(cheap copy) for the image and creates a label for it.
     * Also stores the original Path(File path) as a unique_ptr<QString>.
     */
    [[nodiscard]] QPointer<QLabel> createPixmapLabel(const QString& path, const QPixmap& pixmap);

    /**
     * Creates The ImageLabel, sets pixmap object to it and manages Label's Styles.
     */
    [[nodiscard]] static QPointer<QLabel> createLabel(const QPixmap& pixmap);


    /**
     * Given a const QImage, This method reduces the size to imageWidget's
     * required size, and returns the reduced one.
     */
    [[nodiscard]]static QPixmap generateThumbnail(const QImage &qImage);

    /**
     * Given a const QPixmap, This method reduces the size to imageWidget's
     * required size, and returns the reduced one.
     */
    [[nodiscard]]static QPixmap generateThumbnail(const QPixmap& pixmap);

    /**
     * Check's if the hash corresponding to pixmap already exists or not.
     * If not then stores the QImage File.
     */
    void storeImageObject(const QImage& image, const QString& hash);

    /**
     * Check's if the hash corresponding to filePath already exists or not.
     * If not then stores the File Path.
     */
    void storeFilePath(const QString& path);

    void addThumbnailToMap(const QPointer<QLabel> & pixmapLabel, const QString& currentHash);
    void addThumbnailToMap(const QPointer<QLabel> & pixmapLabel, size_t currentHash);

public:
    static constexpr int IMAGE_ACCESS_VIA_COPY = 0;
    static constexpr int IMAGE_ACCESS_VIA_PATH = 1;

    explicit ImageManagerInterface();

    /**
     * Accepts a valid QImage(const reference) and store it's thumbnail
     * as QLabel object in Thumbnail container. This single method is
     * responsible for all necessary operations to access a new QLabel object
     * which can be directly used in UI. Throws invalid_argument exception if
     * const QImage& qImage or const QString& currentHash is null.
     */
    void setInputImage(const QImage &qImage, const QString& currentHash);

    /**
     * Accepts a valid file path(const reference) and store it's thumbnail
     * as QLabel object in Thumbnail container. This single method is
     * responsible for all necessary operations to access a new QLabel object
     *  which can be directly used in UI. Throws invalid_argument exception
     *  if const string& path is null.
     */
    void setInputImage(const QString& path);

    /**
     * Deletes pointers from thumbnailContainer & qImageHashSet with the given key.
     * QPointer removes QLabel's reference, unique_ptr removes qImage object safely.
     */
    void removeCopyItem(const QString &imageHash);

    /**
     * Deletes pointers from pathBasedThumbnailCollector & imagePathSet with the given key.
     * QPointer removes QLabel's reference, unique_ptr removes path object safely.
     */
    void removePathItem(size_t imageHash);

    /**
     * given a valid hash code (const QString&) this method provides
     * corresponding QPointer<QLabel> Object. If given hash value is a null ptr then
     * an invalid_argument exception is thrown.
     */
    [[nodiscard]] QPointer<QLabel> getPixmapLabel(const QString& imageHash); // sends output

    /**
     * given a valid hash code (const size_t&) this method provides The QLabel* Object.
     * User can use the label after dereferencing the pointer.
     */
    [[nodiscard]] QPointer<QLabel> getPixmapLabel(size_t imageHash);

    /**
     * After checking validity of hash value this method returns a raw pointer of
     * QImage object corresponding to the QImage. For invalid hashes this method
     * raises invalid argument error.
     */
    [[nodiscard]] QImage releaseImageData(const QString& imageHash) const;

    /**
     * Check's for validity of hash value. After validation this method creates a
     * raw QImage Object from File's address and sends by value. If no hash value
     * is present then it returns an empty QImage
     */
    [[nodiscard]] QImage releaseImageData(size_t imageHash) const;

    /**
     * Selects directory, file name for the image to be saved.
     * and saved using QPixmap save method.
     */
    void saveActionPerformed(const QString& imageHash);
};
