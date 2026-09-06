//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <qimage.h>
#include  <QLabel>
#include <stdexcept>

#include "ItemManagerInterface.h"
#include "../CustomWidgets/RegularButton.h"
#include "../Util/ItemRepository.h"

using namespace std;

class ImageManagerInterface : public ItemManagerInterface{
    /**
     * @brief Generates a thumbnail(cheap copy) for the image and creates
     * a QLabel for it.
     * @param pixmap Thumbnail(Cheap Copy) of Original Image
     * @param imageHash Hexadecimal hash value of image File.
     * @param mode expresses Save Status. Either saved by Satlin
     */
    [[nodiscard]] static QPointer<QLabel> createPixmapLabel(
        const QPixmap& pixmap, const QString& imageHash, int mode
    );

    /**
     * @brief This method Generates a QPixmap Object with given ImageFile. The dimensions
     * are reduced to imageWidget's required size, and returns the reduced one.
     * @param filePath address of Image File.
     */
    [[nodiscard]]static QPixmap generateThumbnail(const QString& filePath);

protected:
    void establishConnections() override;

public:
    static constexpr int SAVE_STATUS_TRUE = 1;
    static constexpr int SAVE_STATUS_FALSE = 0;

    explicit ImageManagerInterface();


    /**
     * This single method is responsible for all necessary operations to access
     * a new QLabel object which can be directly used in UI. Throws
     * invalid_argument exception if const string& path is null.
     * @param path address of Image File.
     * @param currentHash Hexadecimal hash value of Image File.
     * @param  mode expresses Save Status. Either saved by Satlin
     * or already before.
     */
    static QPointer<QLabel> getImageLabel(
        const QString& path, const QString& currentHash, int mode
    );

    /**
     * @brief Calls ItemRepository associated methods to remove the
     * image hash and it's metadata. This method doesn't check Hash authenticity
     * it's ItemRepository's decision.
     * @param hash Hexadecimal hash value of Image File.
     */
    [[nodiscard]] bool removeItem(const QString& hash) const override;

    [[nodiscard]] bool replaceHash(const QString &oldHash, const QString &newHash) const;

    /**
     * @brief After checking validity of hash value this method returns a raw pointer of
     * QImage object corresponding to the QImage. For invalid hashes this method
     * raises invalid argument error.
     * @param imageHash Hexadecimal hash value of Image File.
     */
    [[nodiscard]] QImage releaseImageData(const QString& imageHash) const;

    /**
     * @brief Selects directory, file name for the image to be saved.
     * and saved using QPixmap save method. If the image is already saved
     * in system then save operation isn't performed, Even if request comes.
     * @param imageHash Hexadecimal hash value of Image File.
     */
    bool saveActionPerformed(const QString& imageHash);

    /**
     * @brief Return's the file address associated with imageHash.
     * @param imageHash hexadecimal hash value of ImageObject.
     */
    [[nodiscard]] const QString& getImageFileName(const QString& imageHash) const;

    void populateInfoLabels(
        const QString &imageHash, QLabel* extCard,
        QLabel* fileSizeCard, QLabel* timeStampCard,
        RegularButton* saveButton
    ) const override;
};
