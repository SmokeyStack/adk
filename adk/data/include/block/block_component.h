#pragma once

#include <string>
#include <variant>
#include <vector>

#include "json.hpp"
#include "utility/logger.h"

namespace adk {
	/**
	 * @brief Creates the json components
	 */
	class BlockComponent {
	public:
		/**
		 * @brief Creates the "light_dampening" component
		 *
		 * @param value The amount that light will be dampened when it passes through the block, in a range (0-15).
		 * Higher value means the light will be dampened more.
		 *
		 * @param id Identifier of the block
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t LightDampening(int value, std::string id) {
			if (value > 15 || value < 0) {
				adk::log::error("{} - LightDampening can only be in range (0-15)",
					id);
				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t output = { {"minecraft:light_dampening", value} };

			return output;
		}

		/**
		 * @brief Creates the "crafting_table" component
		 *
		 * @param j BlockCraftingTable struct
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Crafting(nlohmann::json j) {
			nlohmann::json::object_t output = { {"minecraft:crafting_table",{j} } };

			return output;
		}

		/**
		 * @brief Creates the "destructible_by_explosion" component
		 *
		 * @param value Describes how resistant the block is to explosion.
		 * Greater values mean the block is less likely to break when near an explosion (or has higher resistance to explosions).
		 * The scale will be different for different explosion power levels.
		 * A negative value or 0 means it will easily explode; larger numbers increase level of resistance.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t DestructibleByExplosion(
			std::variant<bool, double> value) {
			nlohmann::json::object_t output;

			if (std::get_if<bool>(&value))
				output = {
					{"minecraft:destructible_by_explosion", std::get<bool>(value)} };
			else
				output = { {"minecraft:destructible_by_explosion",
						 {{"explosion_resistance", std::get<double>(value)}}} };

			return output;
		}

		/**
		 * @brief Creates the "destructible_by_mining" component
		 *
		 * @param value Sets the number of seconds it takes to destroy the block with base equipment.
		 * Greater numbers result in greater mining times.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t DestructibleByMining(
			std::variant<bool, double> value) {
			nlohmann::json::object_t output;

			if (std::get_if<bool>(&value))
				output = {
					{"minecraft:destructible_by_mining", std::get<bool>(value)} };
			else
				output = { {"minecraft:destructible_by_mining",
						 {{"seconds_to_destroy", std::get<double>(value)}}} };

			return output;
		}

		/**
		 * @brief Creates the "display_name" component
		 *
		 * @param value Specifies the language file key that maps to what text will be displayed when you hover over the block in your inventory and hotbar.
		 * If the string given can not be resolved as a loc string, the raw string given will be displayed.
		 * If this component is omitted, the name of the block will be used as the display name.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t DisplayName(std::string value) {
			nlohmann::json::object_t output = { {"minecraft:display_name", value} };

			return output;
		}

		/**
		 * @brief Creates the "flammable" component
		 *
		 * @param value Describes the flammable properties for this block.
		 * If set to true, default values are used.
		 * If set to false, or if this component is omitted, the block will not be able to catch on fire naturally from neighbors, but it can still be directly ignited.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Flammable(bool value) {
			nlohmann::json::object_t output = {
					{"minecraft:flammable", value} };

			return output;
		}

		/**
		 * @brief Creates the "flammable" component
		 *
		 * @param catch_chance A modifier affecting the chance that this block will catch flame when next to a fire.
		 * Values are greater than or equal to 0, with a higher number meaning more likely to catch on fire.
		 * For a "catch_chance_modifier" greater than 0, the fire will continue to burn until the block is destroyed (or it will burn forever if the "destroy_chance_modifier" is 0).
		 * If the "catch_chance_modifier" is 0, and the block is directly ignited, the fire will eventually burn out without destroying the block (or it will have a chance to be destroyed if "destroy_chance_modifier" is greater than 0).
		 * The default value of 5 is the same as that of Planks.
		 *
		 * @param destroy_chance A modifier affecting the chance that this block will be destroyed by flames when on fire.
		 * Values are greater than or equal to 0, with a higher number meaning more likely to be destroyed by fire.
		 * For a "destroy_chance_modifier" of 0, the block will never be destroyed by fire, and the fire will burn forever if the "catch_chance_modifier" is greater than 0.
		 * The default value of 20 is the same as that of Planks.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Flammable(int catch_chance, int destroy_chance) {
			nlohmann::json::object_t output = {
				{"minecraft:flammable",
				 {{"catch_chance_modifier", catch_chance},
				  {"destroy_chance_modifier", destroy_chance}}} };

			return output;
		}

		/**
		 * @brief Creates the "friction" component
		 *
		 * @param value Describes the friction for this block in a range of (0.0-0.9).
		 * Friction affects an entity's movement speed when it travels on the block.
		 * Greater value results in more friction.
		 *
		 * @param id Identifier of the block
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Friction(double value, std::string id) {
			if (value > 0.9 || value < 0.0) {
				adk::log::error("{} - Friction can only be in range (0.0-0.9)", id);
				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t output = { {"minecraft:friction", value} };

			return output;
		}

		/**
		 * @brief Creates the "light_emission" component
		 *
		 * @param value The amount of light this block will emit in a range (0-15).
		 * Higher value means more light will be emitted.
		 *
		 * @param id Identifier of the block
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t LightEmission(int value, std::string id) {
			if (value > 15 || value < 0) {
				adk::log::error("{} - BlockLightFilter can only be in range (0-15)",
					id);
				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t output = { {"minecraft:light_emission", value} };

			return output;
		}

		/**
		 * @brief Creates the "loot" component
		 *
		 * @param value The path to the loot table, relative to the behavior pack.
		 * Path string is limited to 256 characters.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Loot(std::string value) {
			nlohmann::json::object_t output = { {"minecraft:loot", value} };

			return output;
		}

		/**
		 * @brief Creates the "map_color" component
		 *
		 * @param value Sets the color of the block when rendered to a map.
		 * The color is represented as a hex value in the format "#RRGGBB".
		 * May also be expressed as an array of [R, G, B] from 0 to 255.
		 * If this component is omitted, the block will not show up on the map.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t MapColor(std::string value) {
			nlohmann::json::object_t output = { {"minecraft:map_color", value} };

			return output;
		}

		/**
		 * @brief Creates the "map_color" component
		 *
		 * @param value Sets the color of the block when rendered to a map.
		 * The color is represented as a hex value in the format "#RRGGBB".
		 * May also be expressed as an array of [R, G, B] from 0 to 255.
		 * If this component is omitted, the block will not show up on the map.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t MapColor(std::vector<int> value) {
			nlohmann::json::object_t output = { {"minecraft:map_color", value} };

			return output;
		}

		/**
		 * @brief Creates the "rotation" key for the "transformation" component
		 * Transformed geometries still have the same restrictions that non-transformed geometries have such as a maximum size of 30/16 units.
		 *
		 * @param value Vector of rotation in degrees
		 *
		 * @param id Identifier of the block
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Rotation(std::vector<int> value, std::string id) {
			for (auto const& entry : value) {
				if (entry % 90 != 0) {
					adk::log::error("{} - Rotation can only be factors of 90", id);
					exit(EXIT_FAILURE);
				}
			}

			nlohmann::json::object_t output = {
				{"minecraft:transformation", {{"rotation", value}}} };

			return output;
		}

		/**
		 * @brief Creates the "translation" key for the "transformation" component
		 * Transformed geometries still have the same restrictions that non-transformed geometries have such as a maximum size of 30/16 units.
		 *
		 * @param value Vector of translation in degrees
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Translation(std::vector<double> value) {
			nlohmann::json::object_t output = {
				{"minecraft:transformation", {{"translation", value}}} };

			return output;
		}

		/**
		 * @brief Creates the "scale" key for the "transformation" component
		 * Transformed geometries still have the same restrictions that non-transformed geometries have such as a maximum size of 30/16 units.
		 *
		 * @param value Vector of scale in degrees
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Scale(std::vector<double> value) {
			nlohmann::json::object_t output = {
				{"minecraft:transformation", {{"scale", value}}} };

			return output;
		}

		/**
		 * @brief Creates the "collision_box" component
		 *
		 * @param value Defines the area of the block that collides with entities.
		 * If set to true, default values are used.
		 * If set to false, the block's collision with entities is disabled.
		 * If this component is omitted, default values are used.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t BoxCollision(bool value) {
			nlohmann::json::object_t output = { {"minecraft:collision_box", value} };

			return output;
		}

		/**
		 * @brief Creates the "collision_box" component
		 *
		 * @param origin Minimal position of the bounds of the collision box.
		 * "origin" is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the collision box.
		 * Size is specified as [x, y, z].
		 * "origin" + "size" must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param id Identifier of the block
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t BoxCollision(std::vector<int> origin, std::vector<int> size, std::string id) {
			EnsureValidity(origin, size, "collision", id);

			nlohmann::json::object_t output = { {"minecraft:collision_box",{{"origin",origin},{"size", size}}} };

			return output;
		}

		/**
		 * @brief Creates the "selection_box" component
		 *
		 * @param value Defines the area of the block that is selected by the player's cursor.
		 * If set to true, default values are used.
		 * If set to false, this block is not selectable by the player's cursor.
		 * If this component is omitted, default values are used.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t BoxSelection(bool value) {
			nlohmann::json::object_t output = { {"minecraft:selection_box", value} };

			return output;
		}

		/**
		 * @brief Creates the "selection_box" component
		 *
		 * @param origin Minimal position of the bounds of the collision box.
		 * "origin" is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the collision box.
		 * Size is specified as [x, y, z].
		 * "origin" + "size" must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param id Identifier of the block
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t BoxSelection(std::vector<int> origin, std::vector<int> size, std::string id) {
			EnsureValidity(origin, size, "selection", id);

			nlohmann::json::object_t output = { {"minecraft:selection_box",{{"origin",origin},{"size", size}}} };

			return output;
		}

		nlohmann::json::object_t PlacementFilter(nlohmann::json j) {
			nlohmann::json::object_t output = { {"minecraft:placement_filter",{{"conditions",{j}}}} };

			return output;
		}

		/**
		 * @brief Creates the "tags" component
		 *
		 * @param value An array which can contain multiple item tags.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Tags(std::vector<std::string> value) {
			nlohmann::json::object_t temp = { {"minecraft:tags", {{"tags",value}}} };

			return temp;
		}

		/**
		 * @brief Sets the "custom_components" component
		 *
		 * @param value Array of custom components
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t CustomComponents(std::vector<std::string> value) {
			nlohmann::json::object_t temp = { {"minecraft:custom_components",value} };

			return temp;
		}

		/**
		 * @brief Sets the "tick" component
		 *
		 * @param minimum_tick Minimum number of ticks before the block can be ticked
		 *
		 * @param maximum_tick Maximum number of ticks before the block can be ticked
		 *
		 * @param loop If the block should loop the tick
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t Tick(int minimum_tick, int maximum_tick, bool loop = true) {
			nlohmann::json::object_t temp = { {"minecraft:tick",{{"interval_range", {minimum_tick, maximum_tick}},{"looping", loop}}} };

			return temp;
		}
	protected:
		/**
		 * @brief Ensure the collision_box and selection_box is valid
		 *
		 * @param component_check The vectors of origin and size
		 *
		 * @param component Used to log collision or selection
		 *
		 * @param id Identifier of block
		 *
		 * @return validity
		 */
		void EnsureValidity(std::vector<int> origin, std::vector<int> size, std::string component, std::string id) {
			if (origin.at(0) < -8 ||
				origin.at(0) > 8 ||
				origin.at(1) < 0 ||
				origin.at(1) > 16 ||
				origin.at(2) < -8 ||
				origin.at(2) > 8) {
				adk::log::error(
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

			int origin_1 = origin.at(0);
			int size_1 = size.at(0);
			int origin_2 = origin.at(1);
			int size_2 = size.at(1);
			int origin_3 = origin.at(2);
			int size_3 = size.at(2);

			if ((origin_1 + size_1) < -8 || (origin_1 + size_1) > 8) {
				adk::log::error(
					"{} - Size of each side of the {} box. Size is "
					"specified as [x, y, z]. \"origin\" + \"size\" must be "
					"in the range (-8, 0, -8) to (8, 16, 8), inclusive",
					id, component);
				exit(EXIT_FAILURE);
			}

			if ((origin_2 + size_2) < 0 || (origin_2 + size_2) > 16) {
				adk::log::error(
					"{} - Size of each side of the {} box. Size is "
					"specified as [x, y, z]. \"origin\" + \"size\" must be "
					"in the range (-8, 0, -8) to (8, 16, 8), inclusive",
					id, component);
				exit(EXIT_FAILURE);
			}

			if ((origin_3 + size_3) < -8 || (origin_3 + size_3) > 8) {
				adk::log::error(
					"{} - Size of each side of the {} box. Size is "
					"specified as [x, y, z]. \"origin\" + \"size\" must be "
					"in the range (-8, 0, -8) to (8, 16, 8), inclusive",
					id, component);
				exit(EXIT_FAILURE);
			}
		}
	};
} // namespace adk