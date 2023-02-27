#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>

#include "Item.h"
#include "ItemProperty.h"
#include "json.hpp"

class FoodItem : public Item {
   protected:
    int _nutrition;
    float _saturation;
    bool _always_eat;
    std::string _convert;

   public:
    FoodItem() {}
    /// @brief Represents a Food Item
    /// @param property An ItemProperty object
    /// @param nutrition The value that is added to the actor's nutrition when
    /// the item is used
    /// @param saturation Saturation Modifier is used in this formula:
    /// (nutrition * saturation_modifier * 2) when applying the saturation buff
    /// @param always_eat If true you can always eat this item (even when not
    /// hungry). Default is set to false
    /// @param convert When used, converts to the item specified by the string
    /// in this field. Default does not convert item
    FoodItem(ItemProperty::Property property, int nutrition, float saturation,
             bool always_eat = false, std::string convert = "") {
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
        _nutrition = nutrition;
        _saturation = saturation;
        _always_eat = always_eat;
        _convert = convert;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the item
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Item::output(mod_id, id);

        j["minecraft:item"]["components"]["minecraft:food"] = {
            {"nutrition", _nutrition},
            {"saturation", _saturation},
            {"can_always_eat", _always_eat},
            {"using_converts_to", _convert}};

        return j;
    }
};

#endif