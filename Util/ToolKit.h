//
// Created by sujal-stark on 8/26/26.
//

#pragma once
#include <QFileInfo>
#include <qglobal.h>
#include <QString>

namespace ToolKit {
    [[nodiscard]] inline qint32 getFileSize(const QString& file) {
        return static_cast<qint32>(QFileInfo(file).size());
    }

    [[nodiscard]] inline qint32 getFileSize(const std::string& file) {
        return static_cast<qint32>(
            QFileInfo(QString::fromStdString(file)).size()
        );
    }
}
