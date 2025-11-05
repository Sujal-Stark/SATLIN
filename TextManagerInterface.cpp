//
// Created by sujal-stark on 11/5/25.
//

#include "TextManagerInterface.h"
#include "Constants.h"

TextManagerInterface::TextManagerInterface() = default;

void TextManagerInterface::setCurrentCopiedText(const string &text) {
    this->copiedText = text;
}

ItemWidget *TextManagerInterface::getCurrentCopiedText() const {
    if (!this->textQueue.empty()) {
        return  this->textQueue.back();
    }
    return nullptr;
}

ItemWidget *TextManagerInterface::createTextLabel() {
    if (!this->copiedText.empty() && !currentTextHash.contains(qHash(this->copiedText))) {
        currentTextHash.insert(qHash(this->copiedText)); // hashing

        auto *label = new ItemWidget(QString::fromStdString(this->copiedText)); // CAN LEAK
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignmentFlag::AlignLeft);
        label->setFixedWidth(Constants::TEXT_CARD_WIDTH);
        label->setStyleSheet(
            "border: 1px solid white;"
            "border-radius: 5px;"
            "background-color: rgba(145, 191, 250, 0);"
        );

        return label;
    }

    return nullptr;
}

void TextManagerInterface::addNewTextToQueue() {
    if (
    const auto textLabel = this->createTextLabel();
    textLabel != nullptr
    ) this->textQueue.push(textLabel);
}

