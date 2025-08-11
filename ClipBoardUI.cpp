//
// Created by sujal-stark on 8/12/25.
//

#include "ClipBoardUI.h"
#include "Constants.h"

ClipBoardUI::ClipBoardUI() {
    this->setLayout(this->masterLayout);
    this->constructUI();
}

void ClipBoardUI::constructUI() {
    this->masterLayout->addWidget(this->clipTabWidget);

    // tab insertion
    this->clipTabWidget->addTab(this->textSection, Constants::TEXT_SECTION);
    this->textSection->setLayout(this->textSectionLayout);
    this->textSectionLayout->setSpacing(0);
    this->textSectionLayout->addWidget(
        this->textSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );

    this->clipTabWidget->addTab(this->imageSection, Constants::IMAGE_SECTION);
    this->imageSection->setLayout(this->imageSectionLayout);
    this->imageSectionLayout->setSpacing(0);
    this->imageSectionLayout->addWidget(
        this->imageSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );

    this->clipTabWidget->addTab(this->videoSection, Constants::VIDEO_SECTION);
    this->videoSection->setLayout(this->videoSectionLayout);
    this->videoSectionLayout->setSpacing(0);
    this->videoSectionLayout->addWidget(
        this->videoSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );

    this->clipTabWidget->addTab(this->audioSection, Constants::AUDIO_SECTION);
    this->audioSection->setLayout(this->audioSectionLayout);
    this->audioSectionLayout->setSpacing(0);
    this->audioSectionLayout->addWidget(
        this->audioSectionScrollArea, Qt::AlignmentFlag::AlignCenter
    );
}

