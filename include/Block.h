#ifndef BLOCK_H
#define BLOCK_H

#include <string>

#include "BlockProperty.h"
#include "json.hpp"

class Block {
    using json = nlohmann::json;
    json j;

   private:
    int block_light_filter;
    std::string breathability;
    double friction;
    int light_emission;
    std::vector<int> rotation;

   public:
    std::string getType() { return "blocks/"; };

    Block(BlockProperty::Property property) {
        block_light_filter = property.block_light_filter;
        breathability = property.breathability;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
    }

    json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.30";
        j["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;
        j["minecraft:block"]["components"]["minecraft:unit_cube"] =
            nlohmann::json::object();

        if (block_light_filter != 15)
            j["minecraft:block"]["components"]["minecraft:block_light_filter"] =
                block_light_filter;

        if (breathability != "solid")
            j["minecraft:block"]["components"]["minecraft:breathability"] =
                breathability;

        if (friction != 0.4)
            j["minecraft:block"]["components"]["minecraft:friction"] = friction;

        if (light_emission != 0)
            j["minecraft:block"]["components"]["minecraft:light_emission"] =
                light_emission;

        if (rotation != std::vector<int>{0, 0, 0})
            j["minecraft:block"]["components"]["minecraft:rotation"] = rotation;

        return j;
    }
};

#endif