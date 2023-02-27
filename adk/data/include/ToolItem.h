#ifndef TOOLITEM_H
#define TOOLITEM_H

#include <string>

#include "DurabilityItem.h"
#include "ItemProperty.h"
#include "json.hpp"

class ToolItem : public DurabilityItem {
   protected:
    std::multimap<int, std::string> _set_of_blocks;

   public:
    ToolItem() {}
    /// @brief Represents a Tool Item
    /// @param property
    /// @param durability
    /// @param damage_chance_min
    /// @param damage_chance_max
    /// @param blocks
    ToolItem(ItemProperty::Property property, int durability,
             int damage_chance_min, int damage_chance_max,
             std::multimap<int, std::string> blocks) {
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
        _set_of_blocks = blocks;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the item
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = DurabilityItem::output(mod_id, id);

        std::vector<int> list;

        for (auto const& entry : _set_of_blocks) {
            if (!(std::find(list.begin(), list.end(), entry.first) !=
                  list.end())) {
                std::pair<std::multimap<int, std::string>::iterator,
                          std::multimap<int, std::string>::iterator>
                    looper;
                looper = _set_of_blocks.equal_range(entry.first);
                json temp;

                for (std::multimap<int, std::string>::iterator it =
                         looper.first;
                     it != looper.second; ++it)
                    temp["blocks"].push_back(it->second);

                temp["speed"] = entry.first;
                j["minecraft:item"]["components"]["minecraft:digger"]
                 ["destroy_speeds"]
                     .push_back(temp);
                list.push_back(entry.first);
            }
        }

        j["minecraft:item"]["components"]["minecraft:digger"]["on_dig"]
         ["event"] = mod_id + ":damage_item";
        j["minecraft:item"]["events"][mod_id + ":damage_item"]["damage"] = {
            {"type", "durability"}, {"amount", 1}, {"target", "self"}};

        return j;
    }
};

#endif