#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "ItemProperty.h"
#include "json.hpp"

class Item {
   protected:
    std::string display_name;
    std::string icon;
    int stack;

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "items/"; };

    Item(){};
    Item(ItemProperty::Property property) {
        display_name = property.display_name;
        icon = property.icon;
        stack = property.stack;
    }

    virtual json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.50";
        j["minecraft:item"]["components"]["minecraft:display_name"]["value"] =
            display_name;
        j["minecraft:item"]["components"]["minecraft:max_stack_size"] = stack;
        j["minecraft:item"]["description"]["identifier"] = mod_id + ":" + id;

        return j;
    }
};

#endif