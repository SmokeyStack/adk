#ifndef ARMORITEM_H
#define ARMORITEM_H

#include <string>

#include "type_armor.h"
#include "item_durability.h"
#include "item_property.h"
#include "json.hpp"

/**
 * @brief Represents an Armor Item
 *
 */
class ArmorItem : public DurabilityItem {
   protected:
    int _protection;
    std::string _slot;
    bool _dispensable;

   public:
    ArmorItem() {}
    /**
     * @brief Construct a new Armor Item object
     *
     * @param property An ItemProperty object
     * @param protection How much protection point should this armor give
     * @param slot Which slot should the armor go in
     * @param durability How much durability point should this armor have
     * @param damage_chance_min Minimum chance the armor takes damage
     * @param damage_chance_max Maximum chance the armor takes damage
     * @param dispensable Can this armor be equipped by a dispenser
     */
    ArmorItem(ItemProperty property, int protection, adk::ArmorSlot slot,
              int durability, int damage_chance_min, int damage_chance_max,
              bool dispensable = true) {
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
        _protection = protection;
        _slot = adk::getArmorSlot(slot);
        _durability = durability;
        _dispensable = dispensable;
        _damage_chance_min = damage_chance_min;
        _damage_chance_max = damage_chance_max;
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

        j["minecraft:item"]["components"]["minecraft:armor"]["protection"] =
            _protection;
        j["minecraft:item"]["components"]["minecraft:wearable"]["slot"] = _slot;
        j["minecraft:item"]["components"]["minecraft:wearable"]["dispensable"] =
            _dispensable;

        return j;
    }
};

#endif