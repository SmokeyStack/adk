#ifndef RECORDITEM_H
#define RECORDITEM_H

#include <string>

#include "item.h"
#include "item_property.h"
#include "json.hpp"

/**
 * @brief Represents a Record Item
 *
 */
class RecordItem : public Item {
   protected:
    std::string _sound;
    float _duration;
    int _signal;

   public:
    RecordItem() {}
    /**
     * @brief Construct a new Record Item object
     *
     * @param property ItemProperty
     * @param sound Sound event type
     * @param duration Duration of sound events in seconds
     * @param signal Signal strength for comparator blocks to use
     */
    RecordItem(ItemProperty property, std::string sound, float duration,
               int signal = 0) {
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
        _sound = sound;
        _duration = duration;
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

        j["minecraft:item"]["components"]["minecraft:record"] = {
            {"sound_event", _sound},
            {"duration", _duration},
            {"comparator_signal", _signal}};

        return j;
    }
};

#endif