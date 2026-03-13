//
// Created by sujal-stark on 11/5/25.
//

#include "TextManagerInterface.h"

#include <qpointer.h>

#include "../Util/Constants.h"

TextManagerInterface::TextManagerInterface() {
    this->establishConnections();
}

QPointer<QLabel> TextManagerInterface::generateNewTextLabel(
    const QString &text, const QString& textHashValue
){
    QPointer ptr = QPointer(new QLabel(text));
    ptr->setProperty(Constants::SHA_STRING_KEY, textHashValue);
    ptr->setWordWrap(true);
    ptr->setAlignment(Qt::AlignmentFlag::AlignLeft);
    ptr->setFixedWidth(Constants::TEXT_CARD_WIDTH);
    ptr->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(145, 191, 250, 0);"
    );

    return ptr;
}

void TextManagerInterface::establishConnections() {
    connect(
        &*this->textEditor, &TextEditor::textEditedSignal,
        this, &TextManagerInterface::transferEditedText
    );
}

void TextManagerInterface::assignDrivers(const shared_ptr<ItemRepository>& repo) {
    this->itemRepository = repo;
}

bool TextManagerInterface::removeItem(const QString& textHash) const {
    return this->itemRepository->removeTextItemHash(textHash);
}

bool TextManagerInterface::replaceHash(const QString& oldHash, const QString& newHash) const {
    if (itemRepository->containsTextHash(oldHash)&& !itemRepository->containsTextHash(newHash)) {
        return itemRepository->removeTextItemHash(oldHash) && itemRepository->addNewTextItemHash(newHash);
    }
    return false;
}

void TextManagerInterface::editOnText(const QString& currentText) const {
    textEditor->receiveText(currentText);
    textEditor->show();
}

void TextManagerInterface::transferEditedText(const QString &text) {
    this->textEditedSignal(text);
}
