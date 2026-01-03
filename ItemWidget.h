//
// Created by sujal-stark on 9/22/25.
//

#pragma once

#include <qboxlayout.h>
#include<QLabel>
#include<QMouseEvent>
#include<string>

using namespace std;

class ItemWidget : public QWidget{
    Q_OBJECT
    vector<bool> OBJECT_RECOGNITION_FLAG_ARRAY = {false, false, false, false}; // stores Flag
    int OBJECT_RECOGNITION_FLAG_INDEX = -1; // stores Flag Index

    // holder object declaration
    QLabel* image_Text_HolderLabel = nullptr;

    // Layouts
    QHBoxLayout *masterLayout = new QHBoxLayout();

    // Methods
    void assignProperties();

signals:
    void textItemClickedSignal(std::string text); // returns Text item
    void imageItemClickedSignal(QPixmap image); // returns Image item


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    explicit ItemWidget(const QString &text, QWidget *parent = nullptr); // holds text
    explicit ItemWidget(const QPixmap &image, QWidget *parent = nullptr); // for image
    void setObjectType(int objectFlag); // accepts flag
    [[nodiscard]] QLabel* getImageHolder() const; // returns current image
    [[nodiscard]] QLabel* getTextHolder() const; // returns current text
};