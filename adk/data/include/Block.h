#ifndef BLOCK_H
#define BLOCK_H

#include <string>

#include "BlockProperty.h"
#include "json.hpp"
#include "spdlog/include/spdlog/spdlog.h"

/**
 * @brief Represents a Block
 *
 */
class Block {
   protected:
    int _block_light_filter;
    nlohmann::json::object_t _crafting;
    std::variant<bool, double> _explosion;
    std::variant<bool, double> _mining;
    std::string _display_name;
    nlohmann::json::object_t _flammable;
    double _friction;
    std::string _geometry;
    int _light_emission;
    std::string _loot;
    std::string _color;
    std::vector<int> _rotation;
    std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
        _collision;
    std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
        _selection;
    std::pair<std::string, std::string> _creative;

    /**
     * @brief Ensure the collision_box and selection_box is valid
     *
     * @param component_check The vectors of origin and size
     * @param component Used to log collision or selection
     * @param id Identifier of block
     * @return true
     * @return false
     */
    bool ensureValidity(
        std::pair<std::vector<int>, std::vector<int>> component_check,
        std::string component, std::string id) {
        if (component_check.first.at(0) < -8 ||
            component_check.first.at(0) > 8 ||
            component_check.first.at(1) < 0 ||
            component_check.first.at(1) > 16 ||
            component_check.first.at(2) < -8 ||
            component_check.first.at(2) > 8) {
            spdlog::error(
                "{} - Minimal position of the bounds of the {} box. \"origin\" "
                "is "
                "specified as [x, y, z] and must be in the range (-8, 0, -8) "
                "to (8, 16, 8), inclusive",
                id, component);
            exit(EXIT_FAILURE);
        }

        int origin_1 = component_check.first.at(0);
        int size_1 = component_check.second.at(0);
        int origin_2 = component_check.first.at(1);
        int size_2 = component_check.second.at(1);
        int origin_3 = component_check.first.at(2);
        int size_3 = component_check.second.at(2);

        if ((origin_1 + size_1) < -8 || (origin_1 + size_1) > 8) {
            spdlog::error(
                "{} - Size of each side of the {} box. Size is "
                "specified as [x, y, z]. \"origin\" + \"size\" must be "
                "in the range (-8, 0, -8) to (8, 16, 8), inclusive",
                id),
                component;
            exit(EXIT_FAILURE);
        }

        if ((origin_2 + size_2) < 0 || (origin_2 + size_2) > 16) {
            spdlog::error(
                "{} - Size of each side of the {} box. Size is "
                "specified as [x, y, z]. \"origin\" + \"size\" must be "
                "in the range (-8, 0, -8) to (8, 16, 8), inclusive",
                id),
                component;
            exit(EXIT_FAILURE);
        }

        if ((origin_3 + size_3) < -8 || (origin_3 + size_3) > 8) {
            spdlog::error(
                "{} - Size of each side of the {} box. Size is "
                "specified as [x, y, z]. \"origin\" + \"size\" must be "
                "in the range (-8, 0, -8) to (8, 16, 8), inclusive",
                id),
                component;
            exit(EXIT_FAILURE);
        }

        return true;
    }

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "block"; };

    Block(){};
    /**
     * @brief Construct a new Block object
     *
     * @param property BlockProperty
     */
    Block(BlockProperty property) {
        _block_light_filter = property.getBlockLightFilter();
        _crafting = property.getCrafting();
        _explosion = property.getExplosion();
        _mining = property.getMining();
        _display_name = property.getName();
        _flammable = property.getFlamamble();
        _friction = property.getFriction();
        _light_emission = property.getLightEmission();
        _loot = property.getLoot();
        _color = property.getColor();
        _rotation = property.getRotation();
        _collision = property.getCollision();
        _selection = property.getSelection();
        _creative = property.getCreative();
    }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return json
     */
    virtual json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.60";
        j["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;
        j["minecraft:block"]["components"]["minecraft:unit_cube"] =
            json::object();

        if (_block_light_filter != 15) {
            if (_block_light_filter > 15 || _block_light_filter < 0) {
                spdlog::get("Blocks/Items")
                    ->error("{} - BlockLightFilter can only be in range (0-15)",
                            id);
                exit(EXIT_FAILURE);
            }

            j["minecraft:block"]["components"]["minecraft:light_dampening"] =
                _block_light_filter;
        }

        if (_crafting != json::object_t({}))
            j["minecraft:block"]["components"]["minecraft:crafting_table"] =
                _crafting;

        if (std::get_if<bool>(&_explosion)) {
            if (!std::get<bool>(_explosion)) {
                j["minecraft:block"]["components"]
                 ["minecraft:destructible_by_explosion"] = false;
            }
        } else if (std::get_if<double>(&_explosion)) {
            j["minecraft:block"]["components"]
             ["minecraft:destructible_by_explosion"] = {
                 {"explosion_resistance", std::get<double>(_explosion)}};
        }

        if (std::get_if<bool>(&_mining)) {
            if (!std::get<bool>(_mining)) {
                j["minecraft:block"]["components"]
                 ["minecraft:destructible_by_mining"] = false;
            }
        } else if (std::get_if<double>(&_mining)) {
            j["minecraft:block"]["components"]
             ["minecraft:destructible_by_mining"] = {
                 {"seconds_to_destroy", std::get<double>(_mining)}};
        }

        if (!_display_name.empty())
            j["minecraft:block"]["components"]["minecraft:display_name"] =
                _display_name;

        if (_flammable != json::object_t({}))
            j["minecraft:block"]["components"]["minecraft:flammable"] =
                _flammable;

        if (_friction != 0.4) {
            if (_friction > 0.9 || _friction < 0.0) {
                spdlog::get("Blocks/Items")
                    ->error("{} - Friction can only be in range (0.0-0.9)", id);
                exit(EXIT_FAILURE);
            }

            j["minecraft:block"]["components"]["minecraft:friction"] =
                _friction;
        }

        if (_light_emission != 0) {
            if (_light_emission > 15 || _light_emission < 0) {
                spdlog::get("Blocks/Items")
                    ->error("{} - BlockLightFilter can only be in range (0-15)",
                            id);
                exit(EXIT_FAILURE);
            }

            j["minecraft:block"]["components"]["minecraft:light_emission"] =
                _light_emission;
        }

        if (!_loot.empty())
            j["minecraft:block"]["components"]["minecraft:loot"] = _loot;

        if (!_color.empty())
            j["minecraft:block"]["components"]["minecraft:map_color"] = _color;

        if (_rotation != std::vector<int>{0, 0, 0}) {
            for (auto const& entry : _rotation) {
                if (entry % 90 != 0) {
                    spdlog::get("Blocks/Items")
                        ->error("{} - Rotation can only be factors of 90", id);
                    exit(EXIT_FAILURE);
                }
            }

            j["minecraft:block"]["components"]["minecraft:rotation"] =
                _rotation;
        }

        if (std::get_if<bool>(&_collision)) {
            if (!std::get<bool>(_collision)) {
                j["minecraft:block"]["components"]["minecraft:collision_box"] =
                    false;
            }
        } else if (std::get_if<std::pair<std::vector<int>, std::vector<int>>>(
                       &_collision)) {
            if (ensureValidity(
                    std::get<std::pair<std::vector<int>, std::vector<int>>>(
                        _collision),
                    "collision", id)) {
                j["minecraft:block"]["components"]["minecraft:collision_box"] =
                    {{"origin",
                      std::get<std::pair<std::vector<int>, std::vector<int>>>(
                          _collision)
                          .first},
                     {"size",
                      std::get<std::pair<std::vector<int>, std::vector<int>>>(
                          _collision)
                          .second}};
            }
        }

        if (std::get_if<bool>(&_selection)) {
            if (!std::get<bool>(_selection)) {
                j["minecraft:block"]["components"]["minecraft:selection_box"] =
                    false;
            }
        } else if (std::get_if<std::pair<std::vector<int>, std::vector<int>>>(
                       &_selection)) {
            if (ensureValidity(
                    std::get<std::pair<std::vector<int>, std::vector<int>>>(
                        _selection),
                    "selection", id)) {
                j["minecraft:block"]["components"]["minecraft:selection_box"] =
                    {{"origin",
                      std::get<std::pair<std::vector<int>, std::vector<int>>>(
                          _selection)
                          .first},
                     {"size",
                      std::get<std::pair<std::vector<int>, std::vector<int>>>(
                          _selection)
                          .second}};
            }
        }

        if (!_creative.first.empty()) {
            j["minecraft:block"]["description"]["menu_category"]["category"] =
                _creative.first;
            if (!_creative.second.empty()) {
                j["minecraft:block"]["description"]["menu_category"]["group"] =
                    _creative.second;
            }
        }

        return j;
    }
};

#endif