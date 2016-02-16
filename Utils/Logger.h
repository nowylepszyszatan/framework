#pragma once

#include "StringUtils.h"

#include <fstream>
#include <mutex>
#include <string>

namespace Utils
{

// Simple logger class.
// It allows user to log into log file or to std::cout
// using stardarize format
class Logger
{
public:

    Logger(const std::string& filename);
    Logger();
    ~Logger();

    // Each log line contains timestamp, log level, header and message.
    // Header is optional. If you provide only one parameter, then it will be treated as message.
    Logger& info(const std::string& header, const std::string& msg = empty_string);
    Logger& warning(const std::string& header, const std::string& msg = empty_string);
    Logger& error(const std::string& header, const std::string& msg = empty_string);
    Logger& data(const std::string& header, const std::string& msg = empty_string);
    Logger& debug(const std::string& header, const std::string& msg = empty_string);

    Logger& flush();
    Logger& close();

    void setAutoFlush(bool autoflush) { _autoflush = autoflush; }
    bool autoflush() { return _autoflush; }

    void turnOnDebugLogs() { _logDebug = true; }
    void turnOffDebugLogs() { _logDebug = false; }
    void turnOnDataLogs() { _logData = true; }
    void turnOffDataLogs() { _logData = false; }

private:

    void writeLine(const std::string& type, const std::string& header, const std::string& msg);

    bool _autoflush;
    bool _logToConsole;
    bool _logDebug;
    bool _logData;
    char _buf[32];
    std::ofstream _out;
    std::mutex _log_mutex;
};

} // namespace Utils

