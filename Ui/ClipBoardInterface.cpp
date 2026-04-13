//
// Created by sujal-stark on 8/12/25.
//

#include <QMimeData>
#include <QClipboard>
#include <QVariant>

// custom import
#include "../Util/Constants.h"
#include "ClipBoardInterface.h"

#include <QFile>

#include "../Widgets/AudioWidget.h"
#include "../Widgets/ImageWidget.h"
#include "../Widgets/ItemWidget.h"

using namespace std;

ClipBoardInterface::ClipBoardInterface() {
    this->setLayout(this->masterLayout);
    this->widgetBehaviourSelection();
    this->constructUI();
    this->clipBoard = QApplication::clipboard();
    this->setActions();
    this->setCustomStyle();
    this->mimeDataAnalyzer->driverReceiver(this->itemRepository);
    this->imageManagerInterface->assignDrivers(this->itemRepository);
    this->audioManagerInterface->assignDrivers(this->itemRepository);
}

void ClipBoardInterface::constructUI() const {
    this->masterLayout->addWidget(this->clipTabWidget);

    // tab insertion
    this->clipTabWidget->addTab(
        this->textSection, IconManager::textIcon(), Constants::TEXT_SECTION
    ); // Text
    this->textSection->setLayout(this->textSectionLayout);
    this->textSectionLayout->setSpacing(0);
    this->textSectionLayout->addWidget(
        this->textSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
    this->textSectionScrollArea->setWidget(this->textHolderFrame);
    this->textHolderFrame->setLayout(this->textScrollAreaInnerLayout);

    this->clipTabWidget->addTab(
        this->imageSection, IconManager::photoIcon(), Constants::IMAGE_SECTION
    ); // Image
    this->imageSection->setLayout(this->imageSectionLayout);
    this->imageSectionLayout->setSpacing(0);
    this->imageSectionLayout->addWidget(
        this->imageSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
    this->imageSectionScrollArea->setWidget(this->imageHolderFrame);
    this->imageHolderFrame->setLayout(this->imageScrollAreaInnerLayout);

    this->clipTabWidget->addTab(
        this->videoSection, IconManager::videoIcon(), Constants::VIDEO_SECTION
    );
    this->videoSection->setLayout(this->videoSectionLayout);
    this->videoSectionLayout->setSpacing(0);
    this->videoSectionLayout->addWidget(
        this->videoSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
    this->videoSectionScrollArea->setWidget(this->videoHolderFrame);
    this->videoHolderFrame->setLayout(this->videoScrollAreaInnerLayout);

    this->clipTabWidget->addTab(
        this->audioSection, IconManager::audioIcon(), Constants::AUDIO_SECTION
    );
    this->audioSection->setLayout(this->audioSectionLayout);
    this->audioSectionLayout->setSpacing(0);
    this->audioSectionLayout->addWidget(
        this->audioSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
    this->audioSectionScrollArea->setWidget(this->audioHolderFrame);
    this->audioHolderFrame->setLayout(this->audioScrollAreaInnerLayout);
}

void ClipBoardInterface::widgetBehaviourSelection() const {
    // Frame
    this->textHolderFrame->setFrameShape(QFrame::Shape::StyledPanel);
    this->imageHolderFrame->setFrameShape(QFrame::Shape::StyledPanel);
    this->videoHolderFrame->setFrameShape(QFrame::Shape::StyledPanel);
    this->audioHolderFrame->setFrameShape(QFrame::Shape::StyledPanel);

    // Scroll Area
    this->textSectionScrollArea->setWidgetResizable(true);
    this->textSectionScrollArea->setStyleSheet(
        "QScrollBar:vertical {width: 0px;}"
        "QScrollBar:horizontal{height: 0px;}"
    );
    this->imageSectionScrollArea->setWidgetResizable(true);
    this->imageSectionScrollArea->setStyleSheet(
        "QScrollBar:vertical {width: 0px;}"
        "QScrollBar:horizontal{height: 0px;}"
    );
    this->videoSectionScrollArea->setWidgetResizable(true);
    this->audioSectionScrollArea->setWidgetResizable(true);

    // layout
    this->textScrollAreaInnerLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    this->textScrollAreaInnerLayout->setContentsMargins(
        Constants::WIDGET_MARGIN, Constants::WIDGET_MARGIN, Constants::WIDGET_MARGIN,
    Constants::WIDGET_MARGIN
    );

    this->imageScrollAreaInnerLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    this->imageScrollAreaInnerLayout->setContentsMargins(
        Constants::WIDGET_MARGIN, Constants::WIDGET_MARGIN, Constants::WIDGET_MARGIN,
        Constants::WIDGET_MARGIN
    );
}

void ClipBoardInterface::handleTextItem(const QString& text, const QString& hash) {
    if (text.isEmpty())return;

    auto* textWidget = new ItemWidget();
    textWidget->setTextManagerInterfaceInputs(
        this->text_manager_interface, this->itemRepository
    );
    textWidget->assignText(text, hash); // issue

    connect(
        textWidget, &ItemWidget::textItemClickedSignal,
        this, &ClipBoardInterface::textItemClickedAction
    );

    connect(
        textWidget, &ItemWidget::clipboardCleanSignal,
        this, &ClipBoardInterface::cleanClipBoard
    );

    this->showTextItemOnScreen(textWidget);
}

void ClipBoardInterface::handleImageItem(const QString& text, const QString& imageHash, const int mode) {
    auto *imageWidget = new ImageWidget();
    imageWidget->assignDrivers(this->imageManagerInterface);

    imageWidget->assignImage(text, imageHash, mode);

    connect(
        imageWidget, &ImageWidget::imageItemClickedSignal,
        this, &ClipBoardInterface::imageItemClickedAction
    );

    connect(
        imageWidget, &ImageWidget::imageRemovedConfirmation,
        this, &ClipBoardInterface::imageRemovedConfirmationAction
    );

    this->showImageOnScreen(imageWidget);
}

void ClipBoardInterface::handleAudioItem(
    const int saveStatus, const qint32 fileSize, const QString &filePath,
    const QString &ext, const QString &timeStamp, const QString &hash
) const {
    auto* widget = new AudioWidget();

    widget->assignDrivers(this->audioManagerInterface);
    widget->assignAudio(
        saveStatus, fileSize, filePath, ext, timeStamp, hash
    );

    connect(
        widget, &AudioWidget::audioItemClickedSignal,
        this, &ClipBoardInterface::audioItemClickedAction
    );

    connect(
        widget, &AudioWidget::audioRemovedConfirmation,
        this, &ClipBoardInterface::audioRemovedConfirmationAction
    );

    this->showAudioItemOnScreen(widget);
}

void ClipBoardInterface::handleIncomingItems() const {
    const QMimeData *currentMime_data = this->clipBoard->mimeData(QClipboard::Clipboard);
    this->mimeDataAnalyzer->analyzeMimeObject(*currentMime_data);
}


void ClipBoardInterface::setActions() const {
    connect(
        this->clipBoard, &QClipboard::dataChanged,
        this, &ClipBoardInterface::handleIncomingItems
    );

    connect(
        this->mimeDataAnalyzer, &MimeDataAnalyzer::textReleaseSignal,
        this, &ClipBoardInterface::handleTextItem
    );

    connect(
        this->mimeDataAnalyzer, &MimeDataAnalyzer::imageFilePathReleaseSignal,
        this, &ClipBoardInterface::handleImageItem
    );

    connect(
        this->mimeDataAnalyzer, &MimeDataAnalyzer::audioFilePathReleaseSignal,
        this, &ClipBoardInterface::handleAudioItem
    );
}

void ClipBoardInterface::showTextItemOnScreen(ItemWidget *item) const {
    this->textScrollAreaInnerLayout->insertWidget(0, item);
}

void ClipBoardInterface::showImageOnScreen(ImageWidget *image) const {
    this->imageScrollAreaInnerLayout->insertWidget(0, image);
}

void ClipBoardInterface::showAudioItemOnScreen(AudioWidget *audio) const {
    this->audioScrollAreaInnerLayout->insertWidget(0, audio);
}


void ClipBoardInterface::textItemClickedAction(const QString &content) const {
    this->clipBoard->setText(content.toStdString().data());
}

void ClipBoardInterface::imageItemClickedAction(const QImage &image) const {
    if (!image.isNull()) {
        this->clipBoard->setImage(image);
    }
}

void ClipBoardInterface::audioItemClickedAction(const QString &filePath) const {
    if (!filePath.isEmpty()) {
        const QPointer mime = new QMimeData();
        QList<QUrl> fileList;
        fileList.append(QUrl::fromLocalFile(filePath));
        mime->setUrls(fileList);
        this->clipBoard->setMimeData(mime);
    }
}

void ClipBoardInterface::setCustomStyle() {
    this->setStyleSheet(
        "background-color: rgba(43, 43, 43, 100);"
    );
    this->clipTabWidget->setStyleSheet(
        "QTabBar::tab { "
            "width: 139px; "
        "}"
    );
}

void ClipBoardInterface::imageRemovedConfirmationAction(
    const QString &imageHash, const QString& filePath, const int mode
) const {
    cleanClipBoard();

    if (
        mode == ImageManagerInterface::SAVE_STATUS_TRUE
        && !MimeDataAnalyzer::deleteImageFile(filePath)
    )qWarning()<<"Unable to delete Item";

}

void ClipBoardInterface::audioRemovedConfirmationAction(
    const QString &hashValue, const QString &filePath, int mode
) const {
    cleanClipBoard();

    if (
        mode == AudioManagerInterface::SAVE_STATUS_TRUE
        && !MimeDataAnalyzer::deleteAudioFile(filePath)
    )qWarning()<<"Unable to Delete Item";
}

void ClipBoardInterface::cleanClipBoard() const {
    this->clipBoard->clear();
}
