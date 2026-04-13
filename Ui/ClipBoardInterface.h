//
// Created by sujal-stark on 8/12/25.
//

#pragma once

#include <QTabWidget>
#include <QScrollArea>
#include <QFrame>
#include <queue>

// Custom Import
#include "../ManagerSources/AudioManagerInterface.h"
#include "../ManagerSources/ImageManagerInterface.h"
#include "../Widgets/ItemWidget.h"
#include "../Widgets/ImageWidget.h"
#include "../ManagerSources/TextManagerInterface.h"
#include "../Util/ItemRepository.h"
#include "../Util/MimeDataAnalyzer.h"
#include "../Widgets/AudioWidget.h"


using namespace std;

class ClipBoardInterface final : public QWidget{
    // General
    shared_ptr<ItemRepository> itemRepository = make_shared<ItemRepository>();
    MimeDataAnalyzer *mimeDataAnalyzer = new MimeDataAnalyzer();
    void constructUI() const;
    void widgetBehaviourSelection() const;
    void setCustomStyle();

    /**
     * @brief build Connections with UI components and Member Classes
     * with actionable methods.
     */
    void setActions() const;

    /**
     * @brief Clears the Clipboard Content when it is called.
     */
    void cleanClipBoard() const;

    // TEXT
    shared_ptr<TextManagerInterface> text_manager_interface = make_shared<TextManagerInterface>();

    /**
     * @brief Receives and ItemWidget Pointer and set's the Object
     * to UI. Latest at top manner is used.
     */
    void showTextItemOnScreen(ItemWidget *item) const;

    /**
     * Receives a text item and sets it as current ClipBoard Item.
     */
    void textItemClickedAction(const QString &content) const;

    void handleTextItem(const QString& text, const QString& hash);

    // IMAGE
    shared_ptr<ImageManagerInterface> imageManagerInterface = make_shared<ImageManagerInterface>();
    void showImageOnScreen(ImageWidget *image) const;

    /**
     * Receives Signal as Const QImage& and int for mode of copy.
     * For different copy mode it can perform different specific
     * operations and finally loads QImage to the Clipboard.
     */
    void imageItemClickedAction(const QImage &image) const;

    void handleImageItem(const QString& text, const QString& imageHash, int mode);
    void imageRemovedConfirmationAction(
        const QString &imageHash, const QString& filePath, int mode
    ) const;

    // AUDIO
    shared_ptr<AudioManagerInterface>audioManagerInterface = make_shared<AudioManagerInterface>();
    void handleAudioItem(
        int saveStatus, qint32 fileSize, const QString &filePath,
        const QString &ext, const QString &timeStamp, const QString &hash
    ) const;
    void showAudioItemOnScreen(AudioWidget* audio) const;
    void audioItemClickedAction(const QString &filePath) const;
    void audioRemovedConfirmationAction(
        const QString& hashValue, const QString& filePath, int mode
    ) const;
    // Signal Reception
    /**
     * Signal Receptor from System's clipboard. It generates current QMimeData
     * Object and runs MimeDataAnalyzer to understand type of object copied.
     */
    void handleIncomingItems() const; // get copied item from clip board


    public:
    explicit ClipBoardInterface();
    // ~ClipBoardInterface();
    QClipboard *clipBoard;
    queue<ItemWidget *> textQueue;

                                // Method declaration


                                // Attribute Declaration
    // Frames
    QFrame *textHolderFrame = new QFrame();
    QFrame *imageHolderFrame = new QFrame();
    QFrame *audioHolderFrame = new QFrame();
    QFrame *videoHolderFrame = new QFrame();

    // Layout
    QVBoxLayout *masterLayout = new QVBoxLayout();

    QVBoxLayout *textSectionLayout = new QVBoxLayout();
    QVBoxLayout *textScrollAreaInnerLayout = new QVBoxLayout();

    QVBoxLayout *imageSectionLayout = new QVBoxLayout();
    QVBoxLayout *imageScrollAreaInnerLayout = new QVBoxLayout();

    QVBoxLayout *videoSectionLayout = new QVBoxLayout();
    QVBoxLayout *videoScrollAreaInnerLayout = new QVBoxLayout();

    QVBoxLayout *audioSectionLayout = new QVBoxLayout();
    QVBoxLayout *audioScrollAreaInnerLayout = new QVBoxLayout();

    // ScrollArea
    QScrollArea *textSectionScrollArea = new QScrollArea();
    QScrollArea *imageSectionScrollArea = new QScrollArea();
    QScrollArea *videoSectionScrollArea = new QScrollArea();
    QScrollArea *audioSectionScrollArea = new QScrollArea();

    // Tab Widget
    QTabWidget *clipTabWidget = new QTabWidget();

    // QWidget
    QWidget *textSection = new QWidget();
    QWidget *imageSection = new QWidget();
    QWidget *videoSection = new QWidget();
    QWidget *audioSection = new QWidget();
};