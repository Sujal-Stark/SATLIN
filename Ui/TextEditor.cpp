//
// Created by sujal-stark on 1/28/26.

#include <QFileDialog>
#include "TextEditor.h"
#include "../Util/Constants.h"

TextEditor::TextEditor() {
    this->setWindowModality(Qt::ApplicationModal);
    this->setWindowTitle(Constants::TEXT_EDITOR_WINDOW_TITLE);
    this->setMinimumSize(
        Constants::TEXT_EDITOR_WIDTH, Constants::TEXT_EDITOR_HEIGHT
    );
    this->setLayout(this->masterOuterLayout);
    assignProperties();
    construct();
    establishConnections();
    setCustomStyle();
}

void TextEditor::assignProperties() const {
    // Frames
    this->mainFrame->setMinimumSize(
        Constants::TEXT_EDITOR_WIDTH - 20, Constants::TEXT_EDITOR_HEIGHT - 20
    );
    this->mainFrame->setFrameShape(QFrame::StyledPanel);

    // Buttons
    this->confirmButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->confirmButton->setIcon(IconManager::confirmIcon());

    this->cancelButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->cancelButton->setIcon(IconManager::cancelIcon());

    // Text Edit
    this->inputArea->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
}

void TextEditor::construct() const {
    this->masterOuterLayout->addWidget(this->mainFrame);
    this->mainFrame->setLayout(this->masterLayout);

    // Writing Zone
    this->masterLayout->addLayout(this->textHolderLayout, 4);
    this->textHolderLayout->addWidget(this->inputArea);

    // Control Zone
    this->masterLayout->addLayout(this->controlLayout, 1);
    this->controlLayout->addStretch();
    this->controlLayout->addWidget(this->confirmButton, Qt::AlignmentFlag::AlignRight);
    this->controlLayout->addWidget(this->cancelButton, Qt::AlignmentFlag::AlignRight);
}

void TextEditor::establishConnections() {
    connect(
        this->cancelButton, &QPushButton::clicked,
        this, &TextEditor::cancelButtonAction
    );

    connect(
        this->confirmButton, &QPushButton::clicked,
        this, &TextEditor::confirmButtonAction
    );
}

void TextEditor::setCustomStyle() {

}

void TextEditor::receiveText(const QString &text) const {
    this->inputArea->setText(text);
}

void TextEditor::cancelButtonAction() {
    emit this->textEditedSignal(nullptr);
    this->closingAction();
}

void TextEditor::confirmButtonAction() {
    emit this->textEditedSignal(this->inputArea->toPlainText());
    this->closingAction();
}

void TextEditor::closingAction() {
    this->inputArea->clear();
    this->close();
}
