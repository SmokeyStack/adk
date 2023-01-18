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

        Property setName(std::string n) {
            this->display_name = n;
            return *this;
        }
        Property setIcon(std::string i) {
            this->icon = i;
            return *this;
        }
        Property setStack(int s) {
            this->stack = s;
            return *this;
        }
    };
};

#endif