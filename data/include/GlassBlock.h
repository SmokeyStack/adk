#ifndef GLASSBLOCK_H
#define GLASSBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class GlassBlock : public Block {
   public:
    /// @brief Represents a glass block
    /// @param property A BlockProperty object
    GlassBlock(BlockProperty::Property property) {
        block_light_filter = 0;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
    };

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the block
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);

        return j;
    }
};

#endif