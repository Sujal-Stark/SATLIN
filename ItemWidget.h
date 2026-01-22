//
// Created by sujal-stark on 9/22/25.
//

#pragma once

#include<QMouseEvent>
#include<QPushButton>
#include<QHBoxLayout>

#include "Constants.h"
#include "ImageManagerInterface.h"
#include "TextManagerInterface.h"

using namespace std;

class ItemWidget : public QWidget{
    Q_OBJECT

    // these two help deducing which media is in use
    vector<bool> OBJECT_RECOGNITION_FLAG_ARRAY = {false, false, false, false}; // stores Flag
    int OBJECT_RECOGNITION_FLAG_INDEX = -1; // stores Flag Index

    // Media Manager Interfaces
    TextManagerInterface *text_manager_interface = nullptr;
    ImageManagerInterface *image_manager_interface = nullptr;

    // QButtons
    QPushButton *deleteButton = new QPushButton(Constants::DELETE_LABEL);
    QPushButton *editButton = new QPushButton(Constants::EDIT_LABEL);

    // holder object declaration
    QLabel* image_Text_HolderLabel = nullptr;

    // Layouts
    QVBoxLayout *masterLayout = new QVBoxLayout();
    QVBoxLayout *masterInnerLayout = new QVBoxLayout();

    QHBoxLayout *contentHolder = new QHBoxLayout();
    QHBoxLayout *buttonHolder = new QHBoxLayout();

    // Frames
    QFrame *mainFrame = new QFrame();

    // Methods
    void stylizeButtons() const;
    void stylizeFrames() const;

signals:
    void textItemClickedSignal(QString text); // returns Text item
    void imageItemClickedSignal(QPixmap image); // returns Image item
    // video signal
    // audio signal

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    explicit ItemWidget();
    void construct() const;
    void assignText(const QString &text, size_t textHash); // holds text
    void assignImage(const QImage &image, QString imageHash); // holds image
    void setObjectType(int objectFlag); // accepts flag

    void setTextManagerInterfaceInput(TextManagerInterface *interface);
    void setImageManagerInterfaceInput(ImageManagerInterface *interface);
};