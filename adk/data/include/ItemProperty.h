#ifndef ITEMPROPERTY_H
#define ITEMPROPERTY_H

#include <string>

class ItemProperty {
   public:
    class Property {
       public:
        std::string display_name = "";
        std::string icon = "";
        int stack = 64;

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
    };
};

#endif