//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <qimage.h>
#include <queue>
#include <set>

#include "ItemWidget.h"

using namespace std;

class ImageManagerInterface {
    QImage copiedImage; // stores newly copied Image
    unordered_map<QString, QImage *>hashImage; // checks for unique image
    queue<ItemWidget *>imageQueue;  // stores output

    [[nodiscard]] ItemWidget* createPixmapLabel(); // Creates the PixMap
    static QString getImageObjectHash(const QImage &qImage); // creates Hash for current image

public:
    void setCopiedImage(const QImage &qImage); // takes input
    [[nodiscard]] ItemWidget* getPixmap() const; // sends output
    void addImageToQueue(); // takes an instance of QImage
    [[nodiscard]]static QImage generateThumbnail(const QImage &qImage);
};
