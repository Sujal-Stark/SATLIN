//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <QLabel>

#include "../Ui/TextEditor.h"
#include "../Util/ItemRepository.h"

using namespace std;

class TextManagerInterface : public QObject {
    Q_OBJECT
    /**
     * This Class stores all the hash values for text Item.
     * Performs CRUD like operations on stored hash values.
     * Hash Data type : QString.
     */
    shared_ptr<ItemRepository> itemRepository = nullptr;

    /**
     * TextEditor Interface is used to make changes in texts.
     */
    unique_ptr<TextEditor> textEditor = make_unique<TextEditor>();

    /**
     * Creates Connections with MemberClass's signal to for handling
     * their output.
     */
    void establishConnections();

    /**
     * Sends a signal to itemWidget to Transfer the edited text.
     */
    void transferEditedText(const QString &text);

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
    void assignDrivers(const shared_ptr<ItemRepository>& repo);

    /**
     * Given a TextHash(const QString&) this method removes the textHash from
     * Item Repository.
     */
    [[nodiscard]] bool removeItem(const QString& textHash) const;

    /**
     * It checks if the old hash is present and the new hash is absent in
     * ItemRepository. If Both conditions are met then it erase old hash and
     * add new Hash to the Repository.
     */
    [[nodiscard]] bool replaceHash(const QString& oldHash, const QString& newHash) const;

    /**
     * Receives a valid QString from ItemWidget, sends it to TextEditor and
     * Open the TextEditor Window.
     */
    void editOnText(const QString& currentText) const;

    signals:
    /**
     * Sends the edited Text to the Caller ItemWidget.
     */
    void textEditedSignal(QString editedText);
};
