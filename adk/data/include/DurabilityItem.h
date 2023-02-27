#ifndef DURABILITYITEM_H
#define DURABILITYITEM_H

#include <string>

#include "Item.h"
#include "ItemProperty.h"
#include "json.hpp"

class DurabilityItem : public Item {
   protected:
    int _durability;
    int _damage_chance_min;
    int _damage_chance_max;

   public:
    DurabilityItem() {}
    /// @brief Represents an Armor Item
    /// @param property An ItemProperty object
    /// @param protection How much protection point should this armor give
    /// @param slot Which slot should the armor go in
    /// @param durability How much durability point should this armor have
    /// @param dispensable Can this armor be equipped by a dispenser
    /// @param damage_chance_min Minimum chance the armor takes damage
    /// @param damage_chance_max Maximum chance the armor takes damage
    DurabilityItem(ItemProperty::Property property, int durability,
                   int damage_chance_min, int damage_chance_max) {
        _display_name = property.display_name;
        _icon = property.icon;
        _stack = property.stack;
        _block_placer = property.block_placer;
        _block_placer_placement = property.block_placer_placement;
        _cooldown_category = property.cooldown_category;
        _cooldown_time = property.cooldown_time;
        _dye = property.dye;
        _entity_placer = property.entity_placer;
        _entity_placer_placement = property.entity_placer_placement;
        _entity_placer_dispense = property.entity_placer_dispense;
        _offset_main = property.offset_main;
        _offset_offhand = property.offset_offhand;
        _durability = durability;
        _damage_chance_min = damage_chance_min;
        _damage_chance_max = damage_chance_max;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the item
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Item::output(mod_id, id);

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