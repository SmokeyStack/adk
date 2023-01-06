#ifndef BLOCKPROPERTY_h
#define BLOCKPROPERTY_h

#include <string>
#include <vector>

#include "json.hpp"

class BlockProperty {
   public:
    class Property {
       public:
        int block_light_filter = 15;
        nlohmann::json::object_t crafting = {
            {"crafting_table", {"crafting_table"}}, {"table_name", "Foo Bar"}};
        nlohmann::json::object_t explosion = {{"explosion_resistance", 0}};
        nlohmann::json::object_t mining = {{"seconds_to_destory", 0.0}};
        std::string display_name = "";
        nlohmann::json::object_t flammable = {{"catch_chance_modifier", 5},
                                              {"destroy_chance_modifier", 20}};
        double friction = 0.4;
        std::string geometry = "";
        int light_emission = 0;
        std::string loot = "";
        std::string colour = "";
        std::vector<int> rotation = {0, 0, 0};

        Property setBlockLightFilter(int blf) {
            this->block_light_filter = blf;
            return *this;
        }

        Property setCrafting(std::vector<std::string>& tags, std::string name) {
            this->crafting = {{"crafting_table", tags}, {"table_name", name}};
            return *this;
        }

        Property setExplosion(float e) {
            this->explosion = {{"explosion_resistance", e}};
            return *this;
        }

        Property setMining(float m) {
            this->mining = {{"seconds_to_destory", m}};
            return *this;
        }

        Property setName(std::string n) {
            this->display_name = n;
            return *this;
        }

        Property setFlammable(int catch_chance, int destroy) {
            this->flammable = {{"catch_chance_modifier", catch_chance},
                               {"destroy_chance_modifier", destroy}};
            return *this;
        }

        Property setFriction(double f) {
            this->friction = f;
            return *this;
        }

        Property setGeometry(std::string g) {
            this->geometry = g;
            return *this;
        }

        Property setLightEmission(int le) {
            this->light_emission = le;
            return *this;
        }

        Property setLoot(std::string l) {
            this->loot = l;
            return *this;
        }

        Property setColour(std::string c) {
            this->colour = c;
            return *this;
        }

        Property setRotation(std::vector<int> r) {
            this->rotation = r;
            return *this;
        }
    };
};

#endif