//
// Created by sujal-stark on 3/22/26.
//

#pragma once
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>

using namespace std;

class AudioCard : public QWidget{
    Q_OBJECT
    // dimensions Constraints
    const int AUDIO_CARD_HEIGHT = 120;
    const int PREVIEW_WINDOW_LENGTH = 100;
    const int NAME_LABEL_HEIGHT = 30;
    const int NAME_LABEL_WIDTH = 360;
    const int CONTROL_BUTTON_LENGTH = 30;
    const QSize CONTROL_BUTTON_ICON_SIZE = QSize(25, 25);

    // Content Properties
    QMediaPlayer* player = new QMediaPlayer();
    QAudioOutput* output = new QAudioOutput();
    QMediaDevices* device = new QMediaDevices();
    QString filePath = nullptr;
    int mode;

    // Layouts
    QHBoxLayout* mainLayout = new QHBoxLayout();
    QVBoxLayout* restLayout = new QVBoxLayout();
    QHBoxLayout* controlPanel = new QHBoxLayout();

    // Labels
    QLabel* previewLabel = new QLabel();
    QLabel* nameLabel = new QLabel();
    QLabel* playTime = new QLabel();

    /**
     *  @brief For all QLabels custom Styling, alignment and size
     *  related instructions are maintained here.
     */
    void customizeLabels() const;

    // Sliders
    QSlider* flowController = new QSlider(Qt::Horizontal);

    /**
     *  @brief For all QSliders custom Styling, alignment, and size
     *  related instructions are maintained here.
     */
    void customizeSliders() const;

    // Buttons
    QPushButton* leftJump = new QPushButton();
    QPushButton* pause_resume = new QPushButton();
    QPushButton* rightJump = new QPushButton();
    QPushButton* volumeUpButton = new QPushButton();
    QPushButton* volumeDownButton = new QPushButton();

    /**
     *  @brief For all QPushButtons custom Styling, alignment and size
     *  related instructions are maintained here.
     */
    void customizeButtons() const;

    /**
     * @brief When called, this method changes the default Ui of the sender
     * button for a small fraction to emulate a sense that button is clicked.
     */
    void changeButtonUIWhenClicked(QPushButton* button) const;

    // General
    /**
     * @brief Combine All Ui components together to form a QWidget.
     * All Alignments related instructions are given here.
     */
    void construct() const;

    /**
     * @brief For Widget Elements connects appropriate methods/slots
     * to handle actions.
     */
    void manageConnections();

    /**
     * @brief Seeks previous 5 Seconds from Current Position. If the value goes
     * negative it wraps around 0. Doesn't respond if audio is not played.
     */
    void jumpLeftForFiveUnit() const;

    /**
     * @brief Seeks next 5 Seconds from Current Position. If the value goes
     * beyond audio duration, the audio Stops. Doesn't respond if audio is not played.
     */
    void jumpRightForFiveUnit() const;

    /**
     * @brief handles Pause or play signal when corresponding button is clicked.
     */
    void pausePlayAction() const;

    /**
     * @brief Increases the volume by 0.1 and wraps around to 1 if exceeded.
     * Doesn't respond if playBackState is not equal to PlayingState
     */
    void volumeUpAction() const;

    /**
     * @brief decreases the volume by 0.1 and wraps around to 0 if exceeded.
     * Doesn't respond if playBackState is not equal to PlayingState
     */
    void volumeDownAction() const;

    /**
     * @brief Updates Current position to the slider and playTime Label to
     * show Dynamic Changes.
     */
    void getRunTime(qint64 duration) const;

public:
    AudioCard(const QString& filePath, int mode);
};
