#ifndef SLABBLOCK_H
#define SLABBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class SlabBlock : public Block {
   public:
    SlabBlock() {}
    /// @brief
    /// @param property
    SlabBlock(BlockProperty::Property property) {
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
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the block
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);

        // Properties
        j["minecraft:block"]["description"]["properties"][mod_id + ":type"] =
            json::array({"lower", "upper", "double"});

        // Components
        j["minecraft:block"]["components"]["minecraft:on_player_placing"]
         ["event"] = mod_id + ":set_placement";
        j["minecraft:block"]["components"]["minecraft:part_visibility"]
         ["conditions"]["lower"] = "q.block_property('" + mod_id +
                                   ":type') == 'lower' || q.block_property('" +
                                   mod_id + ":type') == 'double'";
        j["minecraft:block"]["components"]["minecraft:part_visibility"]
         ["conditions"]["upper"] = "q.block_property('" + mod_id +
                                   ":type') == 'upper' || q.block_property('" +
                                   mod_id + ":type') == 'double'";
        j["minecraft:block"]["components"]["minecraft:on_interact"]
         ["condition"] = "q.is_item_name_any('slot.weapon.mainhand', '" +
                         mod_id + ":" + id +
                         "') && (q.block_face == 0 || q.block_face == 1) && "
                         "q.block_property('" +
                         mod_id + ":type') != 'double'";
        j["minecraft:block"]["components"]["minecraft:on_interact"]["event"] =
            mod_id + ":combine";
        j["minecraft:block"]["components"]["minecraft:geometry"] =
            "geometry.slab";

        // Events
        j["minecraft:block"]["events"][mod_id + ":set_placement"]["sequence"] =
            {{{"condition", "q.target_x_rotation > 0"},
              {"set_block_property", {{mod_id + ":type", "'lower'"}}}},
             {{"condition", "q.target_x_rotation <= 0"},
              {"set_block_property", {{mod_id + ":type", "'upper'"}}}}};
        j["minecraft:block"]["events"][mod_id + ":combine"]["decrement_stack"] =
            json::object();
        j["minecraft:block"]["events"][mod_id + ":combine"]
         ["set_block_property"][mod_id + ":type"] = "'double'";

        // Permutations
        j["minecraft:block"]["permutations"].push_back(
            {{"components",
              {
                  {"minecraft:collision_box",
                   {{"origin", {-8, 0, -8}}, {"size", {16, 8, 16}}}},
                  {"minecraft:selection_box",
                   {{"origin", {-8, 0, -8}}, {"size", {16, 8, 16}}}},
              }},
             {"condition",
              "q.block_property('" + mod_id + ":type') == 'lower'"}});
        j["minecraft:block"]["permutations"].push_back(
            {{"components",
              {
                  {"minecraft:collision_box",
                   {{"origin", {-8, 8, -8}}, {"size", {16, 8, 16}}}},
                  {"minecraft:selection_box",
                   {{"origin", {-8, 8, -8}}, {"size", {16, 8, 16}}}},
              }},
             {"condition",
              "q.block_property('" + mod_id + ":type') == 'upper'"}});
        j["minecraft:block"]["permutations"].push_back(
            {{"components",
              {
                  {"minecraft:collision_box",
                   {{"origin", {-8, 0, -8}}, {"size", {16, 16, 16}}}},
                  {"minecraft:selection_box",
                   {{"origin", {-8, 0, -8}}, {"size", {16, 16, 16}}}},
              }},
             {"condition",
              "!q.block_property('" + mod_id + ":type') == 'double'"}});

        j["minecraft:block"]["components"].erase("minecraft:unit_cube");

        return j;
    };
};

#endif