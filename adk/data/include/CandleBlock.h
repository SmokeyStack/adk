#ifndef CANDLEBLOCK_H
#define CANDLEBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class CandleBlock : public Block {
   public:
    CandleBlock() {}
    /// @brief Represents a candle block
    /// @param property A BlockProperty object
    CandleBlock(BlockProperty::Property property) {
        _block_light_filter = property.block_light_filter;
        _crafting = property.crafting;
        _explosion = property.explosion;
        _mining = property.mining;
        _display_name = property.display_name;
        _flammable = property.flammable;
        _friction = property.friction;
        _light_emission = property.light_emission;
        _loot = property.loot;
        _color = property.color;
        _rotation = property.rotation;
        _does_collide = property.does_collide;
        _collision = property.collision;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the block
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);

        // Properties
        j["minecraft:block"]["description"]["properties"][mod_id + ":count"] =
            json::array({1, 2, 3, 4});

        // Components
        j["minecraft:block"]["components"].erase("minecraft:collision_box");

        j["minecraft:block"]["components"]["minecraft:collision_box"]
         ["origin"] = {-1, 0, -1};
        j["minecraft:block"]["components"]["minecraft:collision_box"]["size"] =
            {2, 6, 2};
        j["minecraft:block"]["components"]["minecraft:selection_box"]
         ["origin"] = {-1, 0, -1};
        j["minecraft:block"]["components"]["minecraft:selection_box"]["size"] =
            {2, 6, 2};
        j["minecraft:block"]["components"]["minecraft:geometry"] =
            "geometry.candle_one";
        j["minecraft:block"]["components"]["minecraft:on_interact"]
         ["condition"] = "q.get_equipped_item_name == '" + id +
                         "' && q.block_property('" + mod_id + ":count') != 4";
        j["minecraft:block"]["components"]["minecraft:on_interact"]["event"] =
            mod_id + ":add_candle";

        // Events
        j["minecraft:block"]["events"][mod_id + ":add_candle"]
         ["set_block_property"][mod_id + ":count"] =
             "(q.block_property('" + mod_id +
             ":count') < 4) ? q.block_property('" + mod_id + ":count') + 1 : 4";
        j["minecraft:block"]["events"][mod_id + ":add_candle"]
         ["decrement_stack"] = json::object();

        // Permutations
        j["minecraft:block"]["permutations"].push_back(
            {{"components",
              {{"minecraft:collision_box",
                {{"origin", {-3, 0, -1}}, {"size", {5, 6, 3}}}},
               {"minecraft:selection_box",
                {{"origin", {-3, 0, -1}}, {"size", {5, 6, 3}}}},
               {"minecraft:geometry", "geometry.candle_two"}}},
             {"condition", "q.block_property('" + mod_id + ":count') == 2"}});
        j["minecraft:block"]["permutations"].push_back(
            {{"components",
              {{"minecraft:collision_box",
                {{"origin", {-2, 0, -2}}, {"size", {5, 6, 5}}}},
               {"minecraft:selection_box",
                {{"origin", {-2, 0, -2}}, {"size", {5, 6, 5}}}},
               {"minecraft:geometry", "geometry.candle_three"}}},
             {"condition", "q.block_property('" + mod_id + ":count') == 3"}});
        j["minecraft:block"]["permutations"].push_back(
            {{"components",
              {{"minecraft:collision_box",
                {{"origin", {-3, 0, -3}}, {"size", {6, 6, 5}}}},
               {"minecraft:selection_box",
                {{"origin", {-3, 0, -3}}, {"size", {6, 6, 5}}}},
               {"minecraft:geometry", "geometry.candle_four"}}},
             {"condition", "q.block_property('" + mod_id + ":count') == 4"}});

        j["minecraft:block"]["components"].erase("minecraft:unit_cube");

        return j;
    };
};

#endif