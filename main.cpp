#include <QApplication>

#include "Ui/MasterWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *masterWindow = new MasterWindow();

    QFont font("Georgia", 12);
    font.setWeight(QFont::Medium);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 0.5);

    app.setFont(font);

    app.setStyleSheet(
        R"(
            QWidget{
                background-color : #011633;
            }

            QTabBar::tab{
                min-width : 150px;
                max-width : 150px;
            }
        )"
    );

    masterWindow->show();

    QApplication::exec();
}
