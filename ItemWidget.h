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

signals:
    void textItemClickedSignal(string text);
    void imageItemClickedSignal(QPixmap image);

protected:
    void mousePressEvent(QMouseEvent *event) override;

public:
    explicit ItemWidget(const QString &text, QWidget *parent = nullptr): QLabel(text, parent){};
};