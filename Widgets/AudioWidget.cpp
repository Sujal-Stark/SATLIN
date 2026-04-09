//
// Created by sujal-stark on 3/14/26.
//

#include "AudioWidget.h"

#include <QMouseEvent>

#include "../Util/Constants.h"
#include "../ManagerSources/IconManager.h"

AudioWidget::AudioWidget() {
    this->setLayout(this->masterLayout);
    this->setFixedWidth(Constants::ITEM_WIDGET_WIDTH);
    this->stylizeButtons();
    this->construct();
    this->establishConnections();
    this->stylize();
}

void AudioWidget::establishConnections() {
    connect(
        this->editButton, &QPushButton::clicked,
        this, &AudioWidget::editButtonClicked
    );

    connect(
        this->deleteButton, &QPushButton::clicked,
        this, &AudioWidget::deleteButtonClicked
    );

    connect(
        this->saveButton, &QPushButton::clicked,
        this, &AudioWidget::saveButtonClicked
    );
}

void AudioWidget::construct() const {
    this->masterLayout->addWidget(this->mainFrame, Qt::AlignmentFlag::AlignCenter);
    this->mainFrame->setLayout(this->masterInnerLayout);

    this->masterInnerLayout->addLayout(this->contentHolder);
    this->contentHolder->addStretch();

    this->masterInnerLayout->addLayout(this->buttonHolder);
    this->buttonHolder->setSpacing(10);
    this->buttonHolder->addStretch();
    this->buttonHolder->addWidget(this->deleteButton, Qt::AlignmentFlag::AlignRight);
    this->buttonHolder->addWidget(this->editButton, Qt::AlignmentFlag::AlignRight);
    this->buttonHolder->addWidget(this->saveButton, Qt::AlignmentFlag::AlignRight);
}

void AudioWidget::stylizeButtons() const {
    this->editButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->editButton->setIcon(IconManager::editIcon());

    this->deleteButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->deleteButton->setIcon(IconManager::cancelIcon());

    this->saveButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->saveButton->setIcon(IconManager::saveIcon());
}

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

void AudioWidget::editButtonClicked() const {
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

void AudioWidget::saveButtonClicked() const {
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
    this->stylize();
}

void AudioWidget::stylize() {
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
}
