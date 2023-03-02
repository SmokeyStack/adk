#ifndef AXISBLOCK_h
#define AXISBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
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
    AxisBlock(BlockProperty property) {
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
        j["minecraft:block"]["description"]["properties"]
         [mod_id + ":cardinal"] = json::array({0, 1, 2});
        j["minecraft:block"]["components"]["minecraft:on_player_placing"]
         ["event"] = mod_id + ":set_direction";
        j["minecraft:block"]["events"][mod_id + ":set_direction"]
         ["set_block_property"][mod_id + ":cardinal"] =
             "math.floor(q.block_face/2.0)";
        j["minecraft:block"]["permutations"] = {
            {{"components",
              {{"minecraft:rotation", std::vector<int>{0, 0, 0}}}},
             {"condition", "q.block_property('fk:cardinal') == 0"}},
            {{"components",
              {{"minecraft:rotation", std::vector<int>{90, 0, 0}}}},
             {"condition", "q.block_property('fk:cardinal') == 1"}},
            {{"components",
              {{"minecraft:rotation", std::vector<int>{0, 0, 90}}}},
             {"condition", "q.block_property('fk:cardinal') == 2"}}};

        return j;
    }
};

#endif