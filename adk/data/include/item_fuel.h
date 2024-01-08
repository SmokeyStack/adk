#ifndef FUELITEM_H
#define FUELITEM_H

#include <string>

#include "item.h"
#include "item_property.h"
#include "json.hpp"

/**
 * @brief Represents a Fuel Item
 *
 */
class FuelItem : public Item {
   protected:
    float _burn_time;

   public:
    FuelItem() {}
    /**
     * @brief Construct a new Fuel Item object
     *
     * @param property ItemProperty
     * @param burn_time How long in seconds will this fuel cook items for
     */
    FuelItem(ItemProperty property, float burn_time) {
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
        _burn_time = burn_time;
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

        j["minecraft:item"]["components"]["minecraft:fuel"]["duration"] =
            _burn_time;

        return j;
    }
};

#endif