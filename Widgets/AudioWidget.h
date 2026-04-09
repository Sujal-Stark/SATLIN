//
// Created by sujal-stark on 3/14/26.
//

#pragma once
#include <QLabel>
#include <qpointer.h>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

#include "../ManagerSources/AudioManagerInterface.h"

class AudioWidget : public QWidget{
    Q_OBJECT
    // Manager Interfaces
    /**
     * This Object Operates On Audio File. All Parsing, editing,
     * storage, retrieval is done with help this Object.
     */
    std::shared_ptr<AudioManagerInterface> audioManagerInterface = nullptr;

    // QButtons
    QPushButton *deleteButton = new QPushButton();
    QPushButton *editButton = new QPushButton();
    QPushButton *saveButton = new QPushButton();

    // QLabels
    QPointer<AudioCard> audioLabel = nullptr;

    // Layouts
    QVBoxLayout *masterLayout = new QVBoxLayout();
    QVBoxLayout *masterInnerLayout = new QVBoxLayout();

    QHBoxLayout *contentHolder = new QHBoxLayout();
    QHBoxLayout *buttonHolder = new QHBoxLayout();

    // Frames
    QFrame *mainFrame = new QFrame();

    // General
    void stylizeButtons() const;

    /**
     * @brief All signals from Ui components to internal methods are
     * Connected here.
     */
    void establishConnections();

    /**
     * @brief Performs the deletion of this Widget. Once clicked it emits
     * a signal of File's path save status and hash values for further
     * clean up by ClipBoardInterface. And this Q Object is scheduled
     * to be deleted.
     */
    void deleteButtonClicked();

    /**
     * @brief Saves Audio corresponding to Current Hash Value.
     * Audio paths present in system are not needed to be redownloaded.
     * No need to check for hash validity as valid
     * hashes are provided to AudioLabel.
     */
    void saveButtonClicked() const;
    void editButtonClicked() const;
    void stylize();

protected:
    /**
     * @brief This method extracts audio file path with it's HashValue, and sends a
     * signal to ClipBoardInterface with QUrl Object. It also performs some
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
    explicit AudioWidget();

    /**
     * @brief All Ui components are attached with each other in this
     * method.
     */
    void construct() const;

    /**
     * @brief Creates A AudioCard Widget With the given information and
     * Attach it with the UI. This AudioWidget is now able to use in ClipBoardInterface
     * @param saveStat Represents Either the file is saved or copied Temporarily.
     * @param fileSize Size of the Audio File in mb
     * @param filePath The absolute file Path of AudioFile.
     * @param ext Current Extension of Audio File
     * @param stamp Time at which The audio File is copied.
     * @param hash Hexadecimal Hash Value assigned to the audioFile.
     */
    void assignAudio(
        int saveStat, qint32 fileSize, const QString& filePath, const QString& ext,
        const QString& stamp, const QString& hash
    );

    /**
     * @brief Receives Drivers (AudioManagerInterface) from ClipBoardInterface.
     * Throws invalid_argument() error if the pointer to the object is nullptr.
     * @param interface Shared Pointer Reference of AudioManagerInterface.
     */
    void assignDrivers(const shared_ptr<AudioManagerInterface>& interface);

    signals:
    /**
     * @brief Sends the QUrl object of Filepath to the Caller Object. The
     * file path can be used to feed the System's Clip Board
     * @param filePath The Absolute File path of AudioFile as QUrl Object.
     */
    void audioItemClickedSignal(QUrl filePath);

    /**
     * @brief Sends current hash, file path and save mode to the caller Object
     * This method should be used to send data for clean up of AudioItem from system.
     * @param audioHash Hexadecimal Hash Value Assigned to the audio File
     * @param filePath QUrl Object containing Absolute File path of audio File.
     * @param mode Represents if the audio File is permanently saved or copied.
     */
    void audioRemovedConfirmation(const QString& audioHash, const QUrl& filePath, int mode);
};
