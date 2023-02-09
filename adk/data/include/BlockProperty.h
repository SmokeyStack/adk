#ifndef BLOCKPROPERTY_h
#define BLOCKPROPERTY_h

#include <string>
#include <vector>

#include "json.hpp"

/// @brief Class that represents properties such as destroy speed, loot, etc
class BlockProperty {
   public:
    class Property {
       public:
        int block_light_filter = 15;
        nlohmann::json::object_t crafting = {
            {"crafting_table", {"crafting_table"}}, {"table_name", "Foo Bar"}};
        nlohmann::json::object_t explosion = {{"explosion_resistance", 0}};
        nlohmann::json::object_t mining = {{"seconds_to_destroy", 0.0}};
        std::string display_name = "";
        nlohmann::json::object_t flammable = {{"catch_chance_modifier", 5},
                                              {"destroy_chance_modifier", 20}};
        double friction = 0.4;
        std::string geometry = "";
        int light_emission = 0;
        std::string loot = "";
        std::string color = "";
        std::vector<int> rotation = {0, 0, 0};

        /// @brief Sets "light_dampening" component
        /// @param blf The amount that light will be dampened when it
        /// passes through the block, in a range (0-15). Higher value means the
        /// light will be dampened more.
        Property setBlockLightFilter(int blf) {
            this->block_light_filter = blf;
            return *this;
        }

        /// @brief Sets "crafting_table" component
        /// @param tags Defines the tags recipes should define to be crafted on
        /// this table. Limited to 64 tags. Each tag is limited to 64
        /// characters.
        /// @param name Specifies the language file key that maps to what text
        /// will be displayed in the UI of this table. If the string given can
        /// not be resolved as a loc string, the raw string given will be
        /// displayed. If this field is omitted, the name displayed will default
        /// to the name specified in the "display_name" component. If this block
        /// has no "display_name" component, the name displayed will default to
        /// the name of the block.
        Property setCrafting(std::vector<std::string>& tags, std::string name) {
            this->crafting = {{"crafting_table", tags}, {"table_name", name}};
            return *this;
        }

        /// @brief Sets "destructible_by_explosion" component
        /// @param e Sets the explosion resistance for the block.
        /// Greater values result in greater resistance to explosions. The scale
        /// will be different for different explosion power levels. A negative
        /// value or 0 means it will easily explode; larger numbers increase
        /// level of resistance.
        Property setExplosion(float e) {
            this->explosion = {{"explosion_resistance", e}};
            return *this;
        }

        /// @brief Sets "destructible_by_mining" component
        /// @param m Sets the number of seconds it takes to destroy the block
        /// with base equipment. Greater numbers result in greater mining times.
        Property setMining(float m) {
            this->mining = {{"seconds_to_destroy", m}};
            return *this;
        }

        /// @brief Sets "display_name" component
        /// @param n Specifies the language file key that maps to what text will
        /// be displayed when you hover over the block in your inventory and
        /// hotbar. If the string given can not be resolved as a loc string, the
        /// raw string given will be displayed. If this component is omitted,
        /// the name of the block will be used as the display name.
        Property setName(std::string n) {
            this->display_name = n;
            return *this;
        }

        /// @brief Sets "flammable" component
        /// @param catch_chance A modifier affecting the chance that this block
        /// will catch flame when next to a fire. Values are greater than or
        /// equal to 0, with a higher number meaning more likely to catch on
        /// fire. For a "catch_chance_modifier" greater than 0, the fire will
        /// continue to burn until the block is destroyed (or it will burn
        /// forever if the "destroy_chance_modifier" is 0). If the
        /// "catch_chance_modifier" is 0, and the block is directly ignited, the
        /// fire will eventually burn out without destroying the block (or it
        /// will have a chance to be destroyed if "destroy_chance_modifier" is
        /// greater than 0). The default value of 5 is the same as that of
        /// Planks.
        /// @param destroy A modifier affecting the chance that this block will
        /// be destroyed by flames when on fire. Values are greater than or
        /// equal to 0, with a higher number meaning more likely to be destroyed
        /// by fire. For a "destroy_chance_modifier" of 0, the block will never
        /// be destroyed by fire, and the fire will burn forever if the
        /// "catch_chance_modifier" is greater than 0. The default value of 20
        /// is the same as that of Planks.
        Property setFlammable(int catch_chance, int destroy) {
            this->flammable = {{"catch_chance_modifier", catch_chance},
                               {"destroy_chance_modifier", destroy}};
            return *this;
        }

        /// @brief Sets "friction" component
        /// @param f Describes the friction for this block in a range of
        /// (0.0-0.9). Friction affects an entity's movement speed when it
        /// travels on the block. Greater value results in more friction.
        Property setFriction(double f) {
            this->friction = f;
            return *this;
        }

        /// @brief Sets "geometry" component
        /// @param g The description identifier of the geometry file to use to
        /// render this block. This identifier must match an existing geometry
        /// identifier in any of the currently loaded resource packs.
        Property setGeometry(std::string g) {
            this->geometry = g;
            return *this;
        }

        /// @brief Sets "light_emission" component
        /// @param le The amount of light this block will emit in a range
        /// (0-15). Higher value means more light will be emitted.
        Property setLightEmission(int le) {
            this->light_emission = le;
            return *this;
        }

        /// @brief Sets "loot" component
        /// @param l The path to the loot table, relative to the behavior pack.
        /// Path string is limited to 256 characters.
        Property setLoot(std::string l) {
            this->loot = l;
            return *this;
        }

        /// @brief Sets "map_color" component
        /// @param c Sets the color of the block when rendered to a map. The
        /// color is represented as a hex value in the format "#RRGGBB". If this
        /// component is omitted, the block will not show up on the map.
        Property setColor(std::string c) {
            this->color = c;
            return *this;
        }

        /// @brief Sets "rotation" component
        /// @param r The block's rotation around the center of the cube in
        /// degrees. The rotation is specified as [x, y, z]. Angles need to be
        /// in factors of 90.
        Property setRotation(std::vector<int> r) {
            this->rotation = r;
            return *this;
        }
    };
};

#endif