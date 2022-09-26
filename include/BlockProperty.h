#ifndef BLOCKPROPERTY_h
#define BLOCKPROPERTY_h

#include <string>
#include <vector>

class BlockProperty {
   public:
    class Property {
       public:
        int block_light_filter = 15;
        std::string breathability = "solid";
        double friction = 0.4;
        int light_emission = 0;
        std::vector<int> rotation = {0, 0, 0};

        Property setBlockLightFilter(int blf) {
            this->block_light_filter = blf;
            return *this;
        }

        Property setBreathability(std::string b) {
            this->breathability = b;
            return *this;
        }

        Property setFriction(double f) {
            this->friction = f;
            return *this;
        }

        Property setLightEmission(int le) {
            this->light_emission = le;
            return *this;
        }

        Property setRotation(std::vector<int> r) {
            this->rotation = r;
            return *this;
        }
    };
};

#endif