//
// Created by sujal-stark on 8/12/25.
//

#include <QMimeData>
#include <QClipboard>
#include <QVariant>

// custom import
#include "../Util/Constants.h"
#include "ClipBoardInterface.h"
#include "../Widgets/ItemWidget.h"

using namespace std;

ClipBoardInterface::ClipBoardInterface() {
    this->setLayout(this->masterLayout);
    this->widgetBehaviourSelection();
    this->constructUI();
    this->clipBoard = QApplication::clipboard();
    this->setActions();
    this->setCustomStyle();
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

void ClipBoardInterface::handleTextItem(const QSharedPointer<QString>& textPtr) {
    const QString& currentText = *textPtr;

    if (currentText.isEmpty())return;

    const size_t currHash = qHash(currentText);

    if(!this->currentTextHash.contains(currHash)) {
        this->currentTextHash.insert(currHash);
        auto *textWidget = new ItemWidget();
        textWidget->setTextManagerInterfaceInputs(
            this->text_manager_interface, this->text_editor
        );
        textWidget->assignText(currentText, currHash); // issue

        connect(
            textWidget, &ItemWidget::textItemClickedSignal,
            this, &ClipBoardInterface::textItemClickedAction
        );

        connect(
            textWidget, &ItemWidget::text_Hash_Removal_Request_Signal,
            this, &ClipBoardInterface::accept_Text_Hash_Removal
        );

        connect(
            textWidget, &ItemWidget::textHashReplacementSignal,
            this, &ClipBoardInterface::acceptTextHashReplacement
        );

        this->showTextItemOnScreen(textWidget);
    }
}

void ClipBoardInterface::handleImageObjectItem(const QSharedPointer<QImage> &imagePtr) {
    const QImage& image = *imagePtr;
    QString imageHash = getImageObjectHash(image);

    if (!this->currentImageHash.contains(imageHash)) {
        this->currentImageHash.insert(imageHash);
        auto *imageWidget = new ItemWidget();
        imageWidget->setImageManagerInterfaceInput(this->image_manager_interface);

        imageWidget->assignImage(image, imageHash); // issue
        connect(
            imageWidget, &ItemWidget::imageItemClickedSignal,
            this, &ClipBoardInterface::imageItemClickedAction
            );
        connect(
            imageWidget, &ItemWidget::image_Hash_Removal_Request_Signal,
            this, &ClipBoardInterface::accept_Image_Hash_Removal
            );
        this->showImageOnScreen(imageWidget);
    }
}

void ClipBoardInterface::handleIncomingItems() const {
    const QMimeData *currentMime_data = this->clipBoard->mimeData(QClipboard::Clipboard);
    this->mimeDataAnalyzer->mimeObjectReceiver(*currentMime_data);
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
        this->mimeDataAnalyzer, &MimeDataAnalyzer::imageObjectReleaseSignal,
        this, &ClipBoardInterface::handleImageObjectItem
    );
}

void ClipBoardInterface::showTextItemOnScreen(ItemWidget *item) const {
    // New Text On top
    this->textScrollAreaInnerLayout->insertWidget(0, (QWidget *)item);
}

void ClipBoardInterface::showImageOnScreen(ItemWidget *image) const {
    // New Image on top
    this->imageScrollAreaInnerLayout->insertWidget(0, (QWidget *)image);
}


void ClipBoardInterface::textItemClickedAction(const QString &content) const {
    this->clipBoard->setText(content.toStdString().data());
}

void ClipBoardInterface::imageItemClickedAction(const QPixmap &content) const {
    qDebug()<<this->textSectionScrollArea->size(); // shall be implemented
}

QString ClipBoardInterface::getImageObjectHash(const QImage &qImage) {
    /*
     * Generates unique hashValue for a new PixMap
     */
    const uint hash = qHashBits(qImage.bits(), qImage.sizeInBytes());
    return QString::number(hash, 16);
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

void ClipBoardInterface::accept_Text_Hash_Removal(const size_t textHash) {
    if (this->currentTextHash.contains(textHash)) {
        const QMimeData *mime_data = this->clipBoard->mimeData(QClipboard::Clipboard);
        if (mime_data && mime_data->hasText() && qHash(mime_data->text()) == textHash) {
            this->clipBoard->clear(QClipboard::Clipboard); // makes the ClipBoard Empty
        }
        this->currentTextHash.erase(textHash);
    }
}

void ClipBoardInterface::acceptTextHashReplacement(const size_t currentHash, const size_t nextHash) {
    if (this->currentTextHash.contains(currentHash)) {
        this->currentTextHash.erase(currentHash);
        this->currentTextHash.insert(nextHash);
    }
}

void ClipBoardInterface::accept_Image_Hash_Removal(const QString &imageHash) {
    if (this->currentImageHash.contains(imageHash)) {
        const QMimeData *mime_data = this->clipBoard->mimeData(QClipboard::Clipboard);
        if (mime_data && mime_data->hasImage()) {
            const QImage image = MimeDataAnalyzer::convertToQImage(*mime_data);
            if (!image.isNull() && getImageObjectHash(image) == imageHash) {
                this->clipBoard->clear(QClipboard::Clipboard);
            }
        }
        this->currentImageHash.erase(imageHash);
    }
}
