//
// Created by sujal-stark on 2/18/26.
//

#pragma once

#include "ItemWidget.h"
#include "../ManagerSources/ImageManagerInterface.h"

class ImageWidget : public ItemWidget {
    Q_OBJECT
    // Manager Interface
    shared_ptr<ImageManagerInterface> imageManagerInterface = nullptr;

    // QLabel
    QPointer<QLabel> imageLabel = nullptr;

protected:

    /**
     * @brief Performs the deletion of this Widget. Once clicked it emits
     * a signal of File's path save status and hash values for further
     * clean up by ClipBoardInterface.
     */
    void deleteButtonClicked() override;

    /**
     * @brief Saves Image corresponding to Current Hash Value. Works only for
     * Image Objects, Image paths present in system are not needed
     * to be redownloaded. No need to check for hash validity as valid
     * hashes are provided to imageLabel.
     */
    void saveButtonClicked() override;
    void editButtonClicked() override;

    /**
     * @brief This method extracts QImage with it's HashValue, and sends a
     * signal to ClipBoardInterface with QImage Object. It also performs some
     * UI change while it's clicked.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Once Mouse Button is released this method reverts Widget's style
     * to default from Clicked Duration style.
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    /**
     * @brief Default properties related to this widget is set.
     * All components for this widget are constructed. Signals
     * are bonded and styles added.
     */
    explicit ImageWidget();
    void construct() const;

    /**
     * @param path FilePath of the Image
     * @param imageHash Hexadecimal Hash value of the image entry.
     * @param mode expresses Save status of Image.
     * @brief This method runs ImageManagerInterface to store info about
     * the image and create imageLabel from it. At the end assign the
     * label in parent Widget.
     */
    void assignImage(const QString& path, const QString& imageHash, int mode);

    /**
     * @brief Receives Drivers (ImageManagerInterface) from ClipBoardInterface.
     * Throws invalid_argument() error if the pointer to the object is nullptr.
     * @param interface Shared Pointer Reference of ImageManagerInterface.
     */
    void assignDrivers(const shared_ptr<ImageManagerInterface>& interface);


    signals:
    /**
     * @brief Once this widget is clicked this signal is sent so that
     * the QImage instance can be loaded to system's clip board.
     */
    void imageItemClickedSignal(QImage image);

    /**
     * @brief This signal is released when a ImageWidget is removed from UI.
     * The parameters are given to ensure total removal of temporary files and
     * hash values from Application's Log.
     * @param imageHash Hexadecimal hash value of Image File.
     * @param filePath File's Address.
     * @param mode expresses either a file is temporarily saved or permanently.
     */
    void imageRemovedConfirmation(const QString& imageHash, const QString& filePath, int mode);
};