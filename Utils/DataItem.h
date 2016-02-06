#pragma once

#include <string>

namespace Utils
{

// Base class for all Items stored in DataDictionary.
// If you what you object be stored in DD,
// it must inharit from this class.
// Method ,,name'' must stay public in derived classes.
class DataItem
{
public:
    DataItem(const std::string& name)
        : _name(name)
    {
    }

    const std::string& name() const { return _name; }

private:
    
    std::string _name;

};

} // namespace Utils

