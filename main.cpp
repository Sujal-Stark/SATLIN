#include <QApplication>

#include "Ui/MasterWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *masterWindow = new MasterWindow();
    masterWindow->show();

    QApplication::exec();
}
