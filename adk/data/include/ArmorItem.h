#ifndef ARMORITEM_H
#define ARMORITEM_H

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
    bool _dispensable;
    int _damage_chance_min;
    int _damage_chance_max;

   public:
    Armor(ItemProperty::Property property, int protection, ArmorSlot test,
          int durability, bool dispensable, int damage_chance_min,
          int damage_chance_max) {
        display_name = property.display_name;
        stack = property.stack;
        _protection = protection;
        _slot = getArmorSlot(test);
        _durability = durability;
        _dispensable = dispensable;
        _damage_chance_min = damage_chance_min;
        _damage_chance_max = damage_chance_max;
    }

    json output(std::string mod_id, std::string id) {
        j = Item::output(mod_id, id);
        j["minecraft:item"]["components"]["minecraft:armor"]["protection"] =
            _protection;
        j["minecraft:item"]["components"]["minecraft:wearable"]["slot"] = _slot;
        j["minecraft:item"]["components"]["minecraft:wearable"]["dispensable"] =
            _dispensable;
        j["minecraft:item"]["components"]["minecraft:durability"]
         ["max_durability"] = _durability;
        j["minecraft:item"]["components"]["minecraft:durability"]
         ["damage_chance"]["min"] = _damage_chance_min;
        j["minecraft:item"]["components"]["minecraft:durability"]
         ["damage_chance"]["max"] = _damage_chance_max;

        return j;
    }
};

#endif