#ifndef WEAPONITEM_H
#define WEAPONITEM_H

#include <string>

#include "DurabilityItem.h"
#include "ItemProperty.h"
#include "json.hpp"

class WeaponItem : public DurabilityItem {
   protected:
    int _damage;

   public:
    WeaponItem() {}
    /// @brief Represents a Tool Item
    /// @param property
    /// @param durability
    /// @param damage_chance_min
    /// @param damage_chance_max
    /// @param blocks
    WeaponItem(ItemProperty::Property property, int damage, int durability,
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
        _damage = damage;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the item
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = DurabilityItem::output(mod_id, id);

        j["minecraft:item"]["components"]["minecraft:damage"] = _damage;

        j["minecraft:item"]["components"]["minecraft:weapon"]
         ["on_hurt_entity"] = mod_id + ":damage_item";
        j["minecraft:item"]["events"][mod_id + ":damage_item"]["damage"] = {
            {"type", "durability"}, {"amount", 1}, {"target", "self"}};

        return j;
    }
};

#endif