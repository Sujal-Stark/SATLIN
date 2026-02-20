//
// Created by sujal-stark on 2/18/26.
//

#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

#include "../ManagerSources/ImageManagerInterface.h"
#include "../ManagerSources/IconManager.h"

class ImageWidget : public QWidget {
    Q_OBJECT
    QString image_item_Hash = nullptr;

    // Manager Interface
    ImageManagerInterface *imageManagerInterface = nullptr;

    // QButtons
    QPushButton *deleteButton = new QPushButton();
    QPushButton *editButton = new QPushButton();
    QPushButton *saveButton = new QPushButton();

    // QLabel
    QPointer<QLabel> imageLabel = nullptr;

    // Layouts
    QVBoxLayout *masterLayout = new QVBoxLayout();
    QVBoxLayout *masterInnerLayout = new QVBoxLayout();

    QHBoxLayout *contentHolder = new QHBoxLayout();
    QHBoxLayout *buttonHolder = new QHBoxLayout();

    // Frames
    QFrame *mainFrame = new QFrame();

    // General
    void stylizeButtons() const;
    void stylizeFrames() const;

    /**
     * All signals from Ui components to internal methods are
     * bonded here.
     */
    void establishConnections();

    /**
     * Performs the deletion of this Widget. Once clicked it emits
     * a signal based on type of copied image and removes their
     * hash values from clipboard's track system.
     */
    void deleteButtonClicked();

    /**
     * Saves The media corresponding to Current Hash Value. Works only for
     * Image Objects, Image paths present in system are not needed
     * to be redownloaded. No need to check for hash validity as valid
     * hashes are provided to imageLabel.
     */
    void saveButtonClicked() const;
    void editButtonClicked() const;
    void stylize();

protected:
    /**
     * Depends upon the type of Image widget is clicked this method extracts
     * QImage, and sends a signal imageItemClickedSignal(QImage image)
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * Once Mouse Button is released this method reverts Widget's style to default
     * from Clicked Duration style.
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    /**
     * Default properties related to this widget is set.
     * All components for this widget are constructed. Signals
     * are bonded and styles added.
     */
    explicit ImageWidget();
    void construct() const;

    /**
    * Given a const QImage(image data), const QString& (hash value) this method
    * runs ImageManagerInterface to store info about the image and create
    * imageLabel from it. In the end store the label in the parent Widget. Only
    * copy images are allowed to download.
    */
    void assignImage(const QImage &image, const QString& imageHash);// holds image

    /**
     * Given a const string(image path) this method runs ImageManagerInterface
     * to store info about the image and create imageLabel from it. In the end
     * store the label in the parent Widget. Images got from file path are
     * unnecessary to download.
     */
    void assignImage(const QString& path);

    /**
     * This method is responsible for catching up all interfaces or managers
     * to work with images.
     */
    void setImageManagerInterfaceInput(ImageManagerInterface *interface);


    signals:
    void imageItemClickedSignal(QImage image);
    void imageObjectRemovalRequestSignal(const QString &image_Hash);
    void imagePathRemovalRequestSignal(size_t imageHash);
};