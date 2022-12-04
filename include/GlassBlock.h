#ifndef GLASSBLOCK_H
#define GLASSBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class GlassBlock : public Block {
   public:
    GlassBlock(BlockProperty::Property property) {
        block_light_filter = 0;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
    };

    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);

        return j;
    }
};

#endif