#ifndef WEAPONITEM_H
#define WEAPONITEM_H

#include <string>

#include "item_durability.h"
#include "item_property.h"
#include "json.hpp"

/**
 * @brief Represents a Weapon Item
 *
 */
class WeaponItem : public DurabilityItem {
   protected:
    int _damage;

   public:
    WeaponItem() {}
    /**
     * @brief Construct a new Weapon Item object
     *
     * @param property ItemProperty
     * @param damage How much damage this item does
     * @param durability How much durability point should this item have
     * @param damage_chance_min Minimum chance the item takes damage
     * @param damage_chance_max Maximum chance the item takes damage
     * @param blocks Key/Value pair of seconds and blocks
     */
    WeaponItem(ItemProperty property, int damage, int durability,
               int damage_chance_min, int damage_chance_max) {
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
        _damage = damage;
    }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return nlohmann::json
     */
    json output(std::string mod_id, std::string id) {
        j = DurabilityItem::output(mod_id, id);

        j["minecraft:item"]["components"]["minecraft:damage"] = _damage;

        j["minecraft:item"]["components"]["minecraft:weapon"]
         ["on_hurt_entity"] = mod_id + ":damage_item";

        return j;
    }
};

#endif