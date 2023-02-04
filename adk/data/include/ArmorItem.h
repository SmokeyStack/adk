#ifndef ARMORITEM_H
#define ARMORITEM_H

#include <string>

#include "Item.h"
#include "ItemProperty.h"
#include "json.hpp"

enum ArmorSlot { HEAD, CHEST, LEGS, FEET };

/// @brief Turns enum ArmorSlot into string
/// @param slot enum ArmorSlot
/// @return String equivalent
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

class ArmorItem : public Item {
   protected:
    int _protection;
    std::string _slot;
    int _durability;
    bool _dispensable;
    int _damage_chance_min;
    int _damage_chance_max;

   public:
    ArmorItem() {}
    /// @brief Represents an Armor Item
    /// @param property An ItemProperty object
    /// @param protection How much protection point should this armor give
    /// @param slot Which slot should the armor go in
    /// @param durability How much durability point should this armor have
    /// @param dispensable Can this armor be equipped by a dispenser
    /// @param damage_chance_min Minimum chance the armor takes damage
    /// @param damage_chance_max Maximum chance the armor takes damage
    ArmorItem(ItemProperty::Property property, int protection, ArmorSlot slot,
              int durability, bool dispensable, int damage_chance_min,
              int damage_chance_max) {
        _display_name = property.display_name;
        _stack = property.stack;
        _protection = protection;
        _slot = getArmorSlot(slot);
        _durability = durability;
        _dispensable = dispensable;
        _damage_chance_min = damage_chance_min;
        _damage_chance_max = damage_chance_max;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the item
    /// @return json object
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