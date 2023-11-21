#ifndef BLOCKCOMPONENT_H
#define BLOCKCOMPONENT_H

#include <spdlog/spdlog.h>

#include <string>
#include <variant>
#include <vector>

#include "BlockCategory.h"
#include "json.hpp"

/**
 * @brief Creates the json components
 *
 */
class BlockComponent {
protected:
	/**
	 * @brief Ensure the collision_box and selection_box is valid
	 *
	 * @param component_check The vectors of origin and size
	 * @param component Used to log collision or selection
	 * @param id Identifier of block
	 * @return true
	 * @return false
	 */
	void ensureValidity(
		std::pair<std::vector<int>, std::vector<int>> component_check,
		std::string component, std::string id) {
		if (component_check.first.at(0) < -8 ||
			component_check.first.at(0) > 8 ||
			component_check.first.at(1) < 0 ||
			component_check.first.at(1) > 16 ||
			component_check.first.at(2) < -8 ||
			component_check.first.at(2) > 8) {
			spdlog::get("Blocks/Items")
				->error(
					"{} - Minimal position of the bounds of the {} box. "
					"\"origin\" "
					"is "
					"specified as [x, y, z] and must be in the range (-8, "
					"0, "
					"-8) "
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
			spdlog::get("Blocks/Items")
				->error(
					"{} - Size of each side of the {} box. Size is "
					"specified as [x, y, z]. \"origin\" + \"size\" must be "
					"in the range (-8, 0, -8) to (8, 16, 8), inclusive",
					id, component);
			exit(EXIT_FAILURE);
		}

		if ((origin_2 + size_2) < 0 || (origin_2 + size_2) > 16) {
			spdlog::get("Blocks/Items")
				->error(
					"{} - Size of each side of the {} box. Size is "
					"specified as [x, y, z]. \"origin\" + \"size\" must be "
					"in the range (-8, 0, -8) to (8, 16, 8), inclusive",
					id, component);
			exit(EXIT_FAILURE);
		}

		if ((origin_3 + size_3) < -8 || (origin_3 + size_3) > 8) {
			spdlog::get("Blocks/Items")
				->error(
					"{} - Size of each side of the {} box. Size is "
					"specified as [x, y, z]. \"origin\" + \"size\" must be "
					"in the range (-8, 0, -8) to (8, 16, 8), inclusive",
					id, component);
			exit(EXIT_FAILURE);
		}
	}

public:
	/**
	 * @brief Creates the "light_dampening" component
	 *
	 * @param value The amount that light will be dampened when it passes
	 through the block, in a range (0-15). Higher value means the light will be
	 dampened more
	 * @param id Identifier of the block
	 * @return nlohmann::json::object_t
	 */
	nlohmann::json::object_t blockLightFilter(int value, std::string id) {
		if (value > 15 || value < 0) {
			spdlog::get("Blocks/Items")
				->error("{} - BlockLightFilter can only be in range (0-15)",
					id);
			exit(EXIT_FAILURE);
		}

		nlohmann::json::object_t temp = { {"minecraft:light_dampening", value} };

		return temp;
	}

	nlohmann::json::object_t crafting(
		std::pair<std::vector<std::string>, std::string> value) {
		nlohmann::json::object_t temp = {
			{"minecraft:crafting_table",
			 {{"crafting_tags", value.first}, {"table_name", value.second}}} };

		return temp;
	}

	nlohmann::json::object_t destructibleByExplosion(
		std::variant<bool, double> value) {
		nlohmann::json::object_t temp;

		if (std::get_if<bool>(&value))
			temp = {
				{"minecraft:destructible_by_explosion", std::get<bool>(value)} };
		else
			temp = { {"minecraft:destructible_by_explosion",
					 {{"explosion_resistance", std::get<double>(value)}}} };

		return temp;
	}

	nlohmann::json::object_t destructibleByMining(
		std::variant<bool, double> value) {
		nlohmann::json::object_t temp;

		if (std::get_if<bool>(&value))
			temp = {
				{"minecraft:destructible_by_mining", std::get<bool>(value)} };
		else
			temp = { {"minecraft:destructible_by_mining",
					 {{"seconds_to_destroy", std::get<double>(value)}}} };

		return temp;
	}

	nlohmann::json::object_t displayName(std::string value) {
		nlohmann::json::object_t temp = { {"display_name", value} };

		return temp;
	}

	nlohmann::json::object_t flammable(std::pair<int, int> value) {
		nlohmann::json::object_t temp = {
			{"minecraft:flammable",
			 {{"catch_chance_modifier", value.first},
			  {"destroy_chance_modifier", value.second}}} };

		return temp;
	}

	nlohmann::json::object_t friction(double value, std::string id) {
		if (value > 0.9 || value < 0.0) {
			spdlog::get("Blocks/Items")
				->error("{} - Friction can only be in range (0.0-0.9)", id);
			exit(EXIT_FAILURE);
		}

		nlohmann::json::object_t temp = { {"minecraft:friction", value} };

		return temp;
	}

	nlohmann::json::object_t lightEmission(int value, std::string id) {
		if (value > 15 || value < 0) {
			spdlog::get("Blocks/Items")
				->error("{} - BlockLightFilter can only be in range (0-15)",
					id);
			exit(EXIT_FAILURE);
		}

		nlohmann::json::object_t temp = { {"minecraft:light_emission", value} };

		return temp;
	}

	nlohmann::json::object_t loot(std::string value) {
		nlohmann::json::object_t temp = { {"minecraft:loot", value} };

		return temp;
	}

	nlohmann::json::object_t color(std::string value) {
		nlohmann::json::object_t temp = { {"minecraft:map_color", value} };

		return temp;
	}

	nlohmann::json::object_t rotation(std::vector<int> value, std::string id) {
		for (auto const& entry : value) {
			if (entry % 90 != 0) {
				spdlog::get("Blocks/Items")
					->error("{} - Rotation can only be factors of 90", id);
				exit(EXIT_FAILURE);
			}
		}

		nlohmann::json::object_t temp = {
			{"minecraft:transformation", {{"rotation", value}}} };

		return temp;
	}

	nlohmann::json::object_t translation(std::vector<double> value) {
		nlohmann::json::object_t temp = {
			{"minecraft:transformation", {{"translation", value}}} };

		return temp;
	}

	nlohmann::json::object_t scale(std::vector<double> value) {
		nlohmann::json::object_t temp = {
			{"minecraft:transformation", {{"scale", value}}} };

		return temp;
	}

	nlohmann::json::object_t collision(
		std::variant<bool, std::pair<std::vector<int>, std::vector<int>>> value,
		std::string id) {
		nlohmann::json::object_t temp;

		if (std::get_if<bool>(&value))
			temp = { {"minecraft:collision_box", std::get<bool>(value)} };
		else {
			ensureValidity(
				std::get<std::pair<std::vector<int>, std::vector<int>>>(value),
				"collision", id);

			temp = { {"minecraft:collision_box",
					 {{"origin",
					   std::get<std::pair<std::vector<int>, std::vector<int>>>(
						   value)
						   .first},
					  {"size",
					   std::get<std::pair<std::vector<int>, std::vector<int>>>(
						   value)
						   .second}}} };
		}

		return temp;
	}

	nlohmann::json::object_t selection(
		std::variant<bool, std::pair<std::vector<int>, std::vector<int>>> value,
		std::string id) {
		nlohmann::json::object_t temp;

		if (std::get_if<bool>(&value))
			temp = { {"minecraft:selection_box", std::get<bool>(value)} };
		else {
			ensureValidity(
				std::get<std::pair<std::vector<int>, std::vector<int>>>(value),
				"selection", id);

			temp = { {"minecraft:selection_box",
					 {{"origin",
					   std::get<std::pair<std::vector<int>, std::vector<int>>>(
						   value)
						   .first},
					  {"size",
					   std::get<std::pair<std::vector<int>, std::vector<int>>>(
						   value)
						   .second}}} };
		}

		return temp;
	}

	nlohmann::json::object_t creativeMenu(
		std::pair<std::string, std::string> value) {
		nlohmann::json::object_t temp = {
			{"menu_category", {{"category", value.first}}} };

		if (!value.second.empty())
			temp["menu_category"].update({ {"group", value.second} });

		return temp;
	}
};

#endif