#ifndef BLOCK_H
#define BLOCK_H

#include <string>

#include "BlockProperty.h"
#include "json.hpp"

class Block {
   protected:
    int _block_light_filter;
    nlohmann::json::object_t _crafting;
    nlohmann::json::object_t _explosion;
    nlohmann::json::object_t _mining;
    std::string _display_name;
    nlohmann::json::object_t _flammable;
    double _friction;
    int _light_emission;
    std::string _loot;
    std::string _color;
    std::vector<int> _rotation;

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "blocks/"; };

    Block(){};
    /// @brief Represents a block
    /// @param property A BlockProperty object
    Block(BlockProperty::Property property) {
        _block_light_filter = property.block_light_filter;
        _crafting = property.crafting;
        _explosion = property.explosion;
        _mining = property.mining;
        _display_name = property.display_name;
        _flammable = property.flammable;
        _friction = property.friction;
        _light_emission = property.light_emission;
        _loot = property.loot;
        _color = property.colour;
        _rotation = property.rotation;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the block
    /// @return json object
    virtual json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.50";
        j["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;
        j["minecraft:block"]["components"]["minecraft:unit_cube"] =
            json::object();

        if (_block_light_filter != 15)
            j["minecraft:block"]["components"]["minecraft:light_dampening"] =
                _block_light_filter;

        if (_crafting != json::object_t({{"crafting_table", {"crafting_table"}},
                                         {"table_name", "Foo Bar"}}))
            j["minecraft:block"]["components"]["minecraft:crafting_table"] =
                _crafting;
        if (_explosion != json::object_t({{"explosion_resistance", 0}}))
            j["minecraft:block"]["components"]
             ["minecraft:destructible_by_explosion"] = _explosion;

        if (_mining != json::object_t({{"seconds_to_destory", 0.0}}))
            j["minecraft:block"]["components"]
             ["minecraft:destructible_by_mining"] = _mining;

        if (_display_name != "")
            j["minecraft:block"]["components"]["minecraft:display_name"] =
                _display_name;

        if (_flammable != json::object_t({{"catch_chance_modifier", 5},
                                          {"destroy_chance_modifier", 20}}))
            j["minecraft:block"]["components"]["minecraft:flammable"] =
                _flammable;

        if (_friction != 0.4)
            j["minecraft:block"]["components"]["minecraft:friction"] =
                _friction;

        if (_light_emission != 0)
            j["minecraft:block"]["components"]["minecraft:light_emission"] =
                _light_emission;

        if (_loot != "")
            j["minecraft:block"]["components"]["minecraft:loot"] = _loot;

        if (_color != "")
            j["minecraft:block"]["components"]["minecraft:map_color"] = _color;

        if (_rotation != std::vector<int>{0, 0, 0})
            j["minecraft:block"]["components"]["minecraft:rotation"] =
                _rotation;

        return j;
    }
};

#endif