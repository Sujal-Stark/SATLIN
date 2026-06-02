//
// Created by sujal-stark on 4/25/26.
//

#pragma once
#include <QObject>
#include <QLabel>

#include "../Ui/TextEditor.h"
#include "../Util/ItemRepository.h"

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
     * Given a TextHash(const QString&) this method removes the textHash from
     * Item Repository.
     */
    [[nodiscard]] virtual bool removeItem(const QString& hash) const = 0;

    /**
     * It checks if the old hash is present and the new hash is absent in
     * ItemRepository. If Both conditions are met then it erase old hash and
     * add new Hash to the Repository.
     */
    [[nodiscard]] virtual bool replaceHash(const QString& oldHash, const QString& newHash) const = 0;
};

