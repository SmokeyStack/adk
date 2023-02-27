#ifndef FUELITEM_H
#define FUELITEM_H

#include <string>

#include "Item.h"
#include "ItemProperty.h"
#include "json.hpp"

class FuelItem : public Item {
   protected:
    float _burn_time;

   public:
    FuelItem() {}
    /// @brief Represents a Fuel Item
    /// @param property An ItemProperty object
    /// @param burn_time How long in seconds will this fuel cook items for
    FuelItem(ItemProperty::Property property, float burn_time) {
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
        _burn_time = burn_time;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the item
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Item::output(mod_id, id);

        j["minecraft:item"]["components"]["minecraft:fuel"]["duration"] =
            _burn_time;

        return j;
    }
};

#endif