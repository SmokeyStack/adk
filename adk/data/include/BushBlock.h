#ifndef BUSHBLOCK_H
#define BUSHBLOCK_H

#include <iostream>

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class BushBlock : public Block {
   public:
    BushBlock(){};
    /// @brief Represents a bush block
    /// @param property A BlockProperty object
    BushBlock(BlockProperty::Property property) {
        block_light_filter = property.block_light_filter;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the block
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);
        j["minecraft:block"]["components"]["minecraft:placement_filter"]
         ["conditions"] = {{{"allowed_faces", json::array({"up"})},
                            {"block_filter",
                             json::array({{{"tags", "q.any_tag('dirt')"}},
                                          {{"tags", "q.any_tag('grass')"}}})}}};

        return j;
    }
};

#endif