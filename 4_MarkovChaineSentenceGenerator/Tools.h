#pragma once

#include <QDebug>
#include <sstream>
#include <stdexcept>

namespace core
{
auto createError(const std::string &file, const int line, const std::string &what) -> std::runtime_error;

auto logMessage(QDebug &&stream, const std::string &file, const int line) -> QDebug;

}  // namespace core


#define RUNTIME_ERROR(what) core::createError(__FILE__, __LINE__, what)

#define QDEBUG() core::logMessage(qDebug(), __FILE__, __LINE__)
#define QINFO() core::logMessage(qInfo(), __FILE__, __LINE__)
#define QWARNING() core::logMessage(qWarning(), __FILE__, __LINE__)
