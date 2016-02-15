#pragma once

#include "Logger.h"
#include "NotInstantiable.h"

#include <unordered_map>
#include <memory>
#include <string>

namespace Utils
{

// ---------------------------
// LogMgr class to used together with Logger.h
// It is able to store number of loggers and choose them
// using string as a name.
// This class is fully static and should be used as global
// storage for loggers, making them available anywhere 
// in the project.
// ---------------------------
class LogMgr : NotInstantiable
{
public:

    static Logger& get(const std::string& loggerId);
    static Logger& cout();
    static Logger& createLogger(const std::string& fileName, const std::string& loggerId);
    static void closeLogger(const std::string& loggerId);
    static void closeAllLoggers();
    static void turnOnDebugLogs();
    static void turnOffDebugLogs();
    static void turnOnDataLogs();
    static void turnOffDataLogs();

    static const std::string COUT_ID;

private:

    static Logger& findLogger(const std::string& loggerId);

    static std::unordered_map<std::string, std::shared_ptr<Logger>> s_loggers;

    static std::mutex s_mgrMutex;
};

} // namespace Utils

