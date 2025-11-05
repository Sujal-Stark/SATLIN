//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <queue>
#include <set>

#include "ItemWidget.h"

class TextManagerInterface {
    queue<ItemWidget *>textQueue; // Holds The final output
    set<size_t> currentTextHash; // Checks if the text exists or not
    string copiedText; // holds input
    [[nodiscard]] ItemWidget* createTextLabel(); // creates the output

public:
    explicit TextManagerInterface();
    void setCurrentCopiedText(const string &text); // receive input
    void addNewTextToQueue(); // fill textQueue with new Item
    [[nodiscard]] ItemWidget * getCurrentCopiedText() const; // sends output
};
