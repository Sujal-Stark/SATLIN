//
// Created by sujal-stark on 9/28/25.
//

#include "Constants.h"
#include "EmojiBoardUI.h"
#include "QDebug"
#include "QHeaderView"
#include <QFont>

EmojiBoardUI::EmojiBoardUI() {
    this->setLayout(this->masterLayout);
    this->propertyHandler();
    this->constructUI();
    this->signalConnector();
    this->eGenerator.start();
}

void EmojiBoardUI::propertyHandler() const {
    this->reactionSectionGrid->setShowGrid(false);
    this->reactionSectionGrid->horizontalHeader()->setVisible(false);
    this->reactionSectionGrid->verticalHeader()->setVisible(false);

    this->reactionSectionGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->reactionSectionGrid->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->reactionSectionGrid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->reactionSectionGrid->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->reactionSectionGrid->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void EmojiBoardUI::constructUI() const {
    // Panel addition
    this->masterLayout->addWidget(this->emojiPanel);

    // Recent Section
    this->emojiPanel->addTab(this->emojiRecentSection, Constants::RECENT);
    this->emojiRecentSection->setLayout(this->recentSectionLayout);
    this->recentSectionLayout->setSpacing(0);
    this->recentSectionLayout->addWidget(
        this->recentSectionGrid, Qt::AlignmentFlag::AlignCenter);

    // Reaction Section
    this->emojiPanel->addTab(this->emojiReactionSection, Constants::REACTION);
    this->emojiReactionSection->setLayout(this->reactionSectionLayout);
    this->reactionSectionLayout->setSpacing(0);
    this->reactionSectionLayout->addWidget(
        this->reactionSectionGrid, Qt::AlignmentFlag::AlignCenter);

    // Animal Section
    this->emojiPanel->addTab(this->emojiAnimalSection, Constants::ANIMALS);
    this->emojiAnimalSection->setLayout(this->animalSectionLayout);
    this->animalSectionLayout->setSpacing(0);
    this->animalSectionLayout->addWidget(
        this->animalSectionGrid, Qt::AlignmentFlag::AlignCenter);

    // Food and Drinks Section
    this->emojiPanel->addTab(this->emojiFoodSection, Constants::FOODS);
    this->emojiFoodSection->setLayout(this->foodSectionLayout);
    this->foodSectionLayout->setSpacing(0);
    this->foodSectionLayout->addWidget(
        this->foodSectionGrid, Qt::AlignmentFlag::AlignCenter);

    // Places and Tour
    this->emojiPanel->addTab(this->emojiPlaceSection, Constants::PLACES);
    this->emojiPlaceSection->setLayout(this->placesSectionLayout);
    this->placesSectionLayout->setSpacing(0);
    this->placesSectionLayout->addWidget(
        this->placesSectionGrid, Qt::AlignmentFlag::AlignCenter);

    // Activity
    this->emojiPanel->addTab(this->emojiActivitySection, Constants::ACTIVITY);
    this->emojiActivitySection->setLayout(this->activitySectionLayout);
    this->activitySectionLayout->setSpacing(0);
    this->activitySectionLayout->addWidget(
        this->activitySectionGrid, Qt::AlignmentFlag::AlignCenter);

    // Objects
    this->emojiPanel->addTab(this->emojiObjectsSection, Constants::OBJECTS_HEADER);
    this->emojiObjectsSection->setLayout(this->objectSectionLayout);
    this->objectSectionLayout->setSpacing(0);
    this->objectSectionLayout->addWidget(
        this->objectSectionGrid, Qt::AlignmentFlag::AlignCenter);

    // Symbols
    this->emojiPanel->addTab(this->emojiSymbolSection, Constants::SYMBOLS);
    this->emojiSymbolSection->setLayout(this->symbolSectionLayout);
    this->symbolSectionLayout->setSpacing(0);
    this->symbolSectionLayout->addWidget(
        this->symbolSectionGrid, Qt::AlignmentFlag::AlignCenter);
}

void EmojiBoardUI::signalConnector() const {
    connect(
    &this->eGenerator, &EmojiGenerator::emojiGeneratedSignal, this, &EmojiBoardUI::emojiReceivedAction
        );
}


void EmojiBoardUI::emojiReceivedAction(const QSharedPointer<std::map<int, std::vector<QString>>>& emojiWidgets) {
    int j = 0;
    QFont emojiFont(Constants::EMOJI_FONT.data());
    emojiFont.setPointSize(Constants::EMOJI_FONT_SIZE);
    auto const &reactions = (*emojiWidgets)[1];
    this->reactionSectionGrid->setColumnCount(6);
    this->reactionSectionGrid->setRowCount((reactions.size()/6) + 1);
    for (int i = 0; i < reactions.size(); i++) {
        this->reactionSectionGrid->setColumnWidth(j, Constants::EMOJI_CELL_WIDTH);
        this->reactionSectionGrid->setRowHeight(i%6, Constants::EMOJI_CELL_HEIGHT);
        auto *label = new QLabel(this);
        label->setFont(emojiFont);
        label->setText(reactions[i]);
        label->setFixedSize(80, 80);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        this->reactionSectionGrid->setCellWidget(j, (i%6), label);
        if ((i + 1) % 6 == 0)j++;
    }
    this->update();
}


