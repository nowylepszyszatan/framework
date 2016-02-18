#pragma once

namespace Utils
{

class Program
{
public:
    Program(int argc, char** argv);
    ~Program();

    void start();

protected:
    virtual void onLoad() {}
    virtual void onStart() {}
    virtual void onTerminate() {}

    int _argc;
    char** _argv;
};

} // namespace Utils

