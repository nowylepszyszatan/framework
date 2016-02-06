#include "DataDictionary.h"
#include "DuplicateItemException.h"

namespace Utils
{

void DataDictionary::addNewItem(const std::shared_ptr<DataItem> item)
{
    if (_dictionary.find(item->name()) == _dictionary.end())
    {
        _distionary.emplace(item->name(), item);
    }
    else
    {
        throw DuplicateItemException("Trying to insert item with duplicate id: " + item->name());
    }
}

void DataDictionary::replaceItem(const std::shared_ptr<DataItem> item)
{
    _dictionary[item->name()] = item;
}

void DataDictionary::removeItem(const std::string& name)
{
    _dictionary.erase(name);
}

std::shared_ptr<DataItem> DataDictionary::getItem(const std::string& name)
{
    auto map_item = _dictionary.find(name);

    if (map_item != _dictionary.end())
        return map_item->second;

    return nullptr; // TBD: maybe throw exception?
}

} // namespace Utils

