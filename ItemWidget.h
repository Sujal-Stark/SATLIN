//
// Created by sujal-stark on 9/22/25.
//

#pragma once

#include<QMouseEvent>
#include<QPushButton>
#include<QHBoxLayout>

#include "Constants.h"
#include "ImageManagerInterface.h"
#include "TextEditor.h"
#include "TextManagerInterface.h"

using namespace std;

class ItemWidget : public QWidget{
    Q_OBJECT

    // these two help deducing which media is in use
    vector<bool> OBJECT_RECOGNITION_FLAG_ARRAY = {false, false, false, false}; // stores Flag
    int OBJECT_RECOGNITION_FLAG_INDEX = -1; // stores Flag Index
    size_t text_item_hash = -1;

    // image
    QString image_item_Hash = nullptr;

    // Text
    TextEditor *text_editor = nullptr;

    // Media Manager Interfaces
    TextManagerInterface *text_manager_interface = nullptr;
    ImageManagerInterface *image_manager_interface = nullptr;

    // QButtons
    QPushButton *deleteButton = new QPushButton(Constants::DELETE_LABEL);
    QPushButton *editButton = new QPushButton(Constants::EDIT_LABEL);
    QPushButton *saveButton = new QPushButton(Constants::SAVE_LABEL);

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
    // General
    void stylizeButtons() const;
    void stylizeFrames() const;
    void establishConnections();
    void deleteButtonClicked();
    void saveButtonClicked() const;
    void editButtonClicked() const;

signals:
    void textItemClickedSignal(QString text); // returns Text item
    void imageItemClickedSignal(QPixmap image); // returns Image item
    // video signal
    // audio signal

    void text_Hash_Removal_Request_Signal(size_t text_Hash);
    void image_Hash_Removal_Request_Signal(QString &image_Hash);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public:
    explicit ItemWidget();
    void construct() const;
    void assignText(const QString &text, size_t textHash); // holds text
    void assignImage(const QImage &image, QString imageHash); // holds image

    void setTextManagerInterfaceInputs(
        TextManagerInterface *interface, TextEditor *textEditor
    );
    void setImageManagerInterfaceInput(ImageManagerInterface *interface);
};