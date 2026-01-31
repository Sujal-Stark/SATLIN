//
// Created by sujal-stark on 11/5/25.
//

#include "TextManagerInterface.h"
#include "Constants.h"

TextManagerInterface::TextManagerInterface() {
    this->currentTextHash = -1;
};

void TextManagerInterface::setInputText(const QString &text, const size_t textHashValue){
    /*
     * Takes Input text int QString format (Not Null) from ItemWidget
     */
    this->copiedText = text;
    this->currentTextHash = textHashValue;
    this->addNewTextToTextMap();
}

QLabel *TextManagerInterface::getCurrentCopiedText() {
    /*
     * Returns the QLabel holding currently copied text from ClipBoard
     */
    const size_t currentHash = this->currentTextHash;
    this->currentTextHash = 0;
    return !this->textMap.empty()? this->textMap[currentHash] : nullptr;
}

QLabel *TextManagerInterface::createTextLabel() const {
    /*
     * Creates The Label and stylize it and return the QLabel
     */
    auto *label = new QLabel(this->copiedText); // CAN LEAK. FIX LATER
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

void TextManagerInterface::addNewTextToTextMap() {
    /*
     * If New Text Label Arrives, It takes it into Map
     */
    const auto textLabel = this->createTextLabel();
    this->textMap[this->currentTextHash] = textLabel;
}

bool TextManagerInterface::removeItem(const size_t textHash) {
    /*
     * Check's if a hash value already exists or not. If exists then
     * we remove the hash and the label from the map and schedule it
     * for deletion.
     */
    if (this->textMap.contains(textHash)) {
        QLabel *currLabel = this->textMap[textHash];
        this->textMap.erase(textHash);
        currLabel->clear(); // clear's the content as well
        currLabel->deleteLater();
        return  true;
    }
    return  false;

}

