//
// Created by sujal-stark on 9/22/25.
//

#include "ItemWidget.h"
#include<Qt>
#include <QFileDialog>

#include "../Ui/ClipBoardInterface.h"
#include "../Util/Constants.h"

ItemWidget::ItemWidget() {
    this->setLayout(this->masterLayout);

    QSizePolicy pol = this->sizePolicy();
    pol.setVerticalPolicy(QSizePolicy::Maximum);
    pol.setHorizontalPolicy(QSizePolicy::Maximum);
    this->setSizePolicy(pol);

    ItemWidget::stylizeButtons();
    ItemWidget::stylizeLabels();
    this->stylizeFrames();
    this->createStyle();
    ItemWidget::customizeAnimationBehaviors();
};

void ItemWidget::stylizeButtons() {
    this->editButton->setObjectName("editButton");
    this->editButton->setSizeHint(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->editButton->setResizeHoverAnimationParameters(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH + 20,
        Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT,
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH,
        Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->editButton->setIcon(IconManager::editIcon());

    this->deleteButton->setObjectName("deleteButton");
    this->deleteButton->setSizeHint(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->deleteButton->setResizeHoverAnimationParameters(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH + 20,
        Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT,
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH,
        Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->deleteButton->setIcon(IconManager::cancelIcon());

    this->saveButton->setObjectName("saveButton");
    this->saveButton->setSizeHint(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->saveButton->setResizeHoverAnimationParameters(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH + 20,
        Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT,
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH,
        Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->saveButton->setIcon(IconManager::saveIcon());
}

void ItemWidget::stylizeLabels() {
    this->savePropertyCard->setFixedSize(40, 20);

    this->extensionCard->setFixedSize(40, 20);

    this->timeStampCard->setFixedSize(40, 20);
}

void ItemWidget::stylizeFrames() const {
    this->mainFrame->setFixedWidth(
        Constants::ITEM_MAIN_FRAME_WIDTH
    );
}

void ItemWidget::customizeAnimationBehaviors() {
    this->expandContractAnimation->setDuration(500);
}

void ItemWidget::construct() {
    this->masterLayout->addWidget(this->mainFrame, Qt::AlignmentFlag::AlignCenter);
    this->mainFrame->setLayout(this->masterInnerLayout);

    this->masterInnerLayout->addLayout(this->metaInfoHolder);
    this->metaInfoHolder->addWidget(
        this->savePropertyCard, Qt::AlignmentFlag::AlignLeft
    );
    this->metaInfoHolder->addWidget(
        this->extensionCard, Qt::AlignmentFlag::AlignLeft
    );
    this->metaInfoHolder->addWidget(
        this->timeStampCard, Qt::AlignmentFlag::AlignLeft
    );
    this->metaInfoHolder->addStretch();

    this->masterInnerLayout->addLayout(this->contentHolder);
    this->contentHolder->addStretch(); // Content shall be included in the child classes.

    this->masterInnerLayout->addLayout(this->buttonHolder);
    this->buttonHolder->addStretch();
    this->buttonHolder->addWidget(this->saveButton, Qt::AlignmentFlag::AlignLeading);
    this->buttonHolder->setSpacing(20);
    this->buttonHolder->addWidget(this->deleteButton, Qt::AlignmentFlag::AlignLeading);
    this->buttonHolder->setSpacing(20);
    this->buttonHolder->addWidget(this->editButton, Qt::AlignmentFlag::AlignLeading);
    this->buttonHolder->setSpacing(20);
}

void ItemWidget::establishConnections() {
    connect(
        this->deleteButton, &QPushButton::clicked,
        this, &ItemWidget::deleteButtonClicked
    );
    connect(
        this->saveButton, &QPushButton::clicked,
        this, &ItemWidget::saveButtonClicked
    );
    connect(
        this->editButton, &QPushButton::clicked,
        this, &ItemWidget::editButtonClicked
    );
}

void ItemWidget::createStyle() {
    this->setStyleSheet(
        R"(
            QWidget{
                border: 1px solid white;
                border-radius: 5px;
                background-color: #033a82
            }

            QPushButton{
                border : 0px;
            }

            QPushButton:hover{
                border : 2px solid #ffffff;
            }
        )"
    );
}

void ItemWidget::popUpAnimation(const int fWidth, const int fHeight) {
    this->expandContractAnimation->setStartValue(QSize(0, 0));
    this->expandContractAnimation->setEndValue(
        QSize(fWidth, fHeight)
    );

    this->expandContractAnimation->start();
}
