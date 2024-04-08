#ifndef PROJECTILEITEM_H
#define PROJECTILEITEM_H

#include <string>

#include "item.h"
#include "item_property.h"
#include "json.hpp"

/**
 * @brief Represents a Projectile Item
 *
 */
class ProjectileItem : public Item {
   protected:
    std::string _entity;
    float _charge_time;

   public:
    ProjectileItem() {}
    /**
     * @brief Construct a new Projectile Item object
     *
     * @param property ItemProperty
     * @param entity The entity to be fired as a projectile
     * @param charge_time How long you must charge a projectile for it to
     * critically hit
     */
    ProjectileItem(ItemProperty property, std::string entity,
                   float charge_time = 0) {
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
        entity = _entity;
        _charge_time = charge_time;
    }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return nlohmann::json
     */
    json output(std::string mod_id, std::string id) {
        j = Item::output(mod_id, id);

        j["minecraft:item"]["components"]["minecraft:projectile"] = {
            {"projectile_entity", _entity},
            {"minimum_critical_power", _charge_time}};

        return j;
    }
};

#endif