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

    [[nodiscard]] QPointer<QLabel> createPixmapLabel(const QString& hash, const QImage& image);
    [[nodiscard]] QPointer<QLabel> createPixmapLabel(const QString& path, const QPixmap& pixmap);
    [[nodiscard]] static QPointer<QLabel> createLabel(const QPixmap& pixmap);

    [[nodiscard]]static QPixmap generateThumbnail(const QImage &qImage);
    [[nodiscard]]static QPixmap generateThumbnail(const QPixmap& pixmap);

    void storeImageObject(const QImage& image, const QString& hash);
    void storeFilePath(const QString& path);

    void addThumbnailToMap(const QPointer<QLabel> & pixmapLabel, const QString& currentHash);
    void addThumbnailToMap(const QPointer<QLabel> & pixmapLabel, size_t currentHash);

public:
    static constexpr int IMAGE_ACCESS_VIA_COPY = 0;
    static constexpr int IMAGE_ACCESS_VIA_PATH = 1;

    explicit ImageManagerInterface();
    void setInputImage(const QImage &qImage, const QString& currentHash);
    void setInputImage(const string& path);

    void removeCopyItem(const QString &imageHash);
    void removePathItem(size_t imageHash);

    [[nodiscard]] QPointer<QLabel> getPixmapLabel(const QString& imageHash); // sends output
    [[nodiscard]] QPointer<QLabel> getPixmapLabel(size_t imageHash);

    void saveActionPerformed(const QString& imageHash);
};
