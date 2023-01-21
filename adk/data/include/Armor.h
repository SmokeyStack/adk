#ifndef ARMOR_H
#define ARMOR_H

#include <iostream>
#include <map>
#include <string>

#include "Item.h"
#include "ItemProperty.h"
#include "json.hpp"

enum ArmorSlot { HEAD, CHEST, LEGS, FEET };

std::string getArmorSlot(ArmorSlot slot) {
    switch (slot) {
        case HEAD:
            return "slot.armor.head";
        case CHEST:
            return "slot.armor.chest";
        case LEGS:
            return "slot.armor.legs";
        case FEET:
            return "slot.armor.feet";
        default:
            return "Error";
    }
}

class Armor : public Item {
   protected:
    int _protection;
    std::string _slot;
    int _durability;

   public:
    Armor(ItemProperty::Property property, int protection, ArmorSlot test,
          int durability) {
        display_name = property.display_name;
        stack = property.stack;
        _protection = protection;
        _slot = getArmorSlot(test);
        _durability = durability;
    }
    json output(std::string mod_id, std::string id) {
        j = Item::output(mod_id, id);
        j["minecraft:item"]["components"]["minecraft:armor"]["protection"] =
            _protection;
        j["minecraft:item"]["components"]["minecraft:wearable"]["slot"] = _slot;
        j["minecraft:item"]["components"]["minecraft:durability"]
         ["max_durability"] = _durability;

        return j;
    }
};

#endif