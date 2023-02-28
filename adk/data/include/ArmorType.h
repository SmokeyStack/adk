#ifndef ARMORTYPE_H
#define ARMORTYPE_H

#include <spdlog/spdlog.h>

#include <string>

namespace adk {
enum class ArmorSlot { HEAD, CHEST, LEGS, FEET };

/// @brief Turns enum ArmorSlot into string
/// @param slot enum ArmorSlot
/// @return String equivalent
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
            spdlog::error("{} is not a valid ArmorSlot", slot);
            exit(EXIT_FAILURE);
            return "Error";
    }
}
}  // namespace adk

#endif