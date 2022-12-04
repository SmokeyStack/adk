#ifndef BLOCK_H
#define BLOCK_H

#include <string>

#include "BlockProperty.h"
#include "json.hpp"

class Block {
   protected:
    int block_light_filter;
    double friction;
    int light_emission;
    std::vector<int> rotation;

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "blocks/"; };

    Block(){};
    Block(BlockProperty::Property property) {
        block_light_filter = property.block_light_filter;
        friction = property.friction;
        light_emission = property.light_emission;
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