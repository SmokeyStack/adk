#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "ItemProperty.h"
#include "json.hpp"

class Item {
   protected:
    std::string _display_name;
    int _stack;

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "items/"; };

    Item(){};
    /// @brief Represents an item
    /// @param property An ItemProeprty object
    Item(ItemProperty::Property property) {
        _display_name = property.display_name;
        _stack = property.stack;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the item
    /// @return json object
    virtual json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.50";
        j["minecraft:item"]["components"]["minecraft:display_name"]["value"] =
            _display_name;
        j["minecraft:item"]["components"]["minecraft:max_stack_size"] = _stack;
        j["minecraft:item"]["description"]["identifier"] = mod_id + ":" + id;

        return j;
    }
};

#endif