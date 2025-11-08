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
}

void ClipBoardUI::constructUI() const {
    this->masterLayout->addWidget(this->clipTabWidget);

    // tab insertion
    this->clipTabWidget->addTab(this->textSection, Constants::TEXT_SECTION); // Text
    this->textSection->setLayout(this->textSectionLayout);
    this->textSectionLayout->setSpacing(0);
    this->textSectionLayout->addWidget(
        this->textSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
    this->textSectionScrollArea->setWidget(this->textHolderFrame);
    this->textHolderFrame->setLayout(this->textScrollAreaInnerLayout);

    this->clipTabWidget->addTab(this->imageSection, Constants::IMAGE_SECTION); // Image
    this->imageSection->setLayout(this->imageSectionLayout);
    this->imageSectionLayout->setSpacing(0);
    this->imageSectionLayout->addWidget(
        this->imageSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
    this->imageSectionScrollArea->setWidget(this->imageHolderFrame);
    this->imageHolderFrame->setLayout(this->imageScrollAreaInnerLayout);

    this->clipTabWidget->addTab(this->videoSection, Constants::VIDEO_SECTION);
    this->videoSection->setLayout(this->videoSectionLayout);
    this->videoSectionLayout->setSpacing(0);
    this->videoSectionLayout->addWidget(
        this->videoSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
    this->videoSectionScrollArea->setWidget(this->videoHolderFrame);
    this->videoHolderFrame->setLayout(this->videoScrollAreaInnerLayout);

    this->clipTabWidget->addTab(this->audioSection, Constants::AUDIO_SECTION);
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
        const QMimeData *currentMime_data = this->clipBoard->mimeData(QClipboard::Selection);
        currentMime_data->hasText()
    ) {
        // sending data
        this->text_manager_interface.setCurrentCopiedText(currentMime_data->text().toStdString());
        this->text_manager_interface.addNewTextToQueue();

        // Receiving data
        ItemWidget* outputWidget =  this->text_manager_interface.getCurrentCopiedText();

        if (outputWidget != nullptr) {
            connect(
                outputWidget, &ItemWidget::textItemClickedSignal,
                this, &ClipBoardUI::textItemClickedAction
            );
            this->showItemOnScreen(outputWidget);
        } // final data sent to UI

    }else if (currentMime_data->hasImage()) {
        if (
            const auto image = qvariant_cast<QImage>(currentMime_data->imageData());
            !image.isNull()
        ) {
            this->image_manager_interface.setCopiedImage(image); // sending data
            this->image_manager_interface.addImageToQueue();

            // Receiving data

            if (
                ItemWidget *outputImageLabel = this->image_manager_interface.getPixmap();
                outputImageLabel != nullptr
            ) {
                connect(
                    outputImageLabel, &ItemWidget::imageItemClickedSignal,
                    this, &ClipBoardUI::imageItemClickedAction
                );
                this->showImageOnScreen(outputImageLabel);
            } // final data sent to UI
        }
    }
}


void ClipBoardUI::setActions() const {
    connect(
        this->clipBoard, &QClipboard::dataChanged,
        this, &ClipBoardUI::handleIncomingItems
    );
}

void ClipBoardUI::showItemOnScreen(ItemWidget *item) const {
    if (item != nullptr) {
        // New Text On top
        this->textScrollAreaInnerLayout->insertWidget(0,item);
    }
}

void ClipBoardUI::showImageOnScreen(ItemWidget *image) const {
    if(image != nullptr) {
        // New Image on top
        this->imageScrollAreaInnerLayout->insertWidget(0, image);
        image->show();
    }
}


void ClipBoardUI::textItemClickedAction(const string &content) const {
    this->clipBoard->setText(content.data());
}

void ClipBoardUI::imageItemClickedAction(const QPixmap &content) const {
    qDebug()<<this->textSectionScrollArea->size(); // shall be implemented
}


