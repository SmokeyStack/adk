#ifndef BLOCK_H
#define BLOCK_H

#include <string>

#include "BlockProperty.h"
#include "json.hpp"

class Block {
   protected:
    int block_light_filter;
    nlohmann::json::object_t crafting;
    nlohmann::json::object_t explosion;
    nlohmann::json::object_t mining;
    std::string display_name;
    nlohmann::json::object_t flammable;
    double friction;
    int light_emission;
    std::string loot;
    std::string colour;
    std::vector<int> rotation;

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "blocks/"; };

    Block(){};
    Block(BlockProperty::Property property) {
        block_light_filter = property.block_light_filter;
        crafting = property.crafting;
        explosion = property.explosion;
        mining = property.mining;
        display_name = property.display_name;
        flammable = property.flammable;
        friction = property.friction;
        light_emission = property.light_emission;
        loot = property.loot;
        colour = property.colour;
        rotation = property.rotation;
    }

    virtual json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.50";
        j["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;
        j["minecraft:block"]["components"]["minecraft:unit_cube"] =
            json::object();

        if (block_light_filter != 15)
            j["minecraft:block"]["components"]["minecraft:light_dampening"] =
                block_light_filter;

        if (crafting != json::object_t({{"crafting_table", {"crafting_table"}},
                                        {"table_name", "Foo Bar"}}))
            j["minecraft:block"]["components"]["minecraft:crafting_table"] =
                crafting;
        if (explosion != json::object_t({{"explosion_resistance", 0}}))
            j["minecraft:block"]["components"]
             ["minecraft:destructible_by_explosion"] = explosion;

        if (mining != json::object_t({{"seconds_to_destory", 0.0}}))
            j["minecraft:block"]["components"]
             ["minecraft:destructible_by_mining"] = mining;

        if (display_name != "")
            j["minecraft:block"]["components"]["minecraft:display_name"] =
                display_name;

        if (flammable != json::object_t({{"catch_chance_modifier", 5},
                                         {"destroy_chance_modifier", 20}}))
            j["minecraft:block"]["components"]["minecraft:flammable"] =
                flammable;

        if (friction != 0.4)
            j["minecraft:block"]["components"]["minecraft:friction"] = friction;

        if (light_emission != 0)
            j["minecraft:block"]["components"]["minecraft:light_emission"] =
                light_emission;

        if (loot != "")
            j["minecraft:block"]["components"]["minecraft:loot"] = loot;

        if (colour != "")
            j["minecraft:block"]["components"]["minecraft:map_color"] = colour;

        if (rotation != std::vector<int>{0, 0, 0})
            j["minecraft:block"]["components"]["minecraft:rotation"] = rotation;

        return j;
    }
};

#endif