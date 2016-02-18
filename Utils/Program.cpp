#include "Program.h"
#include "LogMgr.h"

namespace Utils
{

Program::Program(int argc, char** argv) :
    _argc(argc),
    _argv(argv)
{
}

Program::~Program()
{
}

void Program::start()
{
    try
    {
        onLoad();
        onStart();
        onTerminate();
    }
    catch (const std::exception& exc)
    {
        LogMgr::cout().error("Exception cought:");
        LogMgr::cout().error(exc.what());
    }
    catch (...)
    {
        LogMgr::cout().error("Unkown excpetion cought in the program.");
    }
}

} // namespace Utils

