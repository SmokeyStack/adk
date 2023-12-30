#ifndef DURABILITYITEM_H
#define DURABILITYITEM_H

#include <string>

#include "Item.h"
#include "ItemProperty.h"
#include "json.hpp"

/**
 * @brief Represents an item with durability
 *
 */
class DurabilityItem : public Item {
   protected:
    int _durability;
    int _damage_chance_min;
    int _damage_chance_max;

   public:
    DurabilityItem() {}
    /**
     * @brief Construct a new Durability Item object
     *
     * @param property ItemProperty
     * @param durability How much durability point should this item have
     * @param damage_chance_min Minimum chance the item takes damage
     * @param damage_chance_max Maximum chance the item takes damage
     */
    DurabilityItem(ItemProperty property, int durability, int damage_chance_min,
                   int damage_chance_max) {
        _display_name = property.getName();
        _icon = property.getIcon();
        _stack = property.getStack();
        _block_placer = property.getBlockPlacer();
        _block_placer_placement = property.getBlockPlacerPlacement();
        _cooldown_category = property.getCooldownCategory();
        _cooldown_time = property.getCooldownTime();
        _dye = property.getDyeProperty();
        _entity_placer = property.getEntityPlacer();
        _entity_placer_placement = property.getEntityPlacerPlacement();
        _entity_placer_dispense = property.getEntityPlacerDispense();
        _offset_main = property.getOffsetMain();
        _offset_offhand = property.getOffsetOff();
        _durability = durability;
        _damage_chance_min = damage_chance_min;
        _damage_chance_max = damage_chance_max;
    }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return json
     */
    json output(std::string mod_id, std::string id) {
        j = Item::output(mod_id, id);

        j["minecraft:item"]["components"]["minecraft:durability"]
         ["max_durability"] = _durability;
        j["minecraft:item"]["components"]["minecraft:durability"]
         ["damage_chance"]["min"] = _damage_chance_min;
        j["minecraft:item"]["components"]["minecraft:durability"]
         ["damage_chance"]["max"] = _damage_chance_max;

        j["minecraft:item"]["events"][mod_id + ":damage_item"]["damage"] = {
            {"type", "durability"}, {"amount", 1}, {"target", "self"}};

        return j;
    }
};

#endif