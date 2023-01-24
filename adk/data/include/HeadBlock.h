#ifndef HEADBLOCK_H
#define HEADBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class Head : public Block {
   public:
    Head(BlockProperty::Property property) {
        block_light_filter = property.block_light_filter;
        friction = property.friction;
        light_emission = property.light_emission;
        rotation = property.rotation;
    }

    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);
        j["minecraft:block"]["description"]["properties"][mod_id +
                                                          ":rotation"] =
            json::array({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
        j["minecraft:block"]["components"]["minecraft:on_player_placing"]
         ["event"] = mod_id + ":set_rotation";
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
             ": (q.body_y_rotation > -168.75 && q.body_y_rotation < -146.25) ? "
             "9 : (q.body_y_rotation > -146.25 && q.body_y_rotation < -123.75) "
             "? 10 : (q.body_y_rotation > -123.75 && q.body_y_rotation < "
             "-101.25) ? 11 : (q.body_y_rotation > -101.25 && "
             "q.body_y_rotation < -78.25) ? 12 : (q.body_y_rotation > -78.25 "
             "&& q.body_y_rotation < -56.25) ? 13 : (q.body_y_rotation > "
             "-56.25 && q.body_y_rotation < -33.75) ? 14 : (q.body_y_rotation "
             "> -33.75 && q.body_y_rotation < -11.25) ? 15";
        j["minecraft:block"]["permutations"] = {
            {{"components", {{"minecraft:geometry", "geometry.head_n"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 0"}},
            {{"components", {{"minecraft:geometry", "geometry.head_nne"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 1"}},
            {{"components", {{"minecraft:geometry", "geometry.head_ne"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 2"}},
            {{"components", {{"minecraft:geometry", "geometry.head_ene"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 3"}},
            {{"components", {{"minecraft:geometry", "geometry.head_e"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 4"}},
            {{"components", {{"minecraft:geometry", "geometry.head_ese"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 5"}},
            {{"components", {{"minecraft:geometry", "geometry.head_se"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 6"}},
            {{"components", {{"minecraft:geometry", "geometry.head_sse"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 7"}},
            {{"components", {{"minecraft:geometry", "geometry.head_s"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 8"}},
            {{"components", {{"minecraft:geometry", "geometry.head_ssw"}}},
             {"condition", "q.block_property('" + mod_id + ":rotation') == 9"}},
            {{"components", {{"minecraft:geometry", "geometry.head_sw"}}},
             {"condition",
              "q.block_property('" + mod_id + ":rotation') == 10"}},
            {{"components", {{"minecraft:geometry", "geometry.head_wsw"}}},
             {"condition",
              "q.block_property('" + mod_id + ":rotation') == 11"}},
            {{"components", {{"minecraft:geometry", "geometry.head_w"}}},
             {"condition",
              "q.block_property('" + mod_id + ":rotation') == 12"}},
            {{"components", {{"minecraft:geometry", "geometry.head_wnw"}}},
             {"condition",
              "q.block_property('" + mod_id + ":rotation') == 13"}},
            {{"components", {{"minecraft:geometry", "geometry.head_nw"}}},
             {"condition",
              "q.block_property('" + mod_id + ":rotation') == 14"}},
            {{"components", {{"minecraft:geometry", "geometry.head_nnw"}}},
             {"condition",
              "q.block_property('" + mod_id + ":rotation') == 15"}}};
        j["minecraft:block"]["components"].erase("minecraft:unit_cube");

        return j;
    };
};

#endif