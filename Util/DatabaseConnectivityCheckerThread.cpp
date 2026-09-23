//
// Created by sujal-stark on 9/9/26.
//

#include "DatabaseConnectivityCheckerThread.h"

#include <filesystem>

void DatabaseConnectivityCheckerThread::run() {
    sqlite3* db;

    if (
        sqlite3_open_v2(this->dbFilePath->c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr)
        != SQLITE_OK
    ) throw std::runtime_error(sqlite3_errmsg(db));

    for (const std::string * name : {this->txtTblName, this->imgTblName, this->vidTblName, this->audTblName}) {
        std::string query = "CREATE TABLE IF NOT EXISTS " + *name + "("
            "Hash VARCHAR(300) PRIMARY KEY,"
            "FilePath VARCHAR(100) UNIQUE,"
            "FileSize INT NOT NULL,"
            "saveStat INT NOT NULL,"
            "Ext VARCHAR(20) NOT NULL,"
            "TimeStamp VARCHAR(50) NOT NULL"
        ")";

        char* errMessage;

        if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMessage) != SQLITE_OK) {
            throw std::runtime_error("Can't create tables!!");
        }

        sqlite3_free(errMessage);
        query = "DELETE FROM " + *name + ";";

        if(sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMessage) != SQLITE_OK) {
            throw std::runtime_error("Unable to truncate tables: ");
        }
    }

    sqlite3_close(db);

    emit this->executionCompleted(db);
}

void DatabaseConnectivityCheckerThread::set(
    const std::string* filePath, const std::string* txtTbl, const std::string* imgTbl,
    const std::string* vidTbl, const std::string* audTbl
){
    if (filePath == nullptr || txtTbl == nullptr || imgTbl == nullptr || vidTbl == nullptr || audTbl == nullptr) {
        throw std::runtime_error(
            "Either filePath or table name variables points to null"
        );
    }

    this->dbFilePath = filePath;
    this->txtTblName = txtTbl;
    this->imgTblName = imgTbl;
    this->vidTblName = vidTbl;
    this->audTblName = audTbl;
}
