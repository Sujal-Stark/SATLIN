//
// Created by sujal-stark on 2/25/26.
//

#pragma once

#include <qscopedpointer.h>
#include <QString>
#include <QSet>

using namespace std;

class ItemRepository {
    QScopedPointer<QSet<QString>> textHashCollector;

public:
    ItemRepository();

    /**
     * Adds the Hash values of text item into the CollectorSet only if
     * the Hash Value is valid and not empty. Other-wise it returns False
     * as Failed in adding.
     */
    [[nodiscard]] bool addNewTextItemHash(const QString& textHash) const;

    /**
     * Given a textHash (const QString&) this method checks if repository
     * already contains this hash value or not.
     */
    [[nodiscard]] bool containsTextHash(const QString& textHash) const;

    /**
     * Given a textHash(const QString&) this method removes the text hash
     * value from the repository if it is found.
     */
    [[nodiscard]] bool removeTextItemHash(const QString& textHash) const;
};
