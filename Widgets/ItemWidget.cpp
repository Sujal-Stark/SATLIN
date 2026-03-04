//
// Created by sujal-stark on 9/22/25.
//

#include "ItemWidget.h"
#include<Qt>
#include<iostream>
#include <QFileDialog>

#include "../Ui/ClipBoardInterface.h"
#include "../Util/Constants.h"

using namespace std;

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

void ItemWidget::setTextManagerInterfaceInputs(
    const shared_ptr<TextManagerInterface>& interface,
    const shared_ptr<ItemRepository>& repo
    ) {
    this->textManagerInterface = interface;
    this->textManagerInterface->assignDrivers(repo);
}

void ItemWidget::assignText(const QString &text, const QString& textHash) {
    this->textLabel = TextManagerInterface::generateNewTextLabel(text, textHash);

    if (this->textLabel != nullptr) {
        this->textLabel->show();
        this->contentHolder->addWidget(this->textLabel, Qt::AlignmentFlag::AlignCenter);
    }
}

void ItemWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::MouseButton::LeftButton) {
        emit this->textItemClickedSignal(this->textLabel->text());
    }

    this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(54, 54, 54, 150);"
    );
}

void ItemWidget::mouseReleaseEvent(QMouseEvent *event) {
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
}

void ItemWidget::deleteButtonClicked() {
    if (
        this->textManagerInterface->removeItem(
            this->textLabel->property(Constants::TEXT_HASH_KEY).toString()
        )
    ) {
        emit this->clipboardCleanSignal();
        this->deleteLater();
    }else qWarning()<<"Unable to delete this textItem";
}

void ItemWidget::saveButtonClicked() {
    const QString fileName = QFileDialog::getSaveFileName(
        this,Constants::SAVE_FILE_LABEL, QDir::homePath(),
    "Text Files (*);;All Files (*)"
    );

    if (fileName.isEmpty())return;

    QFile file = QFile(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream = QTextStream(&file);
        stream<<this->textLabel->text();//The content is dumped.
        file.close();
    }
}

void ItemWidget::editButtonClicked() {
    connect(
        &*this->textManagerInterface, &TextManagerInterface::textEditedSignal,
        this, &ItemWidget::editedTextReceivedAction
    );

    this->textManagerInterface->editOnText(this->textLabel->text());
}

void ItemWidget::editedTextReceivedAction(const QString& editedText) {
    if (!editedText.isNull()) {
        const QString oldHash = this->textLabel->property(Constants::TEXT_HASH_KEY).toString();
        const QString newHash = HashGenerator::generateTextHash(editedText);
        if (this->textManagerInterface->replaceHash(oldHash, newHash)) {
            this->textLabel->setText(editedText);
            this->textLabel->setProperty(Constants::TEXT_HASH_KEY, newHash);
            emit textItemClickedSignal(this->textLabel->text());
            this->update();
        }
    }

    disconnect(
        &*this->textManagerInterface, &TextManagerInterface::textEditedSignal,
        this, &ItemWidget::editedTextReceivedAction
    );
}