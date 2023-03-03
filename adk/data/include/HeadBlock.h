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
    HeadBlock(BlockProperty property) {
        _block_light_filter = property.getBlockLightFilter();
        _crafting = property.getCrafting();
        _explosion = property.getExplosion();
        _mining = property.getMining();
        _display_name = property.getName();
        _flammable = property.getFlamamble();
        _friction = property.getFriction();
        _light_emission = property.getLightEmission();
        _loot = property.getLoot();
        _color = property.getColor();
        _rotation = property.getRotation();
        _collision = property.getCollision();
        _selection = property.getSelection();
        _creative = property.getCreative();
    }

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
        j["minecraft:block"]["description"]["properties"][mod_id + ":is_wall"] =
            json::array({false, true});
        j["minecraft:block"]["description"]["properties"]
         [mod_id + ":placement"] = json::array({0, 1, 2, 3, 4, 5});
        j["minecraft:block"]["description"]["properties"][mod_id +
                                                          ":rotation"] =
            json::array({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});

        // Components
        j["minecraft:block"]["components"].erase("minecraft:collision_box");

        j["minecraft:block"]["components"]["minecraft:collision_box"]
         ["origin"] = {-4, 0, -4};
        j["minecraft:block"]["components"]["minecraft:collision_box"]["size"] =
            {8, 8, 8};
        j["minecraft:block"]["components"]["minecraft:selection_box"]
         ["origin"] = {-4, 0, -4};
        j["minecraft:block"]["components"]["minecraft:selection_box"]["size"] =
            {8, 8, 8};
        j["minecraft:block"]["components"]["minecraft:on_player_placing"]
         ["event"] = mod_id + ":set_rotation";
        j["minecraft:block"]["components"]["minecraft:geometry"] =
            "geometry.head_0";

        // Events
        j["minecraft:block"]["events"][mod_id + ":set_rotation"]
         ["set_block_property"][mod_id + ":is_wall"] =
             "(q.block_face > 1) ? true : false";
        j["minecraft:block"]["events"][mod_id + ":set_rotation"]
         ["set_block_property"][mod_id + ":placement"] = "q.block_face";
        j["minecraft:block"]["events"][mod_id + ":set_rotation"]
         ["set_block_property"][mod_id + ":rotation"] =
             "(q.body_y_rotation > -11.25 && q.body_y_rotation < 11.25) ? 0 : "
             "(q.body_y_rotation > 11.25 && q.body_y_rotation < 33.75) ? 1 : "
             "(q.body_y_rotation > 33.75 && q.body_y_rotation < 56.25) ? 2 : "
             "(q.body_y_rotation > 56.25 && q.body_y_rotation < 78.25) ? 3 : "
             "(q.body_y_rotation > 78.25 && q.body_y_rotation < 101.25) ? 4 : "
             "(q.body_y_rotation > 101.25 && q.body_y_rotation < 123.75) ? 5 : "
             "(q.body_y_rotation > 123.75 && q.body_y_rotation < 146.25) ? 6 : "
             "(q.body_y_rotation > 146.25 && q.body_y_rotation < 168.75) ? 7 : "
             "(q.body_y_rotation > 168.75 || q.body_y_rotation < -168.75) ? 8 "
             ": "
             "(q.body_y_rotation > -168.75 && q.body_y_rotation < -146.25) ? 9 "
             ": "
             "(q.body_y_rotation > -146.25 && q.body_y_rotation < -123.75) ? "
             "10 : "
             "(q.body_y_rotation > -123.75 && q.body_y_rotation < -101.25) ? "
             "11 : "
             "(q.body_y_rotation > -101.25 && q.body_y_rotation < -78.25) ? 12 "
             ": "
             "(q.body_y_rotation > -78.25 && q.body_y_rotation < -56.25) ? 13 "
             ": "
             "(q.body_y_rotation > -56.25 && q.body_y_rotation < -33.75) ? 14 "
             ": "
             "(q.body_y_rotation > -33.75 && q.body_y_rotation < -11.25) ? 15";

        // Permutations
        j["minecraft:block"]["permutations"].push_back(
            {{"components",
              {{"minecraft:collision_box",
                {{"origin", {-4, 4, 0}}, {"size", {8, 8, 8}}}},
               {"minecraft:selection_box",
                {{"origin", {-4, 4, 0}}, {"size", {8, 8, 8}}}},
               {"minecraft:geometry", "geometry.head_wall"}}},
             {"condition", "q.block_property('" + mod_id + ":is_wall')"}});

        for (int a = 0; a < 16; a += 4) {
            j["minecraft:block"]["permutations"].push_back(
                {{"components",
                  {{"minecraft:rotation", {0, (a / 4) * -90, 0}}}},
                 {"condition", "q.block_property('" + mod_id +
                                   ":rotation') == " + std::to_string(a) +
                                   " && (q.block_property('" + mod_id +
                                   ":placement') == 0 "
                                   "|| q.block_property('" +
                                   mod_id +
                                   ":placement') == "
                                   "1)"}});
            j["minecraft:block"]["permutations"].push_back(
                {{"components",
                  {{"minecraft:geometry", "geometry.head_22_5"},
                   {"minecraft:rotation", {0, (a / 4) * -90, 0}}}},
                 {"condition", "q.block_property('" + mod_id +
                                   ":rotation') == " + std::to_string(a + 1) +
                                   " && (q.block_property('" + mod_id +
                                   ":placement') == 0 "
                                   "|| q.block_property('" +
                                   mod_id +
                                   ":placement') == "
                                   "1)"}});
            j["minecraft:block"]["permutations"].push_back(
                {{"components",
                  {{"minecraft:geometry", "geometry.head_45"},
                   {"minecraft:rotation", {0, (a / 4) * -90, 0}}}},
                 {"condition", "q.block_property('" + mod_id +
                                   ":rotation') == " + std::to_string(a + 2) +
                                   " && (q.block_property('" + mod_id +
                                   ":placement') == 0 "
                                   "|| q.block_property('" +
                                   mod_id +
                                   ":placement') == "
                                   "1)"}});
            j["minecraft:block"]["permutations"].push_back(
                {{"components",
                  {{"minecraft:geometry", "geometry.head_67_5"},
                   {"minecraft:rotation", {0, (a / 4) * -90, 0}}}},
                 {"condition", "q.block_property('" + mod_id +
                                   ":rotation') == " + std::to_string(a + 3) +
                                   " && (q.block_property('" + mod_id +
                                   ":placement') == 0 "
                                   "|| q.block_property('" +
                                   mod_id +
                                   ":placement') == "
                                   "1)"}});
        }

        j["minecraft:block"]["components"].erase("minecraft:unit_cube");

        return j;
    };
};

#endif