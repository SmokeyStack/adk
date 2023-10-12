#ifndef CANDLEBLOCK_H
#define CANDLEBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

/**
 * @brief Represents a Candle Block
 *
 */
class CandleBlock : public Block {
   public:
    CandleBlock() {}
    /**
     * @brief Construct a new Candle Block object
     *
     * @param property BlockProperty
     */
    CandleBlock(BlockProperty property) { _internal = property; }

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
        j["minecraft:block"]["description"]["states"][mod_id + ":count"]
         ["values"] = {{"min", 1}, {"max", 4}};

        // Components
        if (j["minecraft:block"]["components"].contains(
                "minecraft:collision_box"))
            j["minecraft:block"]["components"].erase("minecraft:collision_box");

        j["minecraft:block"]["components"].update(
            helper.collision(std::make_pair(std::vector<int>{-1, 0, -1},
                                            std::vector<int>{2, 6, 2}),
                             id));

        j["minecraft:block"]["components"].update(
            helper.selection(std::make_pair(std::vector<int>{-1, 0, -1},
                                            std::vector<int>{2, 6, 2}),
                             id));

        j["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] =
            "geometry.candle";
        j["minecraft:block"]["components"]["minecraft:geometry"]
         ["bone_visibility"] = {
             {"one", "q.block_state('" + mod_id + ":count') == 1"},
             {"two", "q.block_state('" + mod_id + ":count') == 2"},
             {"three", "q.block_state('" + mod_id + ":count') == 3"},
             {"four", "q.block_state('" + mod_id + ":count') == 4"}};
        j["minecraft:block"]["components"]["minecraft:on_interact"]
         ["condition"] = "q.is_item_name_any('slot.weapon.mainhand', '" + id +
                         "') && q.block_state('" + mod_id + ":count') != 4";
        j["minecraft:block"]["components"]["minecraft:on_interact"]["event"] =
            mod_id + ":add_candle";

        // Events
        j["minecraft:block"]["events"][mod_id + ":add_candle"]
         ["set_block_state"][mod_id + ":count"] =
             "(q.block_state('" + mod_id +
             ":count') < 4) ? q.block_state('" + mod_id + ":count') + 1 : 4";
        j["minecraft:block"]["events"][mod_id + ":add_candle"]
         ["decrement_stack"] = json::object();

        // Permutations
        json::object_t temp = {
            {"condition", "q.block_state('" + mod_id + ":count') == 2"}};
        temp["components"].update(
            helper.collision(std::make_pair(std::vector<int>{-3, 0, -1},
                                            std::vector<int>{5, 6, 3}),
                             id));
        temp["components"].update(
            helper.selection(std::make_pair(std::vector<int>{-3, 0, -1},
                                            std::vector<int>{5, 6, 3}),
                             id));
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {{"condition", "q.block_state('" + mod_id + ":count') == 3"}};
        temp["components"].update(
            helper.collision(std::make_pair(std::vector<int>{-2, 0, -2},
                                            std::vector<int>{5, 6, 5}),
                             id));
        temp["components"].update(
            helper.selection(std::make_pair(std::vector<int>{-2, 0, -2},
                                            std::vector<int>{5, 6, 5}),
                             id));
        j["minecraft:block"]["permutations"].push_back(temp);
        temp = {{"condition", "q.block_state('" + mod_id + ":count') == 4"}};
        temp["components"].update(
            helper.collision(std::make_pair(std::vector<int>{-3, 0, -3},
                                            std::vector<int>{6, 6, 5}),
                             id));
        temp["components"].update(
            helper.selection(std::make_pair(std::vector<int>{-3, 0, -3},
                                            std::vector<int>{6, 6, 5}),
                             id));
        j["minecraft:block"]["permutations"].push_back(temp);

        return j;
    };
};

#endif