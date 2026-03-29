//
// Created by sujal-stark on 3/22/26.
//

#include "AudioCard.h"

#include <filesystem>
#include <QFile>
#include <QTimer>

#include "../ManagerSources/IconManager.h"
#include "../Util/Constants.h"

using namespace std;

AudioCard::AudioCard(const QString& filePath, const int mode) {
    if (!QFile::exists(filePath)) {
        this->deleteLater();
        return;
    } // fail safe.

    this->setFixedSize(Constants::TEXT_CARD_WIDTH, AUDIO_CARD_HEIGHT);
    this->setLayout(this->mainLayout);

    // audio Object creation
    this->filePath = filePath;
    this->mode = mode;
    this->player->setAudioOutput(this->output);
    this->player->setSource(filePath);

    // post arrangements
    this->customizeLabels();
    this->customizeSliders();
    this->customizeButtons();
    this->construct();
    this->manageConnections();
}

void AudioCard::manageConnections() {
    connect(
        device, &QMediaDevices::audioOutputsChanged,
        this, [this] {
            this->output->setDevice(QMediaDevices::defaultAudioOutput());
        }
    ); // Adapts to output device changes

    connect(
        this->leftJump, &QPushButton::clicked,
        this, &AudioCard::jumpLeftForFiveUnit
    ); // rewind to previous Five Seconds

    connect(
        this->rightJump, &QPushButton::clicked,
        this, &AudioCard::jumpRightForFiveUnit
    ); // rewind to new Five seconds

    connect(
        this->pause_resume, &QPushButton::clicked,
        this, &AudioCard::pausePlayAction
    ); // Pause or play the audio.

    connect(
        this->player, &QMediaPlayer::durationChanged,
        this, [this] {
            this->flowController->setRange(
                0, static_cast<int>(this->player->duration())/1000
            );
        }
    ); // Set Duration of Audio to QSlider.

    connect(
        this->player, &QMediaPlayer::positionChanged,
        this, &AudioCard::getRunTime
    ); // Updates current playTime and slider position

    connect(
        this->volumeUpButton, &QPushButton::clicked,
        this, &AudioCard::volumeUpAction
    ); // Increase the volume by 0.1

    connect(
        this->volumeDownButton, &QPushButton::clicked,
        this, &AudioCard::volumeDownAction
    ); // decrease the volume by 0.1
}

void AudioCard::construct() const {
    // Main Layout.
    this->mainLayout->setAlignment(Qt::AlignmentFlag::AlignCenter);
    this->mainLayout->setSpacing(5);

    // Preview Window
    this->mainLayout->addWidget(this->previewLabel, 40);

    // Rest Of the Widget
    this->mainLayout->addLayout(this->restLayout, 60);
    this->restLayout->setSpacing(5);
        // Name Section
    this->restLayout->addWidget(this->nameLabel, 30);
    this->restLayout->addWidget(this->flowController, 30);
    this->restLayout->addLayout(this->controlPanel, 40);

        // Control Panel
    this->controlPanel->setSpacing(5);
    this->controlPanel->addWidget(this->leftJump, Qt::AlignmentFlag::AlignLeft);
    this->controlPanel->addWidget(this->pause_resume, Qt::AlignmentFlag::AlignLeft);
    this->controlPanel->addWidget(this->rightJump, Qt::AlignmentFlag::AlignLeft);

    this->controlPanel->addWidget(this->volumeUpButton, Qt::AlignmentFlag::AlignCenter);
    this->controlPanel->addWidget(this->volumeDownButton, Qt::AlignmentFlag::AlignCenter);

    this->controlPanel->addWidget(this->playTime, Qt::AlignmentFlag::AlignRight);
}


void AudioCard::customizeLabels() const {
    this->previewLabel->setFixedSize(PREVIEW_WINDOW_LENGTH, PREVIEW_WINDOW_LENGTH);
    this->previewLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    this->previewLabel->setPixmap(
        QPixmap(":/Music_Note").scaled(
            PREVIEW_WINDOW_LENGTH - 10, PREVIEW_WINDOW_LENGTH - 10
        )
    ); // icon like

    this->nameLabel->setFixedSize(NAME_LABEL_WIDTH, NAME_LABEL_HEIGHT);
    this->nameLabel->setAlignment(Qt::AlignmentFlag::AlignLeft);
    this->nameLabel->setAttribute(Qt::WA_TranslucentBackground); // for transparency
    this->nameLabel->setStyleSheet("background: rgba(255, 255, 255, 0);");
    const auto fPath = filesystem::path(this->filePath.toStdString());
    this->nameLabel->setText(fPath.filename().string().data());

    this->playTime->setFixedHeight(this->CONTROL_BUTTON_LENGTH);
    this->playTime->setAlignment(Qt::AlignmentFlag::AlignRight);
    this->playTime->setAttribute(Qt::WA_TranslucentBackground); // for transparency
    this->playTime->setStyleSheet("background: rgba(255, 255, 255, 0);");
    this->playTime->setText(QString("0 : 00")); // Start's from 0:00
}

void AudioCard::customizeButtons() const {
    this->leftJump->setFixedSize(this->CONTROL_BUTTON_LENGTH, this->CONTROL_BUTTON_LENGTH);
    this->leftJump->setIcon(IconManager::leftJumpIcon());
    this->leftJump->setIconSize(this->CONTROL_BUTTON_ICON_SIZE);

    this->pause_resume->setFixedSize(this->CONTROL_BUTTON_LENGTH, this->CONTROL_BUTTON_LENGTH);
    this->pause_resume->setIcon(IconManager::playButtonIcon());
    this->pause_resume->setIconSize(this->CONTROL_BUTTON_ICON_SIZE);

    this->rightJump->setFixedSize(this->CONTROL_BUTTON_LENGTH, this->CONTROL_BUTTON_LENGTH);
    this->rightJump->setIcon(IconManager::rightJumpIcon());
    this->rightJump->setIconSize(this->CONTROL_BUTTON_ICON_SIZE);

    this->volumeUpButton->setFixedSize(this->CONTROL_BUTTON_LENGTH, this->CONTROL_BUTTON_LENGTH);
    this->volumeUpButton->setIcon(IconManager::volumeUpIcon());
    this->volumeUpButton->setIconSize(this->CONTROL_BUTTON_ICON_SIZE);

    this->volumeDownButton->setFixedSize(this->CONTROL_BUTTON_LENGTH, this->CONTROL_BUTTON_LENGTH);
    this->volumeDownButton->setIcon(IconManager::volumeDownIcon());
    this->volumeDownButton->setIconSize(this->CONTROL_BUTTON_ICON_SIZE);
}

void AudioCard::customizeSliders() const {
    this->flowController->setFixedSize(this->NAME_LABEL_WIDTH, this->NAME_LABEL_HEIGHT);
    this->flowController->setAttribute(Qt::WA_TranslucentBackground);
    this->flowController->setStyleSheet("background: rgba(255, 255, 255, 0);");
}

void AudioCard::changeButtonUIWhenClicked(QPushButton* button) const {
    if (this->filePath.isNull() || !button)return;
    button->setStyleSheet("background: rgba(53, 53, 54, 0.8);");
    QTimer::singleShot(
        100, button, [button] {
            button->setStyleSheet("");
        }
    );
}

// Functional Activities
void AudioCard::jumpLeftForFiveUnit() const {
    if (player->playbackState() == QMediaPlayer::StoppedState)return;
    this->changeButtonUIWhenClicked(qobject_cast<QPushButton* >(sender())); // click effect.
    this->player->setPosition(
        clamp(this->player->position() - 5000ll, 0ll, this->player->duration())
    );
}

void AudioCard::jumpRightForFiveUnit() const {
    if (player->playbackState() == QMediaPlayer::StoppedState)return;
    this->changeButtonUIWhenClicked(qobject_cast<QPushButton* >(sender())); // Click effect.
    this->player->setPosition(
        clamp(this->player->position() + 5000ll, 0ll, this->player->duration())
    );
}

void AudioCard::pausePlayAction() const {
    this->changeButtonUIWhenClicked(qobject_cast<QPushButton* >(sender())); // Click Effect.
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        this->pause_resume->setIcon(IconManager::playButtonIcon());
        this->pause_resume->setIconSize(CONTROL_BUTTON_ICON_SIZE);
        this->player->pause();
    }else {
        this->pause_resume->setIcon(IconManager::pauseButtonIcon());
        this->pause_resume->setIconSize(CONTROL_BUTTON_ICON_SIZE);
        this->player->play();
    }
}

void AudioCard::getRunTime(const qint64 duration) const {
    const long long dura = duration/1000;

    this->flowController->setValue(static_cast<int>(dura));
    const long minutes = dura/60;
    const int seconds = static_cast<int>(dura)%60;

    this->playTime->setText(
        QString("%1 : %2").arg(minutes).arg(seconds, 2, 10, QChar('0'))
    );
}

void AudioCard::volumeUpAction() const {
    if (player->playbackState() != QMediaPlayer::PlayingState)return;
    this->changeButtonUIWhenClicked(qobject_cast<QPushButton* >(sender()));
    this->output->setVolume(clamp(this->output->volume() + 0.1f, 0.0f, 1.0f));
}

void AudioCard::volumeDownAction() const {
    if (player->playbackState() != QMediaPlayer::PlayingState)return;
    this->changeButtonUIWhenClicked(qobject_cast<QPushButton* >(sender()));
    this->output->setVolume(clamp(this->output->volume() - 0.1f, 0.0f, 1.0f));
}
