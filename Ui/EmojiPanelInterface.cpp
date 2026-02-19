//
// Created by sujal-stark on 9/28/25.
//

#include "../Util/Constants.h"
#include "EmojiPanelInterface.h"
#include "../Widgets/EmojiWidget.h"
#include "QDebug"
#include "QHeaderView"
#include <QFont>

EmojiPanelInterface::EmojiPanelInterface() {
    this->setLayout(this->masterLayout);
    this->propertyHandler();
    this->constructUI();
    this->signalConnector();
    this->setCustomStyle();
}

void EmojiPanelInterface::propertyHandler() {
    this->emojiFont = QFont(QString::fromStdString(Constants::EMOJI_FONT));
    emojiFont.setPointSize(Constants::EMOJI_FONT_SIZE);

    // reactionSectionGrid
    this->reactionSectionGrid->setColumnCount(6);
    this->reactionSectionGrid->setRowCount(20);

    this->reactionSectionGrid->setShowGrid(false);
    this->reactionSectionGrid->horizontalHeader()->setVisible(false);
    this->reactionSectionGrid->verticalHeader()->setVisible(false);

    this->reactionSectionGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->reactionSectionGrid->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->reactionSectionGrid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->reactionSectionGrid->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->reactionSectionGrid->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // animalSectionGrid
    this->animalSectionGrid->setColumnCount(6);
    this->animalSectionGrid->setRowCount(20);

    this->animalSectionGrid->setShowGrid(false);
    this->animalSectionGrid->horizontalHeader()->setVisible(false);
    this->animalSectionGrid->verticalHeader()->setVisible(false);

    this->animalSectionGrid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->animalSectionGrid->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    this->animalSectionGrid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->animalSectionGrid->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->animalSectionGrid->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void EmojiPanelInterface::constructUI() const {
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

void EmojiPanelInterface::signalConnector() const {
    connect(
    &this->eGenerator, &EmojiGenerator::emojiGeneratedSignal, this, &EmojiPanelInterface::emojiReceivedAction,
    Qt::QueuedConnection
        );
    connect(
        this->emojiPanel, &QTabWidget::currentChanged, this, &EmojiPanelInterface::tabWidgetChangedAction
    );
}


void EmojiPanelInterface::emojiReceivedAction(const int count, int tab, const QSharedPointer<QString> &emojiLabel) {
    const int i = (count / 6), j = count % 6;
    auto *label = new EmojiWidget(*emojiLabel, this->reactionSectionGrid); // access by Value
    label->setFont(emojiFont);
    label->setFixedSize(80, 80);
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);

    switch (tab) {
        case 0: {
            break;
        }
        case 1: {
            this->reactionSectionGrid->setColumnWidth(j, Constants::EMOJI_CELL_WIDTH);
            this->reactionSectionGrid->setRowHeight(i, Constants::EMOJI_CELL_HEIGHT);
            this->reactionSectionGrid->setCellWidget(i, j, label);
            break;
        }
        case 2: {
            this->animalSectionGrid->setColumnWidth(j, Constants::EMOJI_CELL_WIDTH);
            this->animalSectionGrid->setRowHeight(i, Constants::EMOJI_CELL_HEIGHT);
            this->animalSectionGrid->setCellWidget(i, j, label);
            break;
        }
        case 3: {
            break;
        }
        case 4: {
            break;
        }
        case 5: {
            break;
        }
        case 6: {
            break;
        }
        case 7: {
            break;
        }
        default: break;
    }
    this->update();
}

void EmojiPanelInterface::tabWidgetChangedAction(const int tabIndex) {
    this->eGenerator.acceptEmojiGeneratingResources(tabIndex, this->emojiCodes[tabIndex]);
    this->eGenerator.start();
}

void EmojiPanelInterface::setCustomStyle() {
    this->setStyleSheet(
        "background-color: rgba(43, 43, 43, 100);"
    );
    this->emojiPanel->setStyleSheet(
        "QTabBar::tab { "
            "width: 160px; "  // Fixed width for each tab
        "}"
    );
}



