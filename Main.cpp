#include "Utils/Logger.h"
#include "Utils/LogMgr.h"
#include "Utils/GlobalConfig.h"
#include "Utils/DataDictionary.h"
#include "Utils/DataItem.h"
#include "Utils/StringUtils.h"
#include "Utils/Singleton.h"
#include "Utils/ThreadPool.h"
#include "Utils/Program.h"

#include <iostream>
#include <memory>
#include <stdexcept>

using Utils::Logger;
using Utils::LogMgr;
using Utils::GlobalConfig;
using Utils::DataDictionary;
using Utils::DataItem;
using Utils::StringUtils;
using Utils::Program;

const std::string LogFile1 = "dupa.log";
const std::string ID1 = "dupa1";
const std::string HEAD = "Program::Main()";

class Test : public Program
{
public:
    Test(int argc, char** argv) :
        Program(argc, argv)
    {
    }

    void onLoad()
    {
        LogMgr::turnOnDebugLogs();
        auto& log = LogMgr::cout();
        log.info(HEAD, "starting up");
    }

    void onStart()
    {
        auto& log = LogMgr::cout();
        log.info(HEAD, "running");
    }

    void onTerminate()
    {
        auto& log = LogMgr::cout();
        log.info(HEAD, "terminating");
    }   
};


int main(int argc, char** argv)
{
    Test t{argc, argv};

    t.start();

    return 0;
}



