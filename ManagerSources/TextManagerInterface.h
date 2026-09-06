//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <QLabel>

#include "ItemManagerInterface.h"
#include "../Ui/TextEditor.h"
#include "../Util/ItemRepository.h"
#include "../CustomWidgets/RegularButton.h"

using namespace std;

class TextManagerInterface : public ItemManagerInterface {
    Q_OBJECT
    /** TextEditor Interface is used to make changes in texts.*/
    unique_ptr<TextEditor> textEditor = make_unique<TextEditor>();

    /** Sends a signal to ItemWidget to Transfer the edited text.*/
    void transferEditedText(const QString &text);

protected:
    /**
     * Creates Connections with MemberClass's signal to for handling
     * their output.
     */
    void establishConnections() override;


public:
    explicit TextManagerInterface();

    /**
     * This method requires a textItem(const QString&) and hash(
     * const QString&). The hash is stored in repository and a
     * new QPointer<QLabel> is created and returned.
     */
    [[nodiscard]]static QPointer<QLabel> generateNewTextLabel(
        const QString& text, const QString& textHashValue
    );

    /**
     * To work properly on text item, it's hash value this method
     * accepts necessary drivers from the TextItemWidget.
     * Drivers:
     * ItemRepository :- Class that stores all text related hash values.
     */
    void assignDrivers(const shared_ptr<ItemRepository>& repo) override;

    /**
     * Given a TextHash(const QString&) this method removes the textHash from
     * Item Repository.
     */
    [[nodiscard]] bool removeItem(const QString& textHash) const override;

    /**
     * It checks if the old hash is present and the new hash is absent in
     * ItemRepository. If Both conditions are met then it erase old hash and
     * add new Hash to the Repository.
     */
    [[nodiscard]] bool replaceHash(
        const QString& oldHash, const QString& newHash, const QString& editedText
    ) const;

    /**
     * Receives a valid QString from ItemWidget, sends it to TextEditor and
     * Open the TextEditor Window.
     */
    void editOnText(const QString& currentText) const;

    void populateInfoLabels(
        const QString &textHash, QLabel* extCard, QLabel* fileSizeCard,
        QLabel* timeStampCard, RegularButton* saveButton
    )const override;

    /**
     *
     * @param textHash hexadecimal hash value for text items.
     * @param saveStatus flag to show saved or unsaved state of that item.
     * @param saveButton RegularButton instance of a text item.
     * @return a boolean result confirming success -> true or failure - false of that operation.
     * @brief This method updates the state of UI when a text is saved.
     */
    [[nodiscard]] bool updateSaveStatus(
        const QString& textHash, int saveStatus, RegularButton* saveButton
    ) const;

    signals:
    /** Sends the edited Text to the Caller ItemWidget.*/
    void textEditedSignal(QString editedText);
};
