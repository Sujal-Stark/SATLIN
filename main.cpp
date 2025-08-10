#include <QApplication>

#include "MasterWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto *masterWindow = new MasterWindow();
    masterWindow->show();

    app.exec();
}
