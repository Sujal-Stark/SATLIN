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

    const std::optional<AudioContainer*> container = this->itemRepository->getAudioContainer(audioHash);
    if (!container.has_value())return {};

    return container.value()->filePath;
}

bool AudioManagerInterface::removeItem(const QString &hash) const {
    return this->itemRepository->removeAudioItemHash(hash);
}

bool AudioManagerInterface::replaceHash(const QString &oldHash, const QString &newHash) const {
    // not required now.
    return true;
}

void AudioManagerInterface::populateInfoLabels(
    const QString &audioHash, QLabel * const extCard, QLabel * const fileSizeCard,
    QLabel * const timeStampCard, RegularButton* const saveButton
) const {
    const std::optional<AudioContainer*> obj = this->itemRepository->getAudioContainer(audioHash);

    if (!obj.has_value())throw std::runtime_error(
        "unable to retrieve data from repository."
    );

    const AudioContainer* container = obj.value();

    extCard->setText(container->extension);

    fileSizeCard->setText(
        QString::fromStdString(std::to_string(container->fileSize) + " kb")
    );

    timeStampCard->setText(container->timeStamp);

    if (container->saveStatus == 0) saveButton-> setIcon(IconManager::confirmIcon());
}
