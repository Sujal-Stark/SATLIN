//
// Created by sujal-stark on 2/25/26.
//

#include "ItemRepository.h"

#include <iostream>
#include <QDebug>

#include "ToolKit.h"

ItemRepository::ItemRepository() = default;

ItemRepository::~ItemRepository() {
    // TEXT
    this->textHashCollector.clear();

    // IMAGE
    qDeleteAll(this->imageHashCollector);
    this->imageHashCollector.clear();

    // AUDIO
    qDeleteAll(this->audioHashCollector);
    this->audioHashCollector.clear();
}

bool ItemRepository::addNewTextItemHash(
    const QString& text, const int saveStatus, const qint32 size,
    const QString& ext, const QString& timeStamp, const QString& textHash
) {
    if (textHash.isNull())return  false;
    if (this->textHashCollector.contains(textHash)) return false;

    this->textHashCollector.insert(
        textHash, new TextContainer(
            text, saveStatus, size, ext, timeStamp
        )
    );
    return true;
}

bool ItemRepository::containsTextHash(const QString &textHash) const {
    return this->textHashCollector.contains(textHash);
}

bool ItemRepository::removeTextItemHash(const QString &textHash) {
    return this->textHashCollector.remove(textHash);
}

bool ItemRepository::replaceTextHash(
    const QString &newTextHash, const QString &oldTextHash, const QString& text
) {
    if (this->textHashCollector.contains(newTextHash))return false;

    TextContainer* container = this->textHashCollector.find(oldTextHash).value();

    container->text = text;
    container->textSize = text.length() * sizeof(char);

    if (this->textHashCollector.remove(oldTextHash)) {
        this->textHashCollector.insert(
            newTextHash, container
        );

        return true;
    }

    return false;
}

std::optional<TextContainer*> ItemRepository::getTextContainer(const QString &textHash) {
    if (textHash.isNull())return {nullptr};

    const QMap<QString, TextContainer*>::iterator it = this->textHashCollector.find(textHash);

    if (it == this->textHashCollector.end())return {nullptr};

    return {it.value()};
}

void ItemRepository::showTextContainer() const {
    qDebug()<<"Showing Current Text Hashes....";
    for (const auto& it : this->textHashCollector) {
        qDebug()<<it;
    }
}

// IMAGE
bool ItemRepository::addNewImageItem(
    const QString &imageHash, const QString &filePath, const QString &extension,
    const int saveStatus, const QString &timeStamp
) {
    if (imageHash.isEmpty() || filePath.isEmpty() || extension.isEmpty()) return false;
    if (saveStatus > 1 || saveStatus < 0)return  false;
    if (timeStamp.isEmpty())return false;

    if (this->imageHashExists(imageHash))return false;

    const qint32 sizeOfImage = ToolKit::getFileSize(filePath);
    
    this->imageHashCollector.insert(
        imageHash, new ImageContainer(
            saveStatus, sizeOfImage, filePath, extension, timeStamp
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

std::optional<ImageContainer*> ItemRepository::getImageContainer(const QString& imageHash) {
    if (imageHash.isEmpty())return {nullptr};

    const QMap<QString, ImageContainer*>::iterator it = this->imageHashCollector.find(imageHash);
    if (it == this->imageHashCollector.end())return {nullptr};

    return {it.value()};
}

void ItemRepository::showImageContainer() const {
    qDebug()<<"Showing current Image Hashes....";
    for (const auto& it : this->imageHashCollector.keys()) {
        qDebug()<<it;
    }
}

// AUDIO
bool ItemRepository::addNewAudioItem(
    const int saveStat, const qint32 size, const QString &filePath,
     const QString &ext, const QString &timeStamp, const QString &hash
) {
    if (filePath.isEmpty() || ext.isEmpty() || timeStamp.isEmpty() || hash.isEmpty())return false;
    if (saveStat < 0 || saveStat > 1)return false;

    if (audioHashExists(hash))return false;
    this->audioHashCollector.insert(
        hash, new AudioContainer(
            saveStat, size, filePath, ext, timeStamp
        )
    );

    return true;
}

bool ItemRepository::audioHashExists(const QString &hash) {
    return this->audioHashCollector.find(hash) != this->audioHashCollector.end();
}

bool ItemRepository::removeAudioItemHash(const QString &hash) {
    if (hash.isEmpty())throw invalid_argument("Invalid hash");

    const QMap<QString, AudioContainer*>::iterator it = this->audioHashCollector.find(hash);
    if (it == this->audioHashCollector.end())return  false;

    delete it.value();
    this->audioHashCollector.erase(it);

    return true;
}

const AudioContainer *ItemRepository::getAudioContainer(const QString &audioHash) {
    if (audioHash.isEmpty())throw invalid_argument("Invalid hash");

    const QMap<QString, AudioContainer*>::iterator it = this->audioHashCollector.find(audioHash);
    if (it == this->audioHashCollector.end())return  nullptr;
    return it.value();
}

void ItemRepository::showAudioContainers() const {
    qDebug()<<"Showing Audio containers..";

    for (const QString& it : this->audioHashCollector.keys()) {
        qDebug()<<"Keys: "<<it;
    }
}
