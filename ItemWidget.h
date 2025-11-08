//
// Created by sujal-stark on 9/22/25.
//

#pragma once

#include<QLabel>
#include<QMouseEvent>
#include<string>

using namespace std;

class ItemWidget : public QLabel{
    Q_OBJECT
    vector<bool> OBJECT_RECOGNITION_FLAG_ARRAY = {false, false, false, false}; // stores Flag
    int OBJECT_RECOGNITION_FLAG_INDEX = -1; // stores Flag Index

signals:
    void textItemClickedSignal(string text); // returns Text item
    void imageItemClickedSignal(QPixmap image); // returns Image item

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    explicit ItemWidget(const QString &text, QWidget *parent = nullptr): QLabel(text, parent){};
    void setObjectType(int objectFlag); // accepts flag
};