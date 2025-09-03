//
// Created by sujal-stark on 8/12/25.
//

#include <iostream>
#include <QMimeData>
#include <QClipboard>
#include <QHashFunctions>

// custom import
#include "Constants.h"
#include "ClipBoardUI.h"


using namespace std;

ClipBoardUI::ClipBoardUI() {
    this->setLayout(this->masterLayout);
    this->widgetBehaviourSelection();
    this->constructUI();
    this->clipBoard = QApplication::clipboard();
    connect(
        this->clipBoard, &QClipboard::dataChanged, this, &ClipBoardUI::addNewTextToQueue
    );
}

void ClipBoardUI::constructUI() const {
    this->masterLayout->addWidget(this->clipTabWidget);

    // tab insertion
    this->clipTabWidget->addTab(this->textSection, Constants::TEXT_SECTION);
    this->textSection->setLayout(this->textSectionLayout);
    this->textSectionLayout->setSpacing(0);
    this->textSectionLayout->addWidget(
        this->textSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
    this->textSectionScrollArea->setWidget(this->textHolderFrame);
    this->textHolderFrame->setLayout(this->textScrollAreaInnerLayout);

    this->clipTabWidget->addTab(this->imageSection, Constants::IMAGE_SECTION);
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
    this->imageSectionScrollArea->setWidgetResizable(true);
    this->videoSectionScrollArea->setWidgetResizable(true);
    this->audioSectionScrollArea->setWidgetResizable(true);
}

string ClipBoardUI::getCurrentCopiedText() const{
    const QMimeData *mimeData = this->clipBoard->mimeData(QClipboard::Clipboard);

    if (mimeData->hasText()) {
        return mimeData->text().toStdString();
    }if (mimeData->hasHtml()) {
        return mimeData->html().toStdString();
    }
    return "";
}

QLabel* ClipBoardUI::createTextLabel(){
    auto currText = getCurrentCopiedText();

    if (!currText.empty() && currentTextHash != qHash(currText)) {
        std::cout<<"I am in the method"<<endl;
        std::cout <<currentTextHash<<" "<<qHash(currText);
        currentTextHash = qHash(currText);
        auto *label = new QLabel(currText.data());
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label->setFixedHeight(40);
        return label;
    }

    return nullptr;
}

void ClipBoardUI::addNewTextToQueue() {
    auto textLabel = this->createTextLabel();

    if (textLabel != nullptr) {
        this->textQueue.push(textLabel);
        this->showTextOnScreen();
    }
}

void ClipBoardUI::showTextOnScreen() {
    if (!this->textQueue.empty()) {
        this->textScrollAreaInnerLayout->insertWidget(0,this->textQueue.back());
    }
}
