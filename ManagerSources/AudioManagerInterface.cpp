//
// Created by sujal-stark on 3/14/26.
//

#include "AudioManagerInterface.h"

#include <QFile>

AudioManagerInterface::AudioManagerInterface() = default;

void AudioManagerInterface::establishConnections() {
    // Not required Now.
}

QPointer<AudioCard> AudioManagerInterface::createAudioLabel(
    const QString& filePath, const QString& hash, const int mode
) {
    QPointer audioLabel = new AudioCard(filePath, hash, mode);
    return  audioLabel;
}

QString AudioManagerInterface::releaseAudioData(const QString &audioHash) const {
    if (audioHash.isEmpty())throw invalid_argument("invalid hash value.");

    const AudioContainer* container = this->itemRepository->getAudioContainer(audioHash);
    if (container == nullptr)return {};

    return container->filePath;
}

bool AudioManagerInterface::removeItem(const QString &hash) const {
    return this->itemRepository->removeAudioItemHash(hash);
}

bool AudioManagerInterface::replaceHash(const QString &oldHash, const QString &newHash) const {
    // not required now.
    return true;
}
