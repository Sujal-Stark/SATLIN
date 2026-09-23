//
// Created by sujal-stark on 9/9/26.
//

#pragma once
#include <QThread>
#include <sqlite3.h>
#include <QString>
#include <qdebug.h>


class DatabaseConnectivityCheckerThread : public QThread{
    Q_OBJECT
    const std::string* dbFilePath = nullptr;
    const std::string* txtTblName = nullptr;
    const std::string* imgTblName = nullptr;
    const std::string* vidTblName = nullptr;
    const std::string* audTblName = nullptr;

protected:
    void run() override;

public:
    void set(
        const std::string* filePath, const std::string* txtTbl, const std::string* imgTbl,
        const std::string* vidTbl, const std::string* audTbl
    );

    signals:
    void executionCompleted(void* db);
};
