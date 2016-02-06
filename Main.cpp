#include "Utils/Logger.h"
#include "Utils/LogMgr.h"
#include "Utils/GlobalConfig.h"
#include "Utils/DataDictionary.h"
#include "Utils/DataItem.h"
#include "Utils/StringUtils.h"

#include <iostream>
#include <memory>
#include <stdexcept>

using Utils::Logger;
using Utils::LogMgr;
using Utils::GlobalConfig;
using Utils::DataDictionary;
using Utils::DataItem;
using Utils::StringUtils;

const std::string LogFile1 = "dupa.log";
const std::string ID1 = "dupa1";
const std::string HEAD = "Program::Main()";

int main(int argc, char** argv)
{
    try
    {
        auto& log LogMgr::cout();
        
        LogMgr::turnOnDebugLogs();


    }
    catch (const std::exception& exc)
    {
        std::cerr << exc.what() << std::endl;
    }

    return 0;
}


