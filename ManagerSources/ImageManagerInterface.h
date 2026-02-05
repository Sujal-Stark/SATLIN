//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <qimage.h>
#include <queue>
#include <set>
#include  <QLabel>

using namespace std;

class ImageManagerInterface {
    QImage currentImage; // stores newly copied Image
    QString currentHash;
    unordered_map<QString, QLabel *>hashImage; // checks for unique image

    [[nodiscard]] QLabel* createPixmapLabel() const; // Creates the PixMap

public:
    explicit ImageManagerInterface();
    void setInputImage(const QImage &qImage, QString currentHash);
    [[nodiscard]] QLabel* getCurrentPixmapLabel(); // sends output
    void addImageToMap(); // takes an instance of QImage
    [[nodiscard]]static QImage generateThumbnail(const QImage &qImage);
    bool removeItem(const QString &imageHash);
};
