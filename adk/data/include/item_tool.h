#ifndef TOOLITEM_H
#define TOOLITEM_H

#include <string>

#include "item_durability.h"
#include "item_property.h"
#include "json.hpp"

/**
 * @brief Represents a Tool Item
 *
 */
class ToolItem : public DurabilityItem {
   protected:
    std::multimap<int, std::string> _set_of_blocks;

   public:
    ToolItem() {}
    /**
     * @brief Construct a new Tool Item object
     *
     * @param property ItemProperty
     * @param durability How much durability point should this item have
     * @param damage_chance_min Minimum chance the item takes damage
     * @param damage_chance_max Maximum chance the item takes damage
     * @param blocks Key/Value pair of seconds and blocks
     */
    ToolItem(ItemProperty property, int durability, int damage_chance_min,
             int damage_chance_max, std::multimap<int, std::string> blocks) {
        _display_name = property.getName();
        _icon = property.getIcon();
        _stack = property.getStack();
        _block_placer = property.getBlockPlacer();
        _block_placer_placement = property.getBlockPlacerPlacement();
        _cooldown_category = property.getCooldownCategory();
        _cooldown_time = property.getCooldownTime();
        _dye = property.getDyeProperty();
        _entity_placer = property.getEntityPlacer();
        _entity_placer_placement = property.getEntityPlacerPlacement();
        _entity_placer_dispense = property.getEntityPlacerDispense();
        _offset_main = property.getOffsetMain();
        _offset_offhand = property.getOffsetOff();
        _durability = durability;
        _damage_chance_min = damage_chance_min;
        _damage_chance_max = damage_chance_max;
        _set_of_blocks = blocks;
    }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return nlohmann::json
     */
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