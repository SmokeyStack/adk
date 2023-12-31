#ifndef ITEM_H
#define ITEM_H

#include <spdlog/spdlog.h>

#include <string>

//#include "ItemComponent.h"
#include "item_property.h"
#include "json.hpp"

/**
 * @brief Represents an Item
 *
 */
class Item {
   protected:
    ItemProperty _internal;
    //ItemComponent helper;

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "item"; };

    Item(){};
    /**
     * @brief Construct a new Item object
     *
     * @param property ItemProperty
     */
    Item(ItemProperty property) { _internal = property; }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return json
     */
    virtual json Generate(std::string mod_id, std::string id) {
        /*j["format_version"] = "1.20.40";
        j["minecraft:item"]["description"]["identifier"] = mod_id + ":" + id;

        if (!_display_name.empty())
            j["minecraft:item"]["components"]["minecraft:display_name"]
             ["value"] = _display_name;

        if (!_icon.empty())
            j["minecraft:item"]["components"]["minecraft:icon"]["texture"] =
                _icon;

        if (_stack != 64 && _stack != NULL)
            j["minecraft:item"]["components"]["minecraft:max_stack_size"] =
                _stack;

        if (!_block_placer.empty()) {
            j["minecraft:item"]["components"]["minecraft:block_placer"]
             ["block"] = _block_placer;

            if (!_block_placer_placement.empty())
                j["minecraft:item"]["components"]["minecraft:block_placer"]
                 ["use_on"] = _block_placer_placement;
        }

        if (!_cooldown_category.empty() && _cooldown_time != NULL) {
            j["minecraft:item"]["components"]["minecraft:cooldown"]
             ["category"] = _cooldown_category;
            j["minecraft:item"]["components"]["minecraft:cooldown"]
             ["duration"] = _cooldown_time;
        }

        if (!_dye.empty())
            j["minecraft:item"]["components"]["minecraft:dye_powder"]["color"] =
                _dye;

        if (!_entity_placer.empty()) {
            j["minecraft:item"]["components"]["minecraft:block_placer"]
             ["entity"] = _entity_placer;

            if (!_entity_placer_placement.empty())
                j["minecraft:item"]["components"]["minecraft:block_placer"]
                 ["use_on"] = _entity_placer_placement;

            if (!_entity_placer_dispense.empty())
                j["minecraft:item"]["components"]["minecraft:block_placer"]
                 ["dispense_on"] = _entity_placer_dispense;
        }

        if (!_offset_main.empty())
            j["minecraft:item"]["components"]["minecraft:render_offsets"]
             ["main_hand"] = _offset_main;

        if (!_offset_offhand.empty())
            j["minecraft:item"]["components"]["minecraft:render_offsets"]
             ["off_hand"] = _offset_offhand;

        if (!_projectile_entity.empty())
            j["minecraft:item"]["components"]["minecraft:projectile"]
             ["projectile_entity"] = _projectile_entity;*/

        return j;
    }
};

#endif