#ifndef SLABBLOCK_H
#define SLABBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

/**
 * @brief Represents a Slab Block
 *
 */
class SlabBlock : public Block {
   public:
    SlabBlock() {}
    /**
     * @brief Construct a new Slab Block object
     *
     * @param property BlockProperty
     */
    SlabBlock(BlockProperty property) { _internal = property; }

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
        j["minecraft:block"]["description"]["properties"]
         [mod_id + ":is_double"] = json::array({false, true});
        j["minecraft:block"]["description"]["traits"]
         ["minecraft:placement_position"] = {
             {"enabled_states", {"minecraft:vertical_half"}}};

        // Components
        j["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] =
            "geometry.slab";
        j["minecraft:block"]["components"]["minecraft:geometry"]
         ["bone_visibility"] = {
             {"upper",
              "q.block_property('minecraft:vertical_half') == 'top' || "
              "q.block_property('" +
                  mod_id + ":is_double')"},
             {"lower",
              "q.block_property('minecraft:vertical_half') == 'bottom' || "
              "q.block_property('" +
                  mod_id + ":is_double')"}};

        // Events
        j["minecraft:block"]["events"][mod_id + ":become_double"] = {
            {"set_block_property", {{mod_id + ":is_double", true}}},
            {"decrement_stack", json::object()}};
        j["minecraft:block"]["events"][mod_id + ":drop_double"] = {
            {"spawn_loot", json::object()}};

        // Permutations
        json::object_t temp = {
            {"condition",
             "q.block_property('minecraft:vertical_half') == 'top' && "
             "!q.block_property('" +
                 mod_id + ":is_double')"}};
        temp["components"].update(
            helper.collision(std::make_pair(std::vector<int>{-8, 8, -8},
                                            std::vector<int>{16, 8, 16}),
                             id));
        temp["components"].update(
            helper.selection(std::make_pair(std::vector<int>{-8, 8, -8},
                                            std::vector<int>{16, 8, 16}),
                             id));
        temp["components"].update({{"minecraft:on_interact",
                                    {{"event", "" + mod_id + ":become_double"},
                                     {"condition",
                                      "q.block_face == 0 && "
                                      "q.is_item_name_any('slot.weapon."
                                      "mainhand','" +
                                          mod_id + ":" + id + "')"}}}});
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {{"condition",
                 "q.block_property('minecraft:vertical_half') == 'bottom' && "
                 "!q.block_property('" +
                     mod_id + ":is_double')"}};
        temp["components"].update(
            helper.collision(std::make_pair(std::vector<int>{-8, 0, -8},
                                            std::vector<int>{16, 8, 16}),
                             id));
        temp["components"].update(
            helper.selection(std::make_pair(std::vector<int>{-8, 0, -8},
                                            std::vector<int>{16, 8, 16}),
                             id));
        temp["components"].update({{"minecraft:on_interact",
                                    {{"event", "" + mod_id + ":become_double"},
                                     {"condition",
                                      "q.block_face == 1 && "
                                      "q.is_item_name_any('slot.weapon."
                                      "mainhand','" +
                                          mod_id + ":" + id + "')"}}}});
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {{"condition", "q.block_property('" + mod_id + ":is_double')"}};
        temp["components"].update(
            {{"minecraft:on_player_destroyed",
              {{"event", "" + mod_id + ":drop_double"}}}});
        j["minecraft:block"]["permutations"].push_back(temp);
        return j;
    };
};

#endif