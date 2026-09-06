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

bool TextManagerInterface::replaceHash(
    const QString& oldHash, const QString& newHash, const QString& editedText
)const {
    return this->itemRepository->replaceTextHash(newHash, oldHash, editedText);
}

void TextManagerInterface::editOnText(const QString& currentText) const {
    textEditor->receiveText(currentText);
    textEditor->show();
}

void TextManagerInterface::populateInfoLabels(
    const QString &textHash, QLabel *extCard, QLabel *fileSizeCard,
    QLabel *timeStampCard, RegularButton *saveButton
) const {
    const std::optional<TextContainer*> obj = this->itemRepository->getTextContainer(textHash);

    if (!obj.has_value())throw std::runtime_error(
        "Unable to retrieve data from repository"
    );

    const TextContainer* const container = obj.value();

    extCard->setText(container->extension);
    fileSizeCard->setText(QString::fromStdString(std::to_string(container->textSize) + " kb"));
    timeStampCard->setText(container->timeStamp);

    if (container->saveStatus == 0) {
        saveButton->setIcon(IconManager::confirmIcon());
    }
}

bool TextManagerInterface::updateSaveStatus(
    const QString &textHash, const int saveStatus, RegularButton *saveButton
) const {
    const std::optional<TextContainer*> container = this->itemRepository->getTextContainer(textHash);

    if (!container.has_value())return false;

    container.value()->saveStatus = saveStatus;
    if (saveStatus == 0)saveButton->setIcon(IconManager::confirmIcon());

    return true;
}

void TextManagerInterface::transferEditedText(const QString &text) {
    this->textEditedSignal(text);
}
