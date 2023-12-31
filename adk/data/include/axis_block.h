#ifndef AXISBLOCK_h
#define AXISBLOCK_H

#include "block.h"
#include "block_property.h"
#include "json.hpp"

/**
 * @brief Represents a Rotatable Block
 *
 */
class AxisBlock : public Block {
   public:
    AxisBlock() {}
    /**
     * @brief Construct a new Axis Block object
     *
     * @param property BlockProperty
     */
    AxisBlock(BlockProperty property) { _internal = property; }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return json
     */
    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);

        // Properties
        j["minecraft:block"]["description"]["states"]
         [mod_id + ":rotation"] = json::array({0, 1, 2});

        // Components
        j["minecraft:block"]["components"]["minecraft:on_player_placing"]
         ["event"] = mod_id + ":set_rotation";
        j["minecraft:block"]["events"][mod_id + ":set_direction"]
         ["set_block_state"][mod_id + ":cardinal"] =
             "math.floor(q.block_face/2.0)";

        // Permutations
        json::object_t temp = {
            {"condition", "q.block_state('" + mod_id + ":rotation') == 0"}};
        temp["components"].update(helper.rotation(std::vector<int>(0, 0, 0)));
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {
            {"condition", "q.block_state('" + mod_id + ":rotation') == 1"}};
        temp["components"].update(helper.rotation(std::vector<int>(90, 0, 0)));
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {
            {"condition", "q.block_state('" + mod_id + ":rotation') == 2"}};
        temp["components"].update(helper.rotation(std::vector<int>(0, 0, 90)));
        j["minecraft:block"]["permutations"].push_back(temp);

        return j;
    }
};

#endif