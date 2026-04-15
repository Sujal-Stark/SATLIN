//
// Created by sujal-stark on 4/14/26.
//

#include "TextWidget.h"

#include<Qt>
#include<iostream>
#include <QFileDialog>

#include "../Ui/ClipBoardInterface.h"
#include "../Util/Constants.h"

using namespace std;

TextWidget::TextWidget() = default;

void TextWidget::setTextManagerInterfaceInputs(
    const shared_ptr<TextManagerInterface>& interface,
    const shared_ptr<ItemRepository>& repo
    ) {
    this->textManagerInterface = interface;
    this->textManagerInterface->assignDrivers(repo);
}

void TextWidget::assignText(const QString &text, const QString& textHash) {
    this->textLabel = TextManagerInterface::generateNewTextLabel(text, textHash);

    if (this->textLabel != nullptr) {
        this->textLabel->show();
        this->contentHolder->addWidget(this->textLabel, Qt::AlignmentFlag::AlignCenter);
    }
}

void TextWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::MouseButton::LeftButton) {
        emit this->textItemClickedSignal(this->textLabel->text());
    }

    this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(54, 54, 54, 150);"
    );
}

void TextWidget::mouseReleaseEvent(QMouseEvent *event) {
    this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );
}

void TextWidget::deleteButtonClicked() {
    if (
        this->textManagerInterface->removeItem(
            this->textLabel->property(Constants::SHA_STRING_KEY).toString()
        )
    ) {
        emit this->clipboardCleanSignal();
        this->deleteLater();
    }else qWarning()<<"Unable to delete this textItem";
}

void TextWidget::saveButtonClicked() {
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

void TextWidget::editButtonClicked() {
    connect(
        &*this->textManagerInterface, &TextManagerInterface::textEditedSignal,
        this, &TextWidget::editedTextReceivedAction
    );

    this->textManagerInterface->editOnText(this->textLabel->text());
}

void TextWidget::editedTextReceivedAction(const QString& editedText) {
    if (!editedText.isNull()) {
        const QString oldHash = this->textLabel->property(Constants::SHA_STRING_KEY).toString();
        const QString newHash = HashGenerator::generateTextHash(editedText);
        if (this->textManagerInterface->replaceHash(oldHash, newHash)) {
            this->textLabel->setText(editedText);
            this->textLabel->setProperty(Constants::SHA_STRING_KEY, newHash);
            emit textItemClickedSignal(this->textLabel->text());
            this->update();
        }
    }

    disconnect(
        &*this->textManagerInterface, &TextManagerInterface::textEditedSignal,
        this, &TextWidget::editedTextReceivedAction
    );
}
