//
// Created by sujal-stark on 2/25/26.
//

#include "ItemRepository.h"
#include <QDebug>

ItemRepository::ItemRepository() : textHashCollector(new QSet<QString>()) {

}

bool ItemRepository::addNewTextItemHash(const QString &textHash) const {
    if (textHash.isNull())return  false;
    if (this->textHashCollector->contains(textHash)) return false;
    this->textHashCollector->insert(textHash);
    return true;
}

bool ItemRepository::containsTextHash(const QString &textHash) const {
    return this->textHashCollector->contains(textHash);
}

bool ItemRepository::removeTextItemHash(const QString &textHash) const {
    return this->textHashCollector->remove(textHash);
}
