//
// Created by sujal-stark on 9/28/25.
//

#include "Constants.h"
#include "EmojiBoardUI.h"

EmojiBoardUI::EmojiBoardUI() {
    this->setLayout(this->masterLayout);
    this->constructUI();
}

void EmojiBoardUI::constructUI() const {
    // Panel addition
    this->masterLayout->addWidget(this->emojiPanel);

    // Recent Section
    this->emojiPanel->addTab(this->emojiRecentSection, Constants::RECENT);
    this->emojiRecentSection->setLayout(this->recentSectionLayout);
    this->recentSectionLayout->setSpacing(0);
    this->recentSectionLayout->addWidget(
        this->recentSectionScrollArea, Qt::AlignmentFlag::AlignCenter);
    this->recentSectionScrollArea->setWidget(this->recentSectionFrames);
    this->recentSectionFrames->setLayout(this->recentSectionGrid);

    // Reaction Section
    this->emojiPanel->addTab(this->emojiReactionSection, Constants::REACTION);
    this->emojiReactionSection->setLayout(this->reactionSectionLayout);
    this->reactionSectionLayout->setSpacing(0);
    this->reactionSectionLayout->addWidget(
        this->reactionSectionScrollArea, Qt::AlignmentFlag::AlignCenter);
    this->reactionSectionScrollArea->setWidget(this->reactionSectionFrames);
    this->reactionSectionFrames->setLayout(this->reactionSectionGrid);

    // Animal Section
    this->emojiPanel->addTab(this->emojiAnimalSection, Constants::ANIMALS);
    this->emojiAnimalSection->setLayout(this->animalSectionLayout);
    this->animalSectionLayout->setSpacing(0);
    this->animalSectionLayout->addWidget(
        this->animalSectionScrollArea, Qt::AlignmentFlag::AlignCenter);
    this->animalSectionScrollArea->setWidget(this->animalSectionFrames);
    this->animalSectionFrames->setLayout(this->animalSectionGrid);

    // Food and Drinks Section
    this->emojiPanel->addTab(this->emojiFoodSection, Constants::FOODS);
    this->emojiFoodSection->setLayout(this->foodSectionLayout);
    this->foodSectionLayout->setSpacing(0);
    this->foodSectionLayout->addWidget(
        this->foodSectionScrollArea, Qt::AlignmentFlag::AlignCenter);
    this->foodSectionScrollArea->setWidget(this->foodSectionFrames);
    this->foodSectionFrames->setLayout(this->foodSectionGrid);

    // Places and Tour
    this->emojiPanel->addTab(this->emojiPlaceSection, Constants::PLACES);
    this->emojiPlaceSection->setLayout(this->placesSectionLayout);
    this->placesSectionLayout->setSpacing(0);
    this->placesSectionLayout->addWidget(
        this->placesSectionScrollArea, Qt::AlignmentFlag::AlignCenter);
    this->placesSectionScrollArea->setWidget(this->placesSectionFrames);
    this->placesSectionFrames->setLayout(this->placesSectionGrid);
}
