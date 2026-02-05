//
// Created by sujal-stark on 2/4/26.
//

#pragma once

#include <QStyle>
#include <QIcon>
#include <QWidget>

class IconManager : public  QWidget{
public:
    [[nodiscard]] static QIcon saveIcon() ;
    [[nodiscard]] static QIcon confirmIcon();
    [[nodiscard]] static QIcon cancelIcon();
    [[nodiscard]] static QIcon editIcon() ;

    [[nodiscard]] static QIcon textIcon() ;
    [[nodiscard]] static QIcon photoIcon();
    [[nodiscard]] static QIcon videoIcon();
    [[nodiscard]] static QIcon audioIcon();
    [[nodiscard]] static QIcon clipboardIcon();
    [[nodiscard]] static QIcon emojiPanelIcon();
};