#ifndef HEADBLOCK_H
#define HEADBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

/**
 * @brief Represents a Skull Block
 *
 */
class HeadBlock : public Block {
   public:
    HeadBlock() {}
    /**
     * @brief Construct a new Head Block object
     *
     * @param property BlockProperty
     */
    HeadBlock(BlockProperty property) { _internal = property; }

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
        j["minecraft:block"]["description"]["states"][mod_id + ":rotation"]
         ["values"] = {{"min", 0}, {"max", 15}};

        j["minecraft:block"]["description"]["traits"]
         ["minecraft:placement_position"] = {
             {"enabled_states", {"minecraft:block_face"}}};

        // Components
        if (j["minecraft:block"]["components"].contains(
                "minecraft:collision_box"))
            j["minecraft:block"]["components"].erase("minecraft:collision_box");

        j["minecraft:block"]["components"].update(
            helper.collision(std::make_pair(std::vector<int>{-4, 0, -4},
                                            std::vector<int>{8, 8, 8}),
                             id));

        j["minecraft:block"]["components"].update(
            helper.selection(std::make_pair(std::vector<int>{-4, 0, -4},
                                            std::vector<int>{8, 8, 8}),
                             id));

        j["minecraft:block"]["components"]["minecraft:on_player_placing"]
         ["event"] = mod_id + ":set_rotation";
        j["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] =
            "geometry.head";
        j["minecraft:block"]["components"]["minecraft:geometry"]
         ["bone_visibility"] = {
             {"0", "(q.block_state('" + mod_id +
                       ":rotation') == 0 || "
                       "q.block_state('" +
                       mod_id +
                       ":rotation') == 4 || "
                       "q.block_state('" +
                       mod_id +
                       ":rotation') == 8 || "
                       "q.block_state('" +
                       mod_id +
                       ":rotation') == 12) && "
                       "q.block_state('minecraft:block_face') == 'up'"},
             {"22_5", "q.block_state('" + mod_id +
                          ":rotation') == 1 || "
                          "q.block_state('" +
                          mod_id +
                          ":rotation') == 5 || "
                          "q.block_state('" +
                          mod_id +
                          ":rotation') == 9 || "
                          "q.block_state('" +
                          mod_id + ":rotation') == 13"},
             {"45", "q.block_state('" + mod_id +
                        ":rotation') == 2 || "
                        "q.block_state('" +
                        mod_id +
                        ":rotation') == 6 || "
                        "q.block_state('" +
                        mod_id +
                        ":rotation') == 10 || "
                        "q.block_state('" +
                        mod_id + ":rotation') == 14"},
             {"67_5", "q.block_state('" + mod_id +
                          ":rotation') == 3 || "
                          "q.block_state('" +
                          mod_id +
                          ":rotation') == 7 || "
                          "q.block_state('" +
                          mod_id +
                          ":rotation') == 11 || "
                          "q.block_state('" +
                          mod_id + ":rotation') == 15"},
             {"wall", "q.block_state('minecraft:block_face') != 'up'"}};

        // Events
        j["minecraft:block"]["events"][mod_id + ":set_rotation"]
         ["set_block_state"][mod_id + ":rotation"] =
             "q.block_face == 1 ? { t.positive_head_rot = q.head_y_rotation(0) "
             "+ 360 * (q.head_y_rotation(0) != "
             "Math.abs(q.head_y_rotation(0))); t.block_rotation = "
             "Math.round(t.positive_head_rot / 22.5); return t.block_rotation "
             "!= 16 ? t.block_rotation; };";

        // Permutations
        json::object_t temp = {
            {"condition",
             "q.block_state('" + mod_id +
                 ":rotation') >= 4 || "
                 "q.block_state('minecraft:block_face') == 'east'"}};
        temp["components"].update(
            helper.rotation(std::vector<int>{0, -90, 0}, id));
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {{"condition",
                 "q.block_state('" + mod_id +
                     ":rotation') >= 8 || "
                     "q.block_state('minecraft:block_face') == 'south'"}};
        temp["components"].update(
            helper.rotation(std::vector<int>{0, 180, 0}, id));
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {{"condition",
                 "q.block_state('" + mod_id +
                     ":rotation') >= 12 || "
                     "q.block_state('minecraft:block_face') == 'west'"}};
        temp["components"].update(
            helper.rotation(std::vector<int>{0, 90, 0}, id));
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {{"condition", "q.block_state('minecraft:block_face') != 'up'"}};
        temp["components"].update(
            helper.selection(std::make_pair(std::vector<int>{-4, 4, 0},
                                            std::vector<int>{8, 8, 8}),
                             id));
        temp["components"].update(
            helper.collision(std::make_pair(std::vector<int>{-4, 4, 0},
                                            std::vector<int>{8, 8, 8}),
                             id));
        j["minecraft:block"]["permutations"].push_back(temp);

        return j;
    };
};

#endif