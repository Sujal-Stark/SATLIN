//
// Created by sujal-stark on 3/14/26.
//

#pragma once
#include <qpointer.h>

#include "../Util/ItemRepository.h"
#include "../Widgets/AudioCard.h"

class AudioManagerInterface {
    /**
     * Stores All Entries of Audio File by their hash value
     * and Other metadata.
     */
    shared_ptr<ItemRepository> itemRepository;

public:
    static constexpr int SAVE_STATUS_TRUE = 1;
    static constexpr int SAVE_STATUS_FALSE = 0;

    explicit AudioManagerInterface();

    /**
     * @brief Receives necessary drivers(instance of classes) to perform
     * different operations on AudioFile.
     * @param repo ItemRepository Instance Provided By ClipBoardInterface
     */
    void assignDrivers(const shared_ptr<ItemRepository>& repo);

    /**
     * @brief This method accepts necessary parameters and create
     * an AudioCard Widget.
     * @param filePath absolute file path of audio File
     * @param hash Hexadecimal hash value assigned to audioFile
     * @param mode storage status (either saved or temporarily saved)
     * @return An instance of AudioCard
     */
    [[nodiscard]] static QPointer<AudioCard> createAudioLabel(
        const QString& filePath, const QString& hash, int mode
    );

    /**
     * @brief This Method removes the entry of given hash value and
     * corresponding AudioContainer from ItemRepository
     * @param hashValue Hexadecimal hash value assigned to audioFile
     * @return a boolean output representing success or failure
     */
    [[nodiscard]] bool removeAudioItem(const QString& hashValue) const;

    /**
     * @brief With given hash value this method returns the absolute file
     * path from Item Repository.
     * @param audioHash Hexadecimal Hash Value assigned to AudioFile
     * @return QString of Absolute file Path of AudioFile
     */
    [[nodiscard]] QString releaseAudioData(const QString& audioHash) const;
};
