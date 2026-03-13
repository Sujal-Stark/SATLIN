//
// Created by sujal-stark on 2/25/26.
//

#include "ItemRepository.h"
#include <QDebug>

ItemRepository::ItemRepository() = default;

ItemRepository::~ItemRepository() {
    // TEXT
    this->textHashCollector.clear();

    // IMAGE
    qDeleteAll(this->imageHashCollector);
    this->imageHashCollector.clear();
}

bool ItemRepository::addNewTextItemHash(const QString &textHash) {
    if (textHash.isNull())return  false;
    if (this->textHashCollector.contains(textHash)) return false;
    this->textHashCollector.insert(textHash);
    return true;
}

bool ItemRepository::containsTextHash(const QString &textHash) const {
    return this->textHashCollector.contains(textHash);
}

bool ItemRepository::removeTextItemHash(const QString &textHash) {
    return this->textHashCollector.remove(textHash);
}

bool ItemRepository::addNewImageItem(
    const QString &imageHash, const QString &filePath, const QString &extension,
    const int saveStatus, const QString &timeStamp
) {
    if (imageHash.isEmpty() || filePath.isEmpty() || extension.isEmpty()) return false;
    if (saveStatus > 1 || saveStatus < 0)return  false;
    if (timeStamp.isEmpty())return false;

    if (this->imageHashExists(imageHash))return false;

    this->imageHashCollector.insert(
        imageHash, new ImageContainer(
            saveStatus, filePath, extension, timeStamp
        )
    );

    return true;
}

bool ItemRepository::imageHashExists(const QString& imageHash) {
    const QMap<QString, ImageContainer*>::iterator it = this->imageHashCollector.find(imageHash);
    return it != this->imageHashCollector.end();
}

bool ItemRepository::removeImageItemHash(const QString &imageHash) {
    const QMap<QString, ImageContainer*>::iterator it = this->imageHashCollector.find(imageHash);
    if (it == this->imageHashCollector.end())return false;
    delete it.value();
    this->imageHashCollector.erase(it);
    return true;
}

const ImageContainer* ItemRepository::getImageContainer(const QString& imageHash) {
    if (imageHash.isEmpty())return nullptr;

    const QMap<QString, ImageContainer*>::iterator it = this->imageHashCollector.find(imageHash);
    if (it == this->imageHashCollector.end())return nullptr;

    return it.value();
}

void ItemRepository::showImageContainer() const {
    qDebug()<<"Showing current Image Hashes....";
    for (const auto& it : this->imageHashCollector.keys()) {
        qDebug()<<it;
    }
}

void ItemRepository::showTextContainer() const {
    qDebug()<<"Showing Current Text Hashes....";
    for (const auto& it : this->textHashCollector) {
        qDebug()<<it;
    }
}
