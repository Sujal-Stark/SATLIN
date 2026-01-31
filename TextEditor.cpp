//
// Created by sujal-stark on 1/28/26.

#include <QFileDialog>

#include "TextEditor.h"
#include "Constants.h"

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
    this->saveButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->cancelButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );

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
    this->controlLayout->addWidget(this->saveButton, Qt::AlignmentFlag::AlignRight);
    this->controlLayout->addWidget(this->cancelButton, Qt::AlignmentFlag::AlignRight);
}

void TextEditor::establishConnections() {
    connect(
        this->cancelButton, &QPushButton::clicked,
        this, &TextEditor::cancelButtonAction
    );

    connect(
        this->saveButton, &QPushButton::clicked,
        this, &TextEditor::saveButtonAction
    );
}

void TextEditor::setCustomStyle() {

}

void TextEditor::receiveText(QString *text) {
    this->incomingText = text;
    this->inputArea->setText(QString::fromStdString(text->toStdString()));
}

void TextEditor::cancelButtonAction() {
    this->inputArea->clear();
    this->close();
}

void TextEditor::saveButtonAction() {
    QString fileName = QFileDialog::getSaveFileName(
        this,"Save File", QDir::homePath(),
    "Text Files (*.txt);;All Files (*)"
    );

    writeTextFile(fileName, this->inputArea->toPlainText());
    this->close();
}

void TextEditor::writeTextFile(const QString &fileName, const QString &content) {
    QFile file = QFile(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream = QTextStream(&file);
        stream<<content;
        file.close();
    }
}
