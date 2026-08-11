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

TextWidget::TextWidget() {
    TextWidget::stylizeButtons();
    TextWidget::construct();
    TextWidget::establishConnections();
    TextWidget::customizeAnimationBehaviors();
}

void TextWidget::construct() {
    ItemWidget::construct();

    buttonHolder->addWidget(
        this->expandContractToggleButton,Qt::AlignmentFlag::AlignRight
    );
}

void TextWidget::stylizeButtons() {
    ItemWidget::stylizeButtons();

    this->expandContractToggleButton->setObjectName("expandToggle");
    this->expandContractToggleButton->setFixedSize(
        Constants::ITEM_WIDGET_EDIT_BUTTON_WIDTH, Constants::ITEM_WIDGET_EDIT_BUTTON_HEIGHT
    );
    this->expandContractToggleButton->setIcon(
        IconManager::expandIcon()
    );
}

void TextWidget::customizeAnimationBehaviors() {
    ItemWidget::customizeAnimationBehaviors();

    this->textLabelExpansionAnimation->setDuration(500);
}

void TextWidget::establishConnections() {
    ItemWidget::establishConnections();

    connect(
        this->expandContractToggleButton, &QPushButton::clicked,
        this, &TextWidget::expendCollapseAction
    );
}

void TextWidget::setTextManagerInterfaceInputs(
    const shared_ptr<TextManagerInterface>& interface,
    const shared_ptr<ItemRepository>& repo
    ) {
    this->textManagerInterface = interface;
    this->textManagerInterface->assignDrivers(repo);
}

void TextWidget::assignText(const QString &text, const QString& textHash) {
    this->textLabel = TextManagerInterface::generateNewTextLabel(text, textHash);

    if (!this->textLabel.isNull()) {
        this->textLabel->show();
        this->contentHolder->addWidget(this->textLabel, Qt::AlignmentFlag::AlignCenter);
    }
}

void TextWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::MouseButton::LeftButton) {
        emit this->textItemClickedSignal(this->textLabel->text());
    }

    /*this->setStyleSheet(
        "border: 1px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(54, 54, 54, 150);"
    );*/
}

void TextWidget::mouseReleaseEvent(QMouseEvent *event) {
    /*this->setStyleSheet(
        "border: 0px solid white;"
        "border-radius: 5px;"
        "background-color: rgba(15, 14, 14, 150);"
    );*/
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

void TextWidget::expendCollapseAction() {
    if (this->textLabel.isNull()) {
        throw std::runtime_error("Can't animate if text field is empty");
    }

    if (this->sizeHint().height() <= Constants::ITEM_WIDGET_HEIGHT)return;

    constexpr QSize collapsedTextCardParameters = QSize(
        Constants::TEXT_CARD_WIDTH, Constants::TEXT_CARD_HEIGHT
    );
    constexpr QSize collapsedTextWidgetParameters = QSize(
        Constants::ITEM_WIDGET_WIDTH, Constants::ITEM_WIDGET_HEIGHT
    );

    const QSize expandedTextCardParameters = QSize(
        Constants::TEXT_CARD_WIDTH,
        this->textLabel->sizeHint().height()
    );

    const QSize expandedTextWidgetParameters = QSize(
        Constants::ITEM_WIDGET_WIDTH, (
            this->textLabel->sizeHint().height() +
            Constants::ITEM_WIDGET_HEIGHT -
            Constants::TEXT_CARD_HEIGHT
        )
    );

    if (this->isExpanded) {
        this->textLabelExpansionAnimation->setStartValue(
            expandedTextCardParameters
        );

        this->expandContractAnimation->setStartValue(
            expandedTextWidgetParameters
        );

        this->textLabelExpansionAnimation->setEndValue(
            collapsedTextCardParameters
        );
        this->expandContractAnimation->setEndValue(
            collapsedTextWidgetParameters
        );

        this->textLabelExpansionAnimation->start();
        this->expandContractAnimation->start();

        this->isExpanded = false;
        this->expandContractToggleButton->setIcon(IconManager::expandIcon());
    }else {

        this->textLabelExpansionAnimation->setStartValue(
            collapsedTextCardParameters
        );

        this->expandContractAnimation->setStartValue(
            collapsedTextWidgetParameters
        );

        this->textLabelExpansionAnimation->setEndValue(
            expandedTextCardParameters
        );
        this->expandContractAnimation->setEndValue(
            expandedTextWidgetParameters
        );

        this->textLabelExpansionAnimation->start();
        this->expandContractAnimation->start();

        this->isExpanded = true;
        this->expandContractToggleButton->setIcon(IconManager::collapseButton());
    }
}

void TextWidget::popUpAnimation(const int fWidth, const int fHeight) {
    if (this->textLabel.isNull()) {
        throw std::runtime_error("Can't animate as fext field is empty");
    }

    this->expandContractAnimation->setStartValue(QSize(0, 0));
    this->textLabelExpansionAnimation->setStartValue(
        QSize(0, 0)
    );

    this->expandContractAnimation->setEndValue(
        QSize(
            fWidth, min(
                fHeight, this->sizeHint().height()
            )
        )
    );
    this->textLabelExpansionAnimation->setEndValue(
        QSize(
            Constants::TEXT_CARD_WIDTH, min(
                Constants::TEXT_CARD_HEIGHT, this->textLabel->sizeHint().height()
            )
        )
    );

    this->expandContractAnimation->start();
    this->textLabelExpansionAnimation->start();
}
