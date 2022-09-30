#ifndef AXISBLOCK_h
#define AXISBLOCK_H

#include <iostream>

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class AxisBlock : public Block {
   public:
    AxisBlock(BlockProperty::Property property) {
        block_light_filter = property.block_light_filter;
        breathability = property.breathability;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
    }

    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);
        j["minecraft:block"]["description"]["properties"]
         [mod_id + ":cardinal"] = json::array({0, 1, 2});
        j["minecraft:block"]["components"]["minecraft:on_player_placing"]
         ["event"] = mod_id + ":set_direction";
        j["minecraft:block"]["events"][mod_id + ":set_direction"]
         ["set_block_property"][mod_id + ":cardinal"] =
             "math.floor(q.block_face/2.0)";
        j["minecraft:block"]["permutations"] = {
            {{"components",
              {{"minecraft:rotation", std::vector<int>{0, 0, 0}}}},
             {"condition", "q.block_property('fk:cardinal') == 0"}},
            {{"components",
              {{"minecraft:rotation", std::vector<int>{90, 0, 0}}}},
             {"condition", "q.block_property('fk:cardinal') == 1"}},
            {{"components",
              {{"minecraft:rotation", std::vector<int>{0, 0, 90}}}},
             {"condition", "q.block_property('fk:cardinal') == 2"}}};

        return j;
    }
};

#endif