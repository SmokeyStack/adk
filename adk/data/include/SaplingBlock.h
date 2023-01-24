#ifndef SAPLINGBLOCK_H
#define SAPLINGBLOCK_H

#include <vector>

#include "BlockProperty.h"
#include "BushBlock.h"
#include "json.hpp"

class SaplingBlock : public BushBlock {
   protected:
    int _number_of_properties;
    std::string _structure;
    std::string _particle = "minecraft:crop_growth_emitter";

   public:
    /// @brief Represents a sapling block
    /// @param property A BlockProperty object
    /// @param number_of_properties How many stages the sapling has
    /// @param structure The "tree" to load. Temporary solution until Bedrock
    /// has place feature command
    SaplingBlock(BlockProperty::Property property, int number_of_properties,
                 std::string structure) {
        block_light_filter = property.block_light_filter;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
        _number_of_properties = number_of_properties;
        _structure = structure;
    }

    /// @brief Represents a sapling block
    /// @param property A BlockProperty object
    /// @param number_of_properties How many stages the sapling has
    /// @param structure The "tree" to load. Temporary solution until Bedrock
    /// has place feature command
    /// @param particle The particle to play after being bonemealed
    SaplingBlock(BlockProperty::Property property, int number_of_properties,
                 std::string structure, std::string particle) {
        block_light_filter = property.block_light_filter;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
        _number_of_properties = number_of_properties;
        _structure = structure;
        _particle = particle;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the block
    /// @return json object
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

        j["minecraft:block"]["events"][mod_id + ":final_growth"]["run_command"]
         ["command"] = {"structure load " + _structure + " ~-2~~-2"};

        j["minecraft:block"]["permutations"] = {
            {{"components",
              {{"minecraft:random_ticking",
                {{"on_tick", {{"event", mod_id + ":final_growth"}}}}}}},
             {"condition", "q.block_property('" + mod_id +
                               ":growth_stage') == " +
                               std::to_string(_number_of_properties - 1)}},
        };

        return j;
    }
};

#endif