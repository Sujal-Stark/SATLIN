//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <qimage.h>
#include  <QLabel>

using namespace std;

class ImageManagerInterface : public QWidget{
    QImage currentImage; // stores newly copied Image
    QString currentHash;
    unordered_map<QString, QLabel *>hashImage; // checks for unique image
    unordered_map<QString, unique_ptr<QPixmap>> qPixmapHash;

    [[nodiscard]] QLabel* createPixmapLabel(); // Creates the PixMap
    [[nodiscard]]static QImage generateThumbnail(const QImage &qImage);
    void storePixmap(const QImage& image);
    void addThumbnailToMap(); // takes an instance of QImage

public:
    explicit ImageManagerInterface();
    void setInputImage(const QImage &qImage, QString currentHash);
    bool removeItem(const QString &imageHash);
    [[nodiscard]] QLabel* getCurrentPixmapLabel(); // sends output
    void saveActionPerformed(const QString& imageHash);
};
