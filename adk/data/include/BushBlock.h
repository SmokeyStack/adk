#ifndef BUSHBLOCK_H
#define BUSHBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

class BushBlock : public Block {
   public:
    BushBlock(){};
    /// @brief Represents a bush block
    /// @param property A BlockProperty object
    BushBlock(BlockProperty::Property property) {
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
        _is_selectable = property.is_selectable;
        _selection = property.selection;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the block
    /// @return json object
    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);
        j["minecraft:block"]["components"]["minecraft:placement_filter"]
         ["conditions"] = {{{"allowed_faces", json::array({"up"})},
                            {"block_filter",
                             json::array({{{"tags", "q.any_tag('dirt')"}},
                                          {{"tags", "q.any_tag('grass')"}}})}}};

        return j;
    }
};

#endif