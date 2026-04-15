//
// Created by sujal-stark on 9/22/25.
//

#include "ItemWidget.h"
#include<Qt>
#include<iostream>
#include <QFileDialog>

#include "../Ui/ClipBoardInterface.h"
#include "../Util/Constants.h"

ItemWidget::ItemWidget() {
    this->setLayout(this->masterLayout);
    this->setFixedWidth(Constants::ITEM_WIDGET_WIDTH); // for constant width
    this->stylizeButtons();
    this->stylizeFrames();
    this->construct();
    this->establishConnections();
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
};

void ItemWidget::stylizeButtons() const {
    this->editButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->editButton->setIcon(IconManager::editIcon());

    this->deleteButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->deleteButton->setIcon(IconManager::cancelIcon());

    this->saveButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->saveButton->setIcon(IconManager::saveIcon());
}

void ItemWidget::stylizeFrames() const {
    this->mainFrame->setFixedWidth(
        Constants::ITEM_MAIN_FRAME_WIDTH
    );
}

void ItemWidget::construct() const {
    this->masterLayout->addWidget(this->mainFrame, Qt::AlignmentFlag::AlignCenter);
    this->mainFrame->setLayout(this->masterInnerLayout);

    this->masterInnerLayout->addLayout(this->contentHolder);
    this->contentHolder->addStretch();

    this->masterInnerLayout->addLayout(this->buttonHolder);
    this->buttonHolder->setSpacing(10);
    this->buttonHolder->addStretch();
    this->buttonHolder->addWidget(this->saveButton, Qt::AlignmentFlag::AlignRight);
    this->buttonHolder->addWidget(this->deleteButton, Qt::AlignmentFlag::AlignRight);
    this->buttonHolder->addWidget(this->editButton, Qt::AlignmentFlag::AlignRight);
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