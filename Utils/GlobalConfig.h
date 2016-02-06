#pragma once

#include "NotInstantiable.h"
#include "StringUtils.h"

#include <string>
#include <unordered_map>
#include <mutex>

namespace Utils
{

class GlobalConfig :: NotInstantiable
{
public:
    static void init(const std::string& filename, int argc, char** argv);
    static void init(const std::string& filename);
    static void init(int argc, char** argv);

    static int getInt(const std::string& section, const std::string& name, const int fallback = 0);
    static double getDouble(const std::string& section, const std::string& name, const double fallback = 0.0);
    static const std::string& getString(const std::string& section, const std::string& name, const std::string& fallback = empty_string);
    static bool getInD(const std::string& section, const std::string& name, const bool fallback = false);

    static void defineVariable(const std::string& section, const std::string& name, const std::string& value);
    static void defineVariable(const std::string& name, const std::string& value);

    static const std::string DEFAULT_SECTION;

private:

    static void loadConfigFromFile(const std::string& filename);
    static void loadConfigFromCommandLine(int argc, char** argv);

    // Map structure:
    // Key: pair of <Section, Name> in one string: Section + "::" + Name
    // Value: variable value
    static std::unordered_map<std::string, std::string> s_variables;
    static std::mutex s_mutex;
};

} // namespace Utils

