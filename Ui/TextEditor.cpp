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

void TextEditor::dynamicWidgetIntegration() {
    /*
     * According to the modes received this method is responsible
     * for adding or removing subtle widgets from the GUI.
     */

    // Save Action
    if (this->operationModeSignal == 0) {
        // removal of ConfirmButton
        this->controlLayout->removeWidget(this->confirmButton);
        this->confirmButton->hide();

        // addition of Save button
        this->controlLayout->addWidget(
            this->saveButton, Qt::AlignmentFlag::AlignRight
        );
        this->saveButton->show();
    }

    // Edit Action
    else if (this->operationModeSignal == 1) {
        // removal of Save button
        this->controlLayout->removeWidget(this->saveButton);
        this->saveButton->hide();

        // addition of confirm button
        this->controlLayout->addWidget(
            this->confirmButton, Qt::AlignmentFlag::AlignRight
        );
        this->confirmButton->show();
    }

    this->update(); // enforce Window to reflect changes.
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
    this->saveButton->setIcon(IconManager::saveIcon());

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

    connect(
        this->saveButton, &QPushButton::clicked,
        this, &TextEditor::saveButtonAction
    );
}

void TextEditor::setCustomStyle() {

}

void TextEditor::receiveText(const QString &text, const int operationMode) {
    /*
     * Expects a non-empty text for further operation. Performs expected widget changes
     * in the GUI to reflect requested actions.
     */
    this->incomingText = text;
    this->operationModeSignal = operationMode;
    dynamicWidgetIntegration();
    this->inputArea->setText(text);
}

void TextEditor::cancelButtonAction() {
    /*
     * Clear's the TextEditor for further use and close it to stay in the background.
     */
    this->closingAction();
}

void TextEditor::saveButtonAction() {
    /*
     * Creates a file name along with its absolute path. And send it
     * to the writeTextFile method to create the file and dump information.
     */

    const QString fileName = QFileDialog::getSaveFileName(
        this,Constants::SAVE_FILE_LABEL, QDir::homePath(),
    "Text Files (*);;All Files (*)"
    );

    if (!fileName.isEmpty()) {
        writeTextFile(fileName, this->inputArea->toPlainText());
    } // Ensures valid path is sent

    this->closingAction(); // reset's the editor
}

void TextEditor::writeTextFile(const QString &fileName, const QString &content) {
    /*
     * Expects a valid filePath and text content. This method dump the content as Text
     * into the file. and Saves it.
     */

    QFile file = QFile(fileName);

    // WriteOnly ensures file is already empty.
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream = QTextStream(&file);
        stream<<content;//The content is dumped.
        file.close();
    }
}

void TextEditor::confirmButtonAction() {
    this->closingAction();
}

void TextEditor::closingAction() {
    /*
     * After completion of Text editor interface, The State variables are
     * set to default set for future use
     */
    this->inputArea->clear();
    this->incomingText = nullptr;
    this->operationModeSignal = -1;
    this->close();
}
