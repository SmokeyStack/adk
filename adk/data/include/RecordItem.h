#ifndef RECORDITEM_H
#define RECORDITEM_H

#include <string>

#include "Item.h"
#include "ItemProperty.h"
#include "json.hpp"

class RecordItem : public Item {
   protected:
    std::string _sound;
    float _duration;
    int _signal;

   public:
    RecordItem() {}
    /// @brief Represents a Tool Item
    /// @param property
    /// @param durability
    /// @param damage_chance_min
    /// @param damage_chance_max
    /// @param blocks
    RecordItem(ItemProperty::Property property, std::string sound,
               float duration, int signal = 0) {
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
        _sound = sound;
        _duration = duration;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the item
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Item::output(mod_id, id);

        j["minecraft:item"]["components"]["minecraft:record"] = {
            {"sound_event", _sound},
            {"duration", _duration},
            {"comparator_signal", _signal}};

        return j;
    }
};

#endif