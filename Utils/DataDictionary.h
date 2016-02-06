#pragma once

#include "DataItem.h"
#include "NoCopyable.h"

#include <string>
#include <memory>
#include <unordered_map>

namespace Utils
{

// Big, hierarchical storage for all data inside project.
// All item have unique names to choose them.
//
// Bu sure to create each object using make_shared so it wil
// not disapear while still inside dictionary.
class DataDictionary : public DataItem, NoCopyable
{
public:

//typedefs:
    typedef std::unordered_map<std::string, std::shared_ptr<DataItem>> Dictionary;
    typedef Dictionary::value_type value_type;
    typedef Dictionary::iterator iterator;
    typedef Dictionary::const_iterator const_iterator;

// public methods
    DataDictionary(const std::string& name)
        : DataItem(name)
    {
    }

    void addNewItem(const std::shared_ptr<DataItem> item);
    void replaceItem(const std::shared_ptr<DataItem> item);
    void removeItem(const std::string& name);

    std::shared_ptr<DataItem> getItem(const std::string& name);

// iterators and other STL-like methods
    iterator       begin()       noexcept { return _dictionary.begin(); }
    iterator       end()         noexcept { return _dictionary.end();   }
    const_iterator begin() const noexcept { return _dictionary.begin(); }
    const_iterator end()   const noexcept { return _dictionary.end();   }
    bool           empty() const          { return _dictionary.empty(); }
    size_t         size()  const          { return _dictionary.size();  }
    void           clear()                { return _dictionary.clear(); }

private:

    Dictionary _dictionary;

};

} // namespace Utils

