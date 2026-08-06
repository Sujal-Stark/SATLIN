//
// Created by sujal-stark on 7/26/26.
//

#pragma once

#include <QPushButton>
#include <QPropertyAnimation>

/***
 * @brief RegularButton is a class inherited prom QPushButton
 * which with holds its own type of properties explained below
 * 1. Hover animation: When Cursor comes inside the geometric region
 * of this button the button expands by given size and when the
 * cursor leaves the button's geometric region the button shrinks
 * to its original size.
 ***/
class RegularButton : public QPushButton{
    Q_OBJECT

    /***
     * @brief Stores value for size hint. This value can be
     * customized by the user with setSizeHint() method
     ****/
    QSize SIZE_HINT = QSize(0, 0);

    /***
     * @brief Stores value for maximum possible size a button can take
     * during animation. User can change this value using
     * setResizeHoverAnimationParameters(int, int, int, int)
     * method.
     ***/
    QSize MAX_SIZE = QSize(0, 0);

    /***
     * @brief Stores value for minimum possible size a button can take
     * during animation. User can change this value using
     * setResizeHoverAnimationParameters(int, int, int, int)
     * method
     ***/
    QSize MIN_SIZE = QSize(0, 0);

    /***
     * @brief Animates the size of this button object whenever cursor
     * enters or leaves this button's geometric region.
     ***/
    QPropertyAnimation* resizeOnHover = new QPropertyAnimation(this, "size");

    /***
     * @brief The Properties of animation instances used in this class
     * is set in this method.
     ***/
    void customizeAnimationBehavior() const;

    /***
     * @brief The properties of this class is set inside this method.
     ***/
    void customizeWidget();

protected:
    /***
     * @brief reimplemented version of enterEvent to start Expand animation.
     ***/
    void enterEvent(QEnterEvent *event) override;

    /***
     * @brief reimplemented version of leaveEvent, to start contract
     * animation.
     ***/
    void leaveEvent(QEvent *event) override;

public:
    explicit RegularButton();
    explicit RegularButton(QWidget* parent = nullptr);
    explicit RegularButton(const QString& text, QWidget* parent = nullptr);

    /***
     * @param width
     * @param height
     * @brief Takes width, height from the user and stores it into SIZE_HINT
     * variable.
     ***/
    void setSizeHint(int width, int height);

    /***
     * @brief reimplemented version of sizeHint() method to provide
     * user given size as size hint.
     ***/
    [[nodiscard]] QSize sizeHint() const override;

    /***
     * @param maxWidth
     * @param maxHeight
     * @param minWidth
     * @param minHeight
     * @brief Accepts these parameters from the user and set values
     * for hover animation. maxWidth, maxHeight is used for maximum
     * animation size & minWidth, minHeight is used for minimum
     * animation size.
     * @attention :
     * 1. minWidth <= maxWidth
     * 2. minHeight <= maxHeight
     * 3. All the variables should be greater than equal to zero
     ***/
    void setResizeHoverAnimationParameters(
        int maxWidth, int maxHeight,
        int minWidth, int minHeight
    );
};

