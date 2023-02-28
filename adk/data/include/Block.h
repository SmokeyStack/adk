#ifndef BLOCK_H
#define BLOCK_H

#include <spdlog/spdlog.h>

#include <iostream>
#include <string>

#include "BlockProperty.h"
#include "json.hpp"

class Block {
   protected:
    int _block_light_filter;
    nlohmann::json::object_t _crafting;
    nlohmann::json::object_t _explosion;
    nlohmann::json::object_t _mining;
    std::string _display_name;
    nlohmann::json::object_t _flammable;
    double _friction;
    int _light_emission;
    std::string _loot;
    std::string _color;
    std::vector<int> _rotation;
    std::variant<bool, nlohmann::json::object_t> _does_collide, _collision;
    std::variant<bool, nlohmann::json::object_t> _is_selectable, _selection;
    std::string _tab;
    std::string _category;

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "blocks/"; };

    Block(){};
    /// @brief Represents a block
    /// @param property A BlockProperty object
    Block(BlockProperty::Property property) {
        _block_light_filter = property.block_light_filter;
        _crafting = property.crafting;
        _explosion = property.explosion;
        _mining = property.mining;
        _display_name = property.display_name;
        _flammable = property.flammable;
        _friction = property.friction;
        _light_emission = property.light_emission;
        _loot = property.loot;
        _color = property.color;
        _rotation = property.rotation;
        _does_collide = property.does_collide;
        _collision = property.collision;
        _is_selectable = property.is_selectable;
        _selection = property.selection;
        _tab = property.tab;
        _category = property.category;
    }

    /// @brief Generates the json object
    /// @param mod_id Namespace identifier
    /// @param id Identifier for the block
    /// @return json object
    virtual json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.50";
        j["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;
        j["minecraft:block"]["components"]["minecraft:unit_cube"] =
            json::object();

        if (_block_light_filter != 15)
            j["minecraft:block"]["components"]["minecraft:light_dampening"] =
                _block_light_filter;

        if (_crafting != json::object_t({{"crafting_table", {"crafting_table"}},
                                         {"table_name", "Foo Bar"}}))
            j["minecraft:block"]["components"]["minecraft:crafting_table"] =
                _crafting;
        if (_explosion != json::object_t({{"explosion_resistance", 0}}))
            j["minecraft:block"]["components"]
             ["minecraft:destructible_by_explosion"] = _explosion;

        if (_mining != json::object_t({{"seconds_to_destroy", 0.0}}))
            j["minecraft:block"]["components"]
             ["minecraft:destructible_by_mining"] = _mining;

        if (_display_name != "")
            j["minecraft:block"]["components"]["minecraft:display_name"] =
                _display_name;

        if (_flammable != json::object_t({{"catch_chance_modifier", 5},
                                          {"destroy_chance_modifier", 20}}))
            j["minecraft:block"]["components"]["minecraft:flammable"] =
                _flammable;

        if (_friction != 0.4)
            j["minecraft:block"]["components"]["minecraft:friction"] =
                _friction;

        if (_light_emission != 0)
            j["minecraft:block"]["components"]["minecraft:light_emission"] =
                _light_emission;

        if (_loot != "")
            j["minecraft:block"]["components"]["minecraft:loot"] = _loot;

        if (_color != "")
            j["minecraft:block"]["components"]["minecraft:map_color"] = _color;

        if (_rotation != std::vector<int>{0, 0, 0})
            j["minecraft:block"]["components"]["minecraft:rotation"] =
                _rotation;

        if (std::get<bool>(_does_collide)) {
            try {
                if (std::get<nlohmann::json::object_t>(
                        _collision)["origin"][0] < -8 ||
                    std::get<nlohmann::json::object_t>(
                        _collision)["origin"][0] > 8 ||
                    std::get<nlohmann::json::object_t>(
                        _collision)["origin"][1] < 0 ||
                    std::get<nlohmann::json::object_t>(
                        _collision)["origin"][1] > 16 ||
                    std::get<nlohmann::json::object_t>(
                        _collision)["origin"][2] < -8 ||
                    std::get<nlohmann::json::object_t>(
                        _collision)["origin"][2] > 8) {
                    spdlog::error(
                        "{} - Minimal position of the bounds of the collision "
                        "box. origin is specified as [x, y, z] and must be in "
                        "the range (-8, 0, -8) to (8, 16, 8), inclusive",
                        id);
                    exit(EXIT_FAILURE);
                }

                int origin_1 =
                    std::get<nlohmann::json::object_t>(_collision)["origin"][0];
                int size_1 =
                    std::get<nlohmann::json::object_t>(_collision)["size"][0];
                int origin_2 =
                    std::get<nlohmann::json::object_t>(_collision)["origin"][1];
                int size_2 =
                    std::get<nlohmann::json::object_t>(_collision)["size"][1];
                int origin_3 =
                    std::get<nlohmann::json::object_t>(_collision)["origin"][2];
                int size_3 =
                    std::get<nlohmann::json::object_t>(_collision)["size"][2];

                if ((origin_1 + size_1) < -8 || (origin_1 + size_1) > 8) {
                    spdlog::error(
                        "{} - Size of each side of the collision box. Size is "
                        "specified as [x, y, z]. origin + size must be in the "
                        "range (-8, 0, -8) to (8, 16, 8), inclusive",
                        id);
                    exit(EXIT_FAILURE);
                }

                if ((origin_2 + size_2) < 0 || (origin_2 + size_2) > 16) {
                    spdlog::error(
                        "{} - Size of each side of the collision box. Size is "
                        "specified as [x, y, z]. origin + size must be in the "
                        "range (-8, 0, -8) to (8, 16, 8), inclusive",
                        id);
                    exit(EXIT_FAILURE);
                }

                if ((origin_3 + size_3) < -8 || (origin_3 + size_3) > 8) {
                    spdlog::error(
                        "{} - Size of each side of the collision box. Size is "
                        "specified as [x, y, z]. origin + size must be in the "
                        "range (-8, 0, -8) to (8, 16, 8), inclusive",
                        id);
                    exit(EXIT_FAILURE);
                }

                j["minecraft:block"]["components"]["minecraft:collision_box"] =
                    std::get<nlohmann::json::object_t>(_collision);
            } catch (const std::exception& e) {
                e;
            }
        } else {
            j["minecraft:block"]["components"]["minecraft:collision_box"] =
                false;
        }

        if (std::get<bool>(_is_selectable)) {
            try {
                if (std::get<nlohmann::json::object_t>(
                        _selection)["origin"][0] < -8 ||
                    std::get<nlohmann::json::object_t>(
                        _selection)["origin"][0] > 8 ||
                    std::get<nlohmann::json::object_t>(
                        _selection)["origin"][1] < 0 ||
                    std::get<nlohmann::json::object_t>(
                        _selection)["origin"][1] > 16 ||
                    std::get<nlohmann::json::object_t>(
                        _selection)["origin"][2] < -8 ||
                    std::get<nlohmann::json::object_t>(
                        _selection)["origin"][2] > 8) {
                    spdlog::error(
                        "{} - Minimal position of the bounds of the selection "
                        "box. origin is specified as [x, y, z] and must be in "
                        "the range (-8, 0, -8) to (8, 16, 8), inclusive",
                        id);
                    exit(EXIT_FAILURE);
                }

                int origin_1 =
                    std::get<nlohmann::json::object_t>(_selection)["origin"][0];
                int size_1 =
                    std::get<nlohmann::json::object_t>(_selection)["size"][0];
                int origin_2 =
                    std::get<nlohmann::json::object_t>(_selection)["origin"][1];
                int size_2 =
                    std::get<nlohmann::json::object_t>(_selection)["size"][1];
                int origin_3 =
                    std::get<nlohmann::json::object_t>(_selection)["origin"][2];
                int size_3 =
                    std::get<nlohmann::json::object_t>(_selection)["size"][2];

                if ((origin_1 + size_1) < -8 || (origin_1 + size_1) > 8) {
                    spdlog::error(
                        "{} - Size of each side of the selection box. Size is "
                        "specified as [x, y, z]. origin + size must be in the "
                        "range (-8, 0, -8) to (8, 16, 8), inclusive",
                        id);
                    exit(EXIT_FAILURE);
                }

                if ((origin_2 + size_2) < 0 || (origin_2 + size_2) > 16) {
                    spdlog::error(
                        "{} - Size of each side of the selection box. Size is "
                        "specified as [x, y, z]. origin + size must be in the "
                        "range (-8, 0, -8) to (8, 16, 8), inclusive",
                        id);
                    exit(EXIT_FAILURE);
                }

                if ((origin_3 + size_3) < -8 || (origin_3 + size_3) > 8) {
                    spdlog::error(
                        "{} - Size of each side of the selection box. Size is "
                        "specified as [x, y, z]. origin + size must be in the "
                        "range (-8, 0, -8) to (8, 16, 8), inclusive",
                        id);
                    exit(EXIT_FAILURE);
                }

                j["minecraft:block"]["components"]["minecraft:selection_box"] =
                    std::get<nlohmann::json::object_t>(_selection);
            } catch (const std::exception& e) {
                e;
            }
        } else {
            j["minecraft:block"]["components"]["minecraft:selection_box"] =
                false;
        }

        if (_tab != "")
            j["minecraft:block"]["description"]["menu_category"]["category"] =
                _tab;

        if (_category != "")
            j["minecraft:block"]["description"]["menu_category"]["group"] =
                _category;

        return j;
    }
};

#endif