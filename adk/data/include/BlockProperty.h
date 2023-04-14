#ifndef BLOCKPROPERTY_H
#define BLOCKPROPERTY_H

#include <string>
#include <variant>
#include <vector>

#include "BlockCategory.h"
#include "json.hpp"

/**
 * @brief Represents block properties such as destroy speed, loot, etc
 *
 */
class BlockProperty {
   private:
    int block_light_filter = 15;
    nlohmann::json::object_t crafting;
    std::variant<bool, double> explosion = true;
    std::variant<bool, double> mining = true;
    std::string display_name;
    nlohmann::json::object_t flammable;
    double friction = 0.4;
    std::string geometry;
    int light_emission;
    std::string loot;
    std::string color;
    std::vector<int> rotation{0, 0, 0};
    std::vector<double> scale{0, 0, 0};
    std::vector<double> translation{0, 0, 0};
    std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
        collision = true;
    std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
        selection = true;
    std::pair<std::string, std::string> creative;

   public:
    /**
     * @brief Sets the "light_dampening" component
     *
     * @param light_filter The amount that light will be dampened when it passes
     through the block, in a range (0-15). Higher value means the light will be
     dampened more
     * @return BlockProperty
     */
    BlockProperty setBlockLightFilter(int light_filter) {
        this->block_light_filter = light_filter;
        return *this;
    }

    /**
     * @brief Set the "crafting_table" component
     *
     * @param tags Defines the tags recipes should define to be crafted on this
     * table. Limited to 64 tags. Each tag is limited to 64 characters
     * @param name Specifies the language file key that maps to what text will
     * be displayed in the UI of this table. If the string given can not be
     * resolved as a loc string, the raw string given will be  displayed. If
     * this field is omitted, the name displayed will default to the name
     * specified in the "display_name" component. If this block has no
     * "display_name" component, the name displayed will default to the name of
     * the block
     * @return BlockProperty
     */
    BlockProperty setCrafting(std::vector<std::string>& tags,
                              std::string name) {
        this->crafting = {{"crafting_table", tags}, {"table_name", name}};
        return *this;
    }

    /**
     * @brief Sets "destructible_by_explosion" component
     *
     * @param explosion_resistance Sets the explosion resistance for the
     * block. Greater values result in greater resistance to explosions
     * The scale will be different for different explosion power levels. A
     * negative value or 0 means it will easily explode; larger numbers
     * increase level of resistance
     * @return BlockProperty
     */
    BlockProperty setExplosion(
        std::variant<bool, double> explosion_resistance) {
        if (std::get_if<bool>(&explosion_resistance)) {
            this->explosion = std::get<bool>(explosion_resistance);
            return *this;
        } else {
            this->explosion = std::get<double>(explosion_resistance);
            return *this;
        }
    }

    /**
     * @brief Set the "destructible_by_mining" component
     *
     * @param mining_speed Sets the number of seconds it takes to destroy
     * the block with base equipment. Greater numbers result in greater
     * mining times
     * @return BlockProperty
     */
    BlockProperty setMining(std::variant<bool, double> mining_speed) {
        if (std::get_if<bool>(&mining_speed)) {
            this->mining = std::get<bool>(mining_speed);
            return *this;
        } else {
            this->mining = std::get<double>(mining_speed);
            return *this;
        }
    }

    /**
     * @brief Set the "display_name" component
     *
     * @param name Specifies the language file key that maps to what text
     * will be displayed when you hover over the block in your inventory and
     * hotbar If the string given can not be resolved as a loc string, the
     * raw string given will be displayed. If this component is omitted, the
     * name of the block will be used as the display name
     * @return BlockProperty
     */
    BlockProperty setName(std::string name) {
        this->display_name = name;
        return *this;
    }

    /**
     * @brief Set the "flammable" component
     *
     * @param catch_chance A modifier affecting the chance that this block
     * will catch flame when next to a fire. Values are greater than or
     * equal to 0, with a higher number meaning more likely to catch on
     * fire. For a "catch_chance_modifier" greater than 0, the fire will
     * continue to burn until the block is destroyed (or it will burn
     * forever if the "destroy_chance_modifier" is 0). If the
     * "catch_chance_modifier" is 0, and the block is directly ignited, the
     * fire will eventually burn out without destroying the block (or it
     * will have a chance to be destroyed if "destroy_chance_modifier" is
     * greater than 0). The default value of 5 is the same as that of Planks
     * @param destroy A modifier affecting the chance that this block will
     * be destroyed by flames when on fire. Values are greater than or equal
     * to 0, with a higher number meaning more likely to be destroyed by
     * fire. For a "destroy_chance_modifier" of 0, the block will never be
     * destroyed by fire, and the fire will burn forever if the
     * "catch_chance_modifier" is greater than 0. The default value of 20 is
     * the same as that of Planks
     * @return BlockProperty
     */
    BlockProperty setFlammable(int catch_chance, int destroy) {
        this->flammable = {{"catch_chance_modifier", catch_chance},
                           {"destroy_chance_modifier", destroy}};
        return *this;
    }

    /**
     * @brief Set the "friction" component
     *
     * @param friction Describes the friction for this block in a range of
     (0.0-0.9). Friction affects an entity's movement speed when it travels
     on the block. Greater value results in more friction
     * @return BlockProperty
     */
    BlockProperty setFriction(double friction) {
        this->friction = friction;
        return *this;
    }

    /**
     * @brief Set the "geometry" component
     *
     * @param geometry The description identifier of the geometry file to
     * use to render this block. This identifier must match an existing
     * geometry identifier in any of the currently loaded resource packs
     * @return BlockProperty
     */
    BlockProperty setGeometry(std::string geometry) {
        this->geometry = geometry;
        return *this;
    }

    /**
     * @brief Set the "light_emission" component
     *
     * @param emission The amount of light this block will emit in a range
     * (0-15). Higher value means more light will be emitted
     * @return BlockProperty
     */
    BlockProperty setLightEmission(int emission) {
        this->light_emission = emission;
        return *this;
    }

    /**
     * @brief Set the "loot" component
     *
     * @param loot_table The path to the loot table, relative to the
     * behavior pack. Path string is limited to 256 characters
     * @return BlockProperty
     */
    BlockProperty setLoot(std::string loot_table) {
        this->loot = loot_table;
        return *this;
    }

    /**
     * @brief Set the "map_color" component
     *
     * @param map_color Sets the color of the block when rendered to a map.
     * The color is represented as a hex value in the format "#RRGGBB". May
     * also be expressed as an array of [R, G, B] from 0 to 255. If this
     * component is omitted, the block will not show up on the map
     * @return BlockProperty
     */
    BlockProperty setColor(std::string map_color) {
        this->color = map_color;
        return *this;
    }

    /**
     * @brief Set the "translation" field of "transformation" component
     * @param translation
     * @return BlockProperty
     */
    BlockProperty setTranslation(std::vector<double> translation) {
        this->translation = translation;
        return *this;
    }

    /**
     * @brief Set the "scale" field of "transformation" component
     * @param scale
     * @return BlockProperty
     */
    BlockProperty setScale(std::vector<double> scale) {
        this->scale = scale;
        return *this;
    }

    /**
     * @brief Set the "rotation" field of "transformation" component
     * @param rotation The block's rotation around the center of the cube in
     * degrees. The rotation is specified as [x, y, z]. Angles need to be in
     * factors of 90
     * @return BlockProperty
     */
    BlockProperty setRotation(std::vector<int> rotation) {
        this->rotation = rotation;
        return *this;
    }

    /**
     * @brief Set the "collision_box" component
     *
     * @param collision_box Accepts either bool or pair of int vectors
     * @return BlockProperty
     */
    BlockProperty setCollision(
        std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
            collision_box) {
        if (std::get_if<bool>(&collision_box)) {
            this->collision = std::get<bool>(collision_box);
            return *this;
        } else {
            this->collision =
                std::get<std::pair<std::vector<int>, std::vector<int>>>(
                    collision_box);
            return *this;
        }
    }

    /**
     * @brief Set the "selection_box" component
     *
     * @param selection_box Accepts either a bool or a pair of int vectors
     * @return BlockProperty
     */
    BlockProperty setSelection(
        std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
            selection_box) {
        if (std::get_if<bool>(&selection_box)) {
            this->selection = std::get<bool>(selection_box);
            return *this;
        } else {
            this->selection =
                std::get<std::pair<std::vector<int>, std::vector<int>>>(
                    selection_box);
            return *this;
        }
    }

    /**
     * @brief Set the Creative Category component
     *
     * @param tab Determines which category this block will be placed under
     in the inventory and crafting table container screens. Options are
     "construction", "nature", "equipment", "items", and "none". If omitted
     or "none" is specified, the block will not appear in the inventory or
     crafting table container screens
     * @param category Specifies the language file key that maps to which
     expandable/collapsible group this block will be a part of within a
     category. If this field is omitted, or there is no group whose name
     matches the loc string, this block will be placed standalone in the
     given category
     * @return BlockProperty
     */
    BlockProperty setCreativeCategory(
        adk::CreativeTab tab,
        adk::CreativeCategory category = adk::CreativeCategory::NONE) {
        this->creative = std::make_pair(adk::getCreativeTab(tab),
                                        adk::getCreativeCategory(category));
        return *this;
    }

    /**
     * @brief Get the "light_dampening" component
     *
     * @return int
     */
    int getBlockLightFilter() { return block_light_filter; }

    /**
     * @brief Get the "crafting_table" component
     *
     * @return nlohmann::json::object_t
     */
    nlohmann::json::object_t getCrafting() { return crafting; }

    /**
     * @brief Get the "destructible_by_explosion" component
     *
     * @return std::variant<bool, double>
     */
    std::variant<bool, double> getExplosion() { return explosion; }

    /**
     * @brief Get the "destructible_by_mining" component
     *
     * @return std::variant<bool, double>
     */
    std::variant<bool, double> getMining() { return mining; }

    /**
     * @brief Get the "display_name" component
     *
     * @return std::string
     */
    std::string getName() { return display_name; }

    /**
     * @brief Get the "flamamble" component
     *
     * @return nlohmann::json::object_t
     */
    nlohmann::json::object_t getFlamamble() { return flammable; }

    /**
     * @brief Get the "Friction" component
     *
     * @return double
     */
    double getFriction() { return friction; }

    /**
     * @brief Get the "geometry" component
     *
     * @return std::string
     */
    std::string getGeometry() { return geometry; }

    /**
     * @brief Get the "light_emission" component
     *
     * @return int
     */
    int getLightEmission() { return light_emission; }

    /**
     * @brief Get the "loot" component
     *
     * @return std::string
     */
    std::string getLoot() { return loot; }

    /**
     * @brief Get the "map_color" component
     *
     * @return std::string
     */
    std::string getColor() { return color; }

    /**
     * @brief Get the "translation" field of "transformation" component
     *
     * @return std::vector<int>
     */
    std::vector<double> getTranslation() { return translation; }

    /**
     * @brief Get the "scale" field of "transformation" component
     *
     * @return std::vector<int>
     */
    std::vector<double> getScale() { return scale; }

    /**
     * @brief Get the "rotation" field of "transformation" component
     *
     * @return std::vector<int>
     */
    std::vector<int> getRotation() { return rotation; }

    /**
     * @brief Get the "collision_box" component
     *
     * @return std::variant<bool, std::pair<std::vector<int>,
     * std::vector<int>>>
     */
    std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
    getCollision() {
        return collision;
    }

    /**
     * @brief Get the "selection_box" component
     *
     * @return std::variant<bool, std::pair<std::vector<int>,
     * std::vector<int>>>
     */
    std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
    getSelection() {
        return selection;
    }

    /**
     * @brief Get the Creative Category component
     *
     * @return std::pair<std::string, std::string>
     */
    std::pair<std::string, std::string> getCreative() { return creative; }
};

#endif