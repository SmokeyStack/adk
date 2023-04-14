#ifndef ITEM_H
#define ITEM_H

#include <spdlog/spdlog.h>

#include <string>

#include "ItemProperty.h"
#include "json.hpp"

/**
 * @brief Represents an Item
 *
 */
class Item {
   protected:
    std::string _display_name;
    std::string _icon;
    int _stack;
    std::string _block_placer;
    std::vector<std::string> _block_placer_placement;
    std::string _cooldown_category;
    float _cooldown_time;
    std::string _dye;
    std::string _entity_placer;
    std::vector<std::string> _entity_placer_placement;
    std::vector<std::string> _entity_placer_dispense;
    std::vector<double> _offset_main;
    std::vector<double> _offset_offhand;
    std::string _projectile_entity;

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
    Item(ItemProperty property) {
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
    }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return json
     */
    virtual json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.80";
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
             ["projectile_entity"] = _projectile_entity;

        return j;
    }
};

#endif