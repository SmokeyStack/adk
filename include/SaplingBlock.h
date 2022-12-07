#ifndef SAPLINGBLOCK_H
#define SAPLINGBLOCK_H

#include <iostream>
#include <vector>

#include "BlockProperty.h"
#include "BushBlock.h"
#include "json.hpp"

class SaplingBlock : public BushBlock {
   protected:
    int _number_of_properties;

   public:
    SaplingBlock(BlockProperty::Property property, int number_of_properties) {
        block_light_filter = property.block_light_filter;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
        _number_of_properties = number_of_properties;
    }

    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);
        j["minecraft:block"]["components"]["minecraft:random_ticking"]
         ["on_tick"]["event"] = mod_id + ":random_tick";

        std::vector<int> property_array;

        for (int a = 0; a < _number_of_properties; a++) {
            property_array.push_back(a);
        }

        j["minecraft:block"]["description"]["properties"]
         [mod_id + ":growth_stage"] = property_array;

        j["minecraft:block"]["events"][mod_id + ":random_tick"]
         ["set_block_property"][mod_id + ":growth_stage"] =
             "(q.block_property('" + mod_id + ":growth_stage') < " +
             std::to_string(_number_of_properties - 1) +
             ") ? "
             "q.block_property('" +
             mod_id + ":growth_stage') + 1 : " +
             std::to_string(_number_of_properties - 1);

        return j;
    }
};

#endif