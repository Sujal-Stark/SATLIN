//
// Created by sujal-stark on 4/25/26.
//

#pragma once
#include <QObject>
#include <QLabel>

#include "../Ui/TextEditor.h"
#include "../Util/ItemRepository.h"
#include "../CustomWidgets/RegularButton.h"

class ItemManagerInterface : public QWidget{
    Q_OBJECT
    /**
     * This Class stores all the hash values for text Item.
     * Performs CRUD like operations on stored hash values.
     * Hash Data type : QString.
     */
protected:
    shared_ptr<ItemRepository> itemRepository = nullptr;

    /**
     * Creates Connections with MemberClass's signal to for handling
     * their output.
     */
    virtual void establishConnections() = 0;

public:
    explicit ItemManagerInterface();

    /**
     * To work properly on text item, it's hash value this method
     * accepts necessary drivers from the TextItemWidget.
     * Drivers:
     * ItemRepository :- Class that stores all text related hash values.
     */
    virtual void assignDrivers(const shared_ptr<ItemRepository>& repo);

    /**
     * @brief Given a TextHash(const QString&) this method removes the textHash from
     * Item Repository.
     */
    [[nodiscard]] virtual bool removeItem(const QString& hash) const = 0;

    /**
     * @param hash hexadecimal hash value assigned to each item.
     * @param extCard QLabel used to store extension value of an item.
     * @param fileSizeCard QLabel used to store the file size of an item.
     * @param timeStampCard QLabel used to store the time at which item is stored.
     * @param saveButton RegularButton that is used to save the item permanently.
     *
     * @brief Use this abstract method to update information of an item into the
     * related widgets.
     */
    virtual void populateInfoLabels(
        const QString &hash, QLabel* extCard, QLabel* fileSizeCard,
        QLabel* timeStampCard, RegularButton* saveButton
    )const = 0;
};

