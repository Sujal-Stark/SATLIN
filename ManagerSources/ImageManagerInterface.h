//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <qimage.h>
#include  <QLabel>
#include <stdexcept>

#include "../Util/ItemRepository.h"

using namespace std;

class ImageManagerInterface : public QWidget{
    shared_ptr<ItemRepository> itemRepository;
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

public:
    static constexpr int SAVE_STATUS_TRUE = 1;
    static constexpr int SAVE_STATUS_FALSE = 0;

    explicit ImageManagerInterface();

    /**
     * @brief This method accepts a ItemRepository Object from
     * ClipBoardInterface. This class uses this object to manipulate
     * saved data so that ImageWidget Interface do not have to worry
     * about Image metadata and hash storing. Throws invalid_argument
     * error if given instance is nullptr.
     * @param repo a const shared pointer of ItemRepository Class
     */
    void assignDrivers(const shared_ptr<ItemRepository>& repo);

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
     * @param imageHash Hexadecimal hash value of Image File.
     */
    [[nodiscard]] bool removeImageItem(const QString& imageHash) const;

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
     * @param mode expresses Save Status. Either saved by Satlin
     */
    void saveActionPerformed(const QString& imageHash, int mode);

    /**
     * @brief Return's the file address associated with imageHash.
     * @param imageHash hexadecimal hash value of ImageObject.
     */
    [[nodiscard]] const QString& getImageFileName(const QString& imageHash) const;
};
