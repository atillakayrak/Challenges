#include "Tools.h"


static auto extractFileName(const std::string &path)
{
    const auto lastSeparator1 = path.find_last_of('\\');
    if (std::string::npos != lastSeparator1)
        return std::string(path.begin() + lastSeparator1 + 1, path.end());

    const auto lastSeparator2 = path.find_last_of('/');
    if (std::string::npos != lastSeparator2)
        return std::string(path.begin() + lastSeparator2 + 1, path.end());

    return path;
}


static auto createHeader(const std::string &file, const int line)
{
    return (std::stringstream() << "[" << extractFileName(file) << ":" << line << "]").str();
}


auto core::createError(const std::string &file, const int line, const std::string &what)
    -> std::runtime_error
{
    return std::runtime_error(createHeader(file, line) + " EXCEPTION : " + what);
}


auto core::logMessage(QDebug &&stream, const std::string &file, const int line) -> QDebug
{
    return stream << createHeader(file, line).c_str();
}
