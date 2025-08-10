//
// Created by sujal-stark on 8/11/25.
//

#ifndef SATLIN_MASTER_WINDOW_H
#define SATLIN_MASTER_WINDOW_H

#include <QMainWindow>

class MasterWindow final : public QMainWindow {
    Q_OBJECT
    public:
        explicit MasterWindow(QWidget *parent = nullptr);
};

#endif //SATLIN_MASTER_WINDOW_H