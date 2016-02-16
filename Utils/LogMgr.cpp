#include "LogMgr.h"
#include "LogException.h"

#include <iostream>

namespace Utils
{

const std::string LogMgr::COUT_ID = "_LogMgr_cout_id_";

std::unordered_map<std::string, std::shared_ptr<Logger>> LogMgr::s_loggers = { {LogMgr::COUT_ID, std::make_shared<Logger>() } };

std::mutex LogMgr::s_mgrMutex;

Logger& LogMgr::get(const std::string& loggerId)
{
    return findLogger(loggerId);
}

Logger& LogMgr::cout()
{
    return findLogger(LogMgr::COUT_ID);
}

Logger& LogMgr::createLogger(const std::string& filename, const std::string& loggerId)
{
    std::lock_guard<std::mutex> lock(s_mgrMutex);

    auto logger = s_loggers.find(loggerId);

    // create new logger
    if (logger == s_loggers.end())
    {
        auto newLogger = std::make_shared<Logger>(filename);

        s_loggers.emplace(loggerId, newLogger);

        return *newLogger;
    }
    // else if logger already exists
    else
    {
        std::cerr << "Logger with id: " << loggerId << " already exists!" << std::endl;

        return *(logger->second);
    }
}

Logger& LogMgr::findLogger(const std::string& loggerId)
{
    std::lock_guard<std::mutex> lock(s_mgrMutex);

    auto logger = s_loggers.find(loggerId);

    if (logger == s_loggers.end())
    {
        std::cerr << "Logger with id: " << loggerId << " doesn't exists! Redirecting to std::cout instead." << std::endl;

        logger = s_loggers.find(LogMgr::COUT_ID);
    }

    auto ptr = logger->second;
    return *ptr;
}

void LogMgr::closeLogger(const std::string& loggerId)
{
    std::lock_guard<std::mutex> lock(s_mgrMutex);

    auto logger = s_loggers.find(loggerId);

    if (logger == s_loggers.end())
    {
        std::cerr << "Logger with id: " << loggerId << " doesn't exists!" << std::endl;
    }
    else
    {
        logger->second->flush();
        logger->second->close();

        s_loggers.erase(logger);
    }
}

void LogMgr::closeAllLoggers()
{
    std::lock_guard<std::mutex> lock(s_mgrMutex);

    for (auto& logger : s_loggers)
    {
        logger.second->flush();
        logger.second->close();
    }

    s_loggers.clear();
}

void LogMgr::turnOnDebugLogs()
{
    std::lock_guard<std::mutex> lock(s_mgrMutex);

    for (auto& logger : s_loggers)
    {
        logger.second->turnOnDebugLogs();
    }
}

void LogMgr::turnOffDebugLogs()
{
    std::lock_guard<std::mutex> lock(s_mgrMutex);

    for (auto& logger : s_loggers)
    {
        logger.second->turnOffDebugLogs();
    }
}

void LogMgr::turnOnDataLogs()
{
    std::lock_guard<std::mutex> lock(s_mgrMutex);

    for (auto& logger : s_loggers)
    {
        logger.second->turnOnDataLogs();
    }
}

void LogMgr::turnOffDataLogs()
{
    std::lock_guard<std::mutex> lock(s_mgrMutex);

    for (auto& logger : s_loggers)
    {
        logger.second->turnOffDataLogs();
    }
}

} // namespace Utils

