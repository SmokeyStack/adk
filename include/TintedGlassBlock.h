#ifndef TINTEDGLASSBLOCK_H
#define TINTEDGLASSBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class TintedGlassBlock : public Block {
   public:
    TintedGlassBlock(BlockProperty::Property property) {
        block_light_filter = 15;
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