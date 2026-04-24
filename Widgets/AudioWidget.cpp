//
// Created by sujal-stark on 3/14/26.
//

#include "AudioWidget.h"

#include <QMouseEvent>

#include "../Util/Constants.h"
#include "../ManagerSources/IconManager.h"

AudioWidget::AudioWidget() = default;

// Widget Internal Operations
void AudioWidget::assignDrivers(const shared_ptr<AudioManagerInterface> &interface) {
    if (interface == nullptr)throw invalid_argument("Invalid Drivers.");
    this->audioManagerInterface = interface;
}

void AudioWidget::assignAudio(
    const int saveStat, qint32 fileSize, const QString& filePath, const QString& ext,
    const QString& stamp, const QString& hash
) {
    this->audioLabel = AudioManagerInterface::createAudioLabel(
        filePath, hash, saveStat
    );

    if (!this->audioLabel.isNull()) {
        this->contentHolder->addWidget(
            this->audioLabel, Qt::AlignmentFlag::AlignCenter
        );
    }
}

void AudioWidget::editButtonClicked() {
    /*Audio Editing Will be introduced Later*/

    qDebug()<<this->audioLabel->getAudioObjectHash();
}

void AudioWidget::deleteButtonClicked() {
    if (this->audioManagerInterface->removeAudioItem(this->audioLabel->getAudioObjectHash())) {
        emit this->audioRemovedConfirmation(
            this->audioLabel->getAudioObjectHash(), this->audioLabel->getAudioFileName(),
            this->audioLabel->getMode()
        );
    }
    this->deleteLater();
}

void AudioWidget::saveButtonClicked() {
    /*Audio Saving Will be introduced Later*/

    qDebug()<<this->audioLabel->getAudioObjectHash();
}

void AudioWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MouseButton::LeftButton) {
        const QString filePath = this->audioManagerInterface->releaseAudioData(
            this->audioLabel->getAudioObjectHash()
        );
        if (!filePath.isEmpty())emit this->audioItemClickedSignal(QUrl::fromLocalFile(filePath));
    }

    // changes the label color
    this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(54, 54, 54, 150);"
    );
}

void AudioWidget::mouseReleaseEvent(QMouseEvent *event) {
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
}
