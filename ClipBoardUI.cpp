//
// Created by sujal-stark on 8/12/25.
//

#include <QMimeData>
#include <QClipboard>
#include <QVariant>

// custom import
#include "Constants.h"
#include "ClipBoardUI.h"
#include "ItemWidget.h"

using namespace std;

ClipBoardUI::ClipBoardUI() {
    this->setLayout(this->masterLayout);
    this->widgetBehaviourSelection();
    this->constructUI();
    this->clipBoard = QApplication::clipboard();
    this->setActions();
    this->setCustomStyle();
}

void ClipBoardUI::constructUI() const {
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

void ClipBoardUI::widgetBehaviourSelection() const {
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

void ClipBoardUI::handleIncomingItems() {
    if (
        const QMimeData *currentMime_data = this->clipBoard->mimeData(QClipboard::Clipboard);
        currentMime_data->hasText()
    ) {
        const QString currentText = currentMime_data->text();
        const size_t currHash = qHash(currentText);

        if(!this->currentTextHash.contains(currHash)) {
            this->currentTextHash.insert(currHash);
            auto *textWidget = new ItemWidget();
            textWidget->setTextManagerInterfaceInputs(
                this->text_manager_interface, this->text_editor
            );
            textWidget->assignText(currentMime_data->text(), currHash); // issue

            connect(
                textWidget, &ItemWidget::textItemClickedSignal,
                this, &ClipBoardUI::textItemClickedAction
                );
            connect(
                textWidget, &ItemWidget::text_Hash_Removal_Request_Signal,
                this, &ClipBoardUI::accept_Text_Hash_Removal
                );

            this->showTextItemOnScreen(textWidget);
        }

    }else if (currentMime_data->hasImage()) {
        if (
            const auto image = convertToQImage(currentMime_data);
            !image.isNull()
        ) {
            QString imageHash = getImageObjectHash(image);

            if (!this->currentImageHash.contains(imageHash)) {
                this->currentImageHash.insert(imageHash);
                auto *imageWidget = new ItemWidget();
                imageWidget->setImageManagerInterfaceInput(this->image_manager_interface);

                imageWidget->assignImage(image, imageHash); // issue
                connect(
                    imageWidget, &ItemWidget::imageItemClickedSignal,
                    this, &ClipBoardUI::imageItemClickedAction
                    );
                connect(
                    imageWidget, &ItemWidget::image_Hash_Removal_Request_Signal,
                    this, &ClipBoardUI::accept_Image_Hash_Removal
                    );
                this->showImageOnScreen(imageWidget);
            }
        }
    }
}


void ClipBoardUI::setActions() const {
    connect(
        this->clipBoard, &QClipboard::dataChanged,
        this, &ClipBoardUI::handleIncomingItems
    );
}

void ClipBoardUI::showTextItemOnScreen(ItemWidget *item) const {
    if (item != nullptr) {
        // New Text On top
        this->textScrollAreaInnerLayout->insertWidget(0, (QWidget *)item);
    }
}

void ClipBoardUI::showImageOnScreen(ItemWidget *image) const {
    if(image != nullptr) {
        // New Image on top
        this->imageScrollAreaInnerLayout->insertWidget(0, (QWidget *)image);
    }
}


void ClipBoardUI::textItemClickedAction(const QString &content) const {
    this->clipBoard->setText(content.toStdString().data());
}

void ClipBoardUI::imageItemClickedAction(const QPixmap &content) const {
    qDebug()<<this->textSectionScrollArea->size(); // shall be implemented
}

QString ClipBoardUI::getImageObjectHash(const QImage &qImage) {
    /*
     * Generates unique hashValue for a new PixMap
     */
    const uint hash = qHashBits(qImage.bits(), qImage.sizeInBytes());
    return QString::number(hash, 16);
}

QImage ClipBoardUI::convertToQImage(const QMimeData *mime_data) {
    QVariant imageVariant = mime_data->imageData();

    if (imageVariant.isValid() && imageVariant.canConvert<QImage>()) {
        return qvariant_cast<QImage>(imageVariant);
    }

    return QImage(nullptr);
}

void ClipBoardUI::setCustomStyle() {
    this->setStyleSheet(
        "background-color: rgba(43, 43, 43, 100);"
    );
    this->clipTabWidget->setStyleSheet(
        "QTabBar::tab { "
            "width: 139px; "
        "}"
    );
}

void ClipBoardUI::accept_Text_Hash_Removal(const size_t textHash) {
    if (this->currentTextHash.contains(textHash)) {
        const QMimeData *mime_data = this->clipBoard->mimeData(QClipboard::Clipboard);
        if (mime_data && mime_data->hasText() && qHash(mime_data->text()) == textHash) {
            this->clipBoard->clear(QClipboard::Clipboard); // makes the ClipBoard Empty
        }
        this->currentTextHash.erase(textHash);
    }
}

void ClipBoardUI::accept_Image_Hash_Removal(const QString &imageHash) {
    if (this->currentImageHash.contains(imageHash)) {
        const QMimeData *mime_data = this->clipBoard->mimeData(QClipboard::Clipboard);
        if (mime_data && mime_data->hasImage()) {
            const QImage image = convertToQImage(mime_data);
            if (!image.isNull() && getImageObjectHash(image) == imageHash) {
                this->clipBoard->clear(QClipboard::Clipboard);
            }
        }
        this->currentImageHash.erase(imageHash);
    }
}
