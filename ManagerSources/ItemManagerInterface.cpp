//
// Created by sujal-stark on 4/25/26.
//

#include "ItemManagerInterface.h"

ItemManagerInterface::ItemManagerInterface() = default;

void ItemManagerInterface::assignDrivers(const shared_ptr<ItemRepository>& repo) {
    this->itemRepository = repo;
}
