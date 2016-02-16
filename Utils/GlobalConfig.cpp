#include "GlobalConfig.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

namespace Utils
{

const std::string GlobalConfig::DEFAULT_SECTION = "Global";

std::unordered_map<std::string, std::string> GlobalConfig::s_variables;
std::mutex GlobalConfig::s_mutex;

void parseConfigLine(const std::string& line, const std::string& actualSection)
{
    size_t sectionNameEnd = line.find("::");
    std::string sectionName = (sectionNameEnd == std::string::npos)
                              ? actualSection
                              : line.substr(0, sectionNameEnd);
    size_t variableNameStart = (sectionNameEnd == std::string::npos) ? 0 : sectionNameEnd + 2;
    size_t variableNameEnd = line.find("=");

    if ((sectionNameEnd != std::string::npos) && (sectionNameEnd > variableNameEnd))
        throw std::runtime_error("Cannot use \"=\" in section name: " + line);

    if (variableNameEnd == std::string::npos)
        throw std::runtime_error("Missing \"=\" in config line: " + line);

    if (variableNameEnd - variableNameStart < 1)
        throw std::runtime_error("Missing variable name in config line: " + line);

    if (line.length() - variableNameEnd < 1)
        throw std::runtime_error("Missing variable value in config line: " + line);

    std::string variableName  = line.substr(variableNameStart, variableNameEnd - variableNameStart);
    std::string variableValue = line.substr(variableNameEnd + 1, line.length() - variableNameEnd);

    if (variableValue.size() && ispunct(variableValue[0]) && variableValue[0] != '/')
    {
        std::cerr << "Warning: found punctation at start of variable, probably a mistake. Line is: " << line << std::endl;
    }

    GlobalConfig::defineVariable(sectionName, variableName, variableValue);
}

std::string parseSectionLine(const std::string& line)
{
    if (line.front() == '[' && line.back() == ']')
    {
        return line.substr(1, line.length() - 2);
    }
    else
    {
        throw std::runtime_error("Wrong format of section token: " + line);
    }
}

void parseLine(const std::string& line)
{
    static std::string section = GlobalConfig::DEFAULT_SECTION;

    if (line.empty())
        return;

    if (line.front() == '#')
        return;

    if (line.front() == '[')
    {
        section = parseSectionLine(line);
        return;
    }
    
    if (line.find("=") != std::string::npos)
    {
        parseConfigLine(line, section);
    }
}

void GlobalConfig::init(const std::string& filename, int argc, char** argv)
{
    loadConfigFromFile(filename);
    loadConfigFromCommandLine(argc, argv);
}

void GlobalConfig::init(const std::string& filename)
{
    loadConfigFromFile(filename);
}

void GlobalConfig::init(int argc, char** argv)
{
    loadConfigFromCommandLine(argc, argv);
}

int GlobalConfig::getInt(const std::string& section, const std::string& name, const int fallback)
{
    auto x = s_variables.find(section + "::" + name);

    if (x != s_variables.end())
    {
        return std::stoi(x->second);
    }
    else
    {
        return fallback;
    }
}

double GlobalConfig::getDouble(const std::string& section, const std::string& name, const double fallback)
{
    auto x = s_variables.find(section + "::" + name);

    if (x != s_variables.end())
    {
        return std::stod(x->second);
    }
    else
    {
        return fallback;
    }
}

const std::string& GlobalConfig::getString(const std::string& section, const std::string& name, const std::string& fallback)
{
    auto x = s_variables.find(section + "::" + name);

    if (x != s_variables.end())
    {
        return x->second;
    }
    else
    {
        return fallback;
    }
}

bool GlobalConfig::getInd(const std::string& section, const std::string& name, const bool fallback)
{
    auto x = s_variables.find(section + "::" + name);

    if (x != s_variables.end())
    {
        return (x->second == "y" || x->second == "Y");
    }
    else
    {
        return fallback;
    }
}

void GlobalConfig::defineVariable(const std::string& section, const std::string& name, const std::string& value)
{
    std::lock_guard<std::mutex> lock(s_mutex);

    std::string key = section + "::" + name;

    s_variables[key] = value;
}

void GlobalConfig::defineVariable(const std::string& name, const std::string& value)
{
    defineVariable(DEFAULT_SECTION, name, value);
}

void GlobalConfig::loadConfigFromFile(const std::string& filename)
{
    std::ifstream input;
    input.open(filename);

    if (input.is_open())
    {
        while (input.good())
        {
            std::string line;
            getline(input, line);
            parseLine(line);
        }
    }
    else
    {
        std::cerr << "Cannot open input file: " << filename << std::endl;
    }
}

void GlobalConfig::loadConfigFromCommandLine(int argc, char** argv)
{
    try
    {
        for (int i = 1; i < argc; i++)
        {
            parseConfigLine(argv[i], DEFAULT_SECTION);
        }
    }
    catch (const std::runtime_error& exc)
    {
        std::cerr << exc.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Uknown exception while parsing command line! " << std::endl;
    }
}

} // namespace Utils

