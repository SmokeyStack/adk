#ifndef ARMORTYPE_H
#define ARMORTYPE_H

#include <spdlog/spdlog.h>

#include <string>

namespace adk {
/**
 * @brief Represents slots for armor
 *
 */
enum class ArmorSlot { HEAD, CHEST, LEGS, FEET };

/**
 * @brief Get the Armor Slot object
 *
 * @param slot ArmorSlot Enum
 * @return std::string
 */
std::string getArmorSlot(adk::ArmorSlot slot) {
    switch (slot) {
        case adk::ArmorSlot::HEAD:
            return "slot.armor.head";
        case adk::ArmorSlot::CHEST:
            return "slot.armor.chest";
        case adk::ArmorSlot::LEGS:
            return "slot.armor.legs";
        case adk::ArmorSlot::FEET:
            return "slot.armor.feet";
        default:
            logger->error("This shouldn't happen");
            exit(EXIT_FAILURE);
            return "Error";
    }
}
}  // namespace adk

#endif