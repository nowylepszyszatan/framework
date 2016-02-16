#include "Logger.h"
#include "LogException.h"

#include <ctime>
#include <string>
#include <mutex>
#include <iostream>
#include <iomanip>

namespace Utils
{

// Logging levels
static const std::string INF_STRING = "Info";
static const std::string WRN_STRING = "Warning";
static const std::string ERR_STRING = "Error";
static const std::string DTA_STRING = "Data";
static const std::string DBG_STRING = "Debug";

Logger::Logger(const std::string& filename) :
    _autoflush(false),
    _logToConsole(false),
    _logDebug(false),
    _logData(false)
{
    _out.open(filename);

    if (_out.is_open())
    {
        std::cerr << "Logger::Logger() Failed to open log file: " + filename << std::endl;

        throw LogException("Logger::Logger() Failed to open log file: " + filename);
    }

    info("start of log file " + filename, "");
}

Logger::Logger() :
    _autoflush(false),
    _logToConsole(true),
    _logDebug(false),
    _logData(false)
{
}

Logger::~Logger()
{
    if (_out.is_open())
    {
        close();
    }
}

Logger& Logger::info(const std::string& header, const std::string& msg)
{
    writeLine(INF_STRING, header, msg);

    return *this;
}


Logger& Logger::warning(const std::string& header, const std::string& msg)
{
    writeLine(WRN_STRING, header, msg);

    return *this;
}

Logger& Logger::error(const std::string& header, const std::string& msg)
{
    writeLine(ERR_STRING, header, msg);

    return *this;
}

Logger& Logger::data(const std::string& header, const std::string& msg)
{
    if (_logData)
        writeLine(DTA_STRING, header, msg);

    return *this;
}

Logger& Logger::debug(const std::string& header, const std::string& msg)
{
    if (_logDebug)
        writeLine(DBG_STRING, header, msg);

    return *this;
}

// ---------------------------------
// Main formatting method.
// it is guard by mutex, so only single
// thread is able to write into the
// log file at once.
// (this logger is not high-performance)
// ---------------------------------
void Logger::writeLine(const std::string& type, const std::string& header, const std::string& msg)
{
    std::lock_guard<std::mutex> lock(_log_mutex);

    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    auto timeinfo = localtime(&now_c);

    strftime(_buf, sizeof(_buf), "%Y-%m-%d %H:%:M:%S", timeinfo);

    if (_logToConsole)
        std::cout << _buf << "\t" << type << "\t" << header << "\t" << msg << std::endl;
    else
        _out      << _buf << "\t" << type << "\t" << header << "\t" << msg << std::endl;

    if (_autoflush)
        _out.flush();
}

Logger& Logger::flush()
{
    if (_out.is_open())
        _out.flush();

    return *this;
}

Logger& Logger::close()
{
    if (_out.is_open())
    {
        info("end of log file.", "").flush();

        _out.close();
    }

    return *this;
}

} // namespace Utils

