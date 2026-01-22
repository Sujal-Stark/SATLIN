//
// Created by sujal-stark on 11/5/25.
//

#pragma once
#include <QLabel>

using namespace std;

class TextManagerInterface {
    map<size_t, QLabel *>textMap; // Holds The final output
    size_t currentTextHash;
    QString copiedText; // holds input
    [[nodiscard]] QLabel* createTextLabel() const; // creates the output

public:
    explicit TextManagerInterface();
    void setInputText(const QString& text, size_t textHashValue);

    void addNewTextToTextMap(); // fill textMap with new Item
    [[nodiscard]] QLabel * getCurrentCopiedText(); // sends output
};
