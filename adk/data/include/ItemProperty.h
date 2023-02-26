#ifndef ITEMPROPERTY_H
#define ITEMPROPERTY_H

#include <string>

enum class Dye {
    BLACK,
    RED,
    GREEN,
    BROWN,
    BLUE,
    PURPLE,
    CYAN,
    SILVER,
    GRAY,
    PINK,
    LIME,
    YELLOW,
    LIGHTBLUE,
    MAGENTA,
    ORANGE,
    WHITE
};

std::string getDye(Dye dye) {
    switch (dye) {
        case Dye::BLACK:
            return "black";
        case Dye::RED:
            return "red";
        case Dye::GREEN:
            return "green";
        case Dye::BROWN:
            return "brown";
        case Dye::BLUE:
            return "blue";
        case Dye::PURPLE:
            return "purple";
        case Dye::CYAN:
            return "cyan";
        case Dye::SILVER:
            return "silver";
        case Dye::GRAY:
            return "gray";
        case Dye::PINK:
            return "pink";
        case Dye::LIME:
            return "lime";
        case Dye::YELLOW:
            return "yellow";
        case Dye::LIGHTBLUE:
            return "lightblue";
        case Dye::MAGENTA:
            return "magenta";
        case Dye::ORANGE:
            return "orange";
        case Dye::WHITE:
            return "white";
        default:
            return "Error";
    }
}

class ItemProperty {
   public:
    class Property {
       public:
        std::string display_name;
        std::string icon;
        int stack;
        std::string block_placer;
        std::vector<std::string> block_placer_placement;
        std::string cooldown_category;
        float cooldown_time;
        std::string dye;
        std::string entity_placer;
        std::vector<std::string> entity_placer_placement;
        std::vector<std::string> entity_placer_dispense;
        std::vector<float> offset_main;
        std::vector<float> offset_offhand;

        /// @brief Sets "display_name" component
        /// @param n Display Name item component. Display Names set the name to
        /// display when an item is in use or hovered over.
        Property setName(std::string n) {
            this->display_name = n;
            return *this;
        }

        /// @brief Sets "icon" component
        /// @param i The icon item component determines the icon to represent
        /// the item.
        Property setIcon(std::string i) {
            this->icon = i;
            return *this;
        }

        /// @brief Sets "max_stack_size" component
        /// @param s The max stack size this item can hold
        Property setStack(int s) {
            this->stack = s;
            return *this;
        }

        Property setBlockPlacer(std::string block,
                                std::vector<std::string> placement = {}) {
            this->block_placer = block;
            this->block_placer_placement = placement;
            return *this;
        }

        Property setCooldown(std::string category, float time) {
            this->cooldown_category = category;
            this->cooldown_time = time;
            return *this;
        }

        Property setDye(Dye dye) {
            this->dye = getDye(dye);
            return *this;
        }

        Property setEntityPlacer(std::string entity,
                                 std::vector<std::string> placement = {},
                                 std::vector<std::string> dispense = {}) {
            this->entity_placer = entity;
            this->entity_placer_placement = placement;
            this->entity_placer_dispense = dispense;
            return *this;
        }

        Property setRenderMain(std::vector<float> offset) {
            this->offset_main = offset;
            return *this;
        }

        Property setRenderOffhand(std::vector<float> offset) {
            this->offset_offhand = offset;
            return *this;
        }
    };
};

#endif