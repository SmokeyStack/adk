#pragma once

#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "json.hpp"
#include "shared_construct.h"

namespace adk {
	enum class BlockAllowedFaces {
		UP,
		DOWN,
		NORTH,
		SOUTH,
		EAST,
		WEST,
		SIDE,
		ALL
	};

	/**
	 * @brief Get the Allowed Faces object
	 *
	 * @param category enum BlockAllowedFaces
	 *
	 * @return std::string
	 */
	inline std::string GetBlockAllowedFaces(adk::BlockAllowedFaces value) {
		switch (value) {
		case adk::BlockAllowedFaces::UP:
			return "up";
		case adk::BlockAllowedFaces::DOWN:
			return "down";
		case adk::BlockAllowedFaces::NORTH:
			return "north";
		case adk::BlockAllowedFaces::SOUTH:
			return "south";
		case adk::BlockAllowedFaces::EAST:
			return "east";
		case adk::BlockAllowedFaces::WEST:
			return "west";
		case adk::BlockAllowedFaces::SIDE:
			return "side";
		case adk::BlockAllowedFaces::ALL:
			return "all";
		default:
			return "Error";
		}
	}

	namespace {
		/**
		 * @brief Makes your block into a custom crafting table which enables the crafting table UI and the ability to craft recipes.
		 *
		 * @param crafting_tags Defines the tags recipes should define to be crafted on this table.
		 * Limited to 64 tags.
		 * Each tag is limited to 64 characters.
		 *
		 * @param table_name Specifies the language file key that maps to what text will be displayed in the UI of this table.
		 * If the string given can not be resolved as a loc string, the raw string given will be displayed.
		 * If this field is omitted, the name displayed will default to the name specified in the "display_name" component.
		 * If this block has no "display_name" component, the name displayed will default to the name of the block.
		 */
		struct BlockCraftingTable {
			std::vector<std::string> crafting_tags;
			std::string table_name;
		};

		void to_json(nlohmann::json& j, const BlockCraftingTable& p) {
			j.update({ {"crafting_tags", p.crafting_tags} });

			if (!p.table_name.empty()) j.update({ {"table_name", p.table_name} });
		}

		/**
		 * @brief Sets rules for under what conditions the block can be placed or survive.
		 *
		 * @param allowed_faces List of any of the following strings describing which face(s) this block can be placed on: up, down, north, south, east, west, side, all.
		 * Limited to 6 faces.
		 *
		 * @param block_filter List of blocks that this block can be placed against in the allowed_faces direction.
		 * Limited to 64 blocks.
		 * Each block in this list can either be specified as a String (block name) or as a BlockDescriptor.
		 */
		struct BlockPlacementFilter {
			std::vector<BlockAllowedFaces> allowed_faces;
			std::vector<std::variant<std::string, BlockDescriptor>> block_filter;
		};

		void to_json(nlohmann::json& j, const BlockPlacementFilter& p) {
			std::vector<std::string> allowed_faces;
			for (BlockAllowedFaces var : p.allowed_faces) {
				allowed_faces.push_back(GetBlockAllowedFaces(var));
			}
			nlohmann::json j2 = nlohmann::json::array();
			for (auto& entries : p.block_filter) {
				if (std::holds_alternative<std::string>(entries)) {
					j2.push_back(std::get<std::string>(entries));
				}
				else {
					j2.push_back(std::get<BlockDescriptor>(entries));
				}
			}

			j = nlohmann::json{ {"allowed_faces", allowed_faces}, {"block_filter", j2} };
		}
	}

	/**
	 * @brief Represents block properties such as destroy speed, loot, etc
	 */
	class BlockProperty {
	public:
		/**
		 * @brief Sets the "light_dampening" component
		 *
		 * @param value The amount that light will be dampened when it passes through the block, in a range (0-15).
		 * Higher value means the light will be dampened more.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetLightDampening(int value) {
			this->light_dampening_ = value;

			return *this;
		}

		/**
		 * @brief Sets the "crafting_table" component
		 *
		 * @param value BlockCraftingTable struct
		 *
		 * @return nlohmann::json::object_t
		*/
		BlockProperty SetCrafting(BlockCraftingTable value) {
			this->crafting_ = value;

			return *this;
		}

		/**
		 * @brief Sets the "destructible_by_explosion" component
		 *
		 * @param value Describes how resistant the block is to explosion.
		 * Greater values mean the block is less likely to break when near an explosion (or has higher resistance to explosions).
		 * The scale will be different for different explosion power levels.
		 * A negative value or 0 means it will easily explode; larger numbers increase level of resistance.
		 *
		 * @return BlockProperty
		*/
		BlockProperty SetDestructibleByExplosion(
			std::variant<bool, double> value) {
			if (std::get_if<bool>(&value)) {
				this->explosion_ = std::get<bool>(value);

				return *this;
			}

			this->explosion_ = std::get<double>(value);

			return *this;
		}

		/**
		 * @brief Set the "destructible_by_mining" component
		 *
		 * @param value Sets the number of seconds it takes to destroy the block with base equipment.
		 * Greater numbers result in greater mining times.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetDestructibleByMining(std::variant<bool, double> value) {
			if (std::get_if<bool>(&value)) {
				this->mining_ = std::get<bool>(value);

				return *this;
			}

			this->mining_ = std::get<double>(value);

			return *this;
		}

		/**
		 * @brief Set the "display_name" component
		 *
		 * @param value Specifies the language file key that maps to what text will be displayed when you hover over the block in your inventory and hotbar.
		 * If the string given can not be resolved as a loc string, the raw string given will be displayed.
		 * If this component is omitted, the name of the block will be used as the display name.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetDisplayName(std::string value) {
			this->display_name_ = value;

			return *this;
		}

		/**
		 * @brief Sets the "flammable" component
		 *
		 * @param value Describes the flammable properties for this block.
		 * If set to true, default values are used.
		 * If set to false, or if this component is omitted, the block will not be able to catch on fire naturally from neighbors, but it can still be directly ignited.
		 *
		 * @return BlockProperty
		*/
		BlockProperty SetFlammable(bool value) {
			this->flammable_ = value;

			return *this;
		}

		/**
		 * @brief Sets the "flammable" component
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
		BlockProperty SetFlammable(int catch_chance, int destroy_chance) {
			this->flammable_ = std::make_pair(catch_chance, destroy_chance);

			return *this;
		}

		/**
		 * @brief Set the "friction" component
		 *
		 * @param value Describes the friction for this block in a range of (0.0-0.9).
		 * Friction affects an entity's movement speed when it travels on the block.
		 * Greater value results in more friction.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetFriction(double value) {
			this->friction_ = value;

			return *this;
		}

		/**
		 * @brief Set the "light_emission" component
		 *
		 * @param value The amount of light this block will emit in a range (0-15).
		 * Higher value means more light will be emitted.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetLightEmission(int value) {
			this->light_emission_ = value;

			return *this;
		}

		/**
		 * @brief Set the "loot" component
		 *
		 * @param value The path to the loot table, relative to the behavior pack.
		 * Path string is limited to 256 characters.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetLoot(std::string value) {
			this->loot_ = value;

			return *this;
		}

		/**
		 * @brief Set the "map_color" component
		 *
		 * @param value Sets the color of the block when rendered to a map.
		 * The color is represented as a hex value in the format "#RRGGBB".
		 * May also be expressed as an array of [R, G, B] from 0 to 255.
		 * If this component is omitted, the block will not show up on the map.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetMapColor(std::string value) {
			this->map_color_ = value;

			return *this;
		}

		/**
		 * @brief Set the "map_color" component
		 *
		 * @param value Sets the color of the block when rendered to a map.
		 * The color is represented as a hex value in the format "#RRGGBB".
		 * May also be expressed as an array of [R, G, B] from 0 to 255.
		 * If this component is omitted, the block will not show up on the map.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetMapColor(std::vector<int> value) {
			this->map_color_ = value;

			return *this;
		}

		/**
		 * @brief Creates the "translation" key for the "transformation" component
		 * Transformed geometries still have the same restrictions that non-transformed geometries have such as a maximum size of 30/16 units.
		 *
		 * @param value Vector of rotation in degrees
		 *
		 * @return BlockProperty
		*/
		BlockProperty SetTranslation(std::vector<double> value) {
			this->translation_ = translation_;

			return *this;
		}

		/**
		 * @brief Creates the "scale" key for the "transformation" component
		 * Transformed geometries still have the same restrictions that non-transformed geometries have such as a maximum size of 30/16 units.
		 *
		 * @param value Vector of scale in degrees
		 *
		 * @return BlockProperty
		*/
		BlockProperty SetScale(std::vector<double> value) {
			this->scale_ = scale_;

			return *this;
		}

		/**
		 * @brief Creates the "rotation" key for the "transformation" component
		 * Transformed geometries still have the same restrictions that non-transformed geometries have such as a maximum size of 30/16 units.
		 *
		 * @param value Vector of rotation in degrees
		 *
		 * @param id Identifier of the block
		 *
		 * @return BlockProperty
		*/
		BlockProperty SetRotation(std::vector<int> rotation) {
			this->rotation_ = rotation;
			return *this;
		}

		/**
		 * @brief Set the "collision_box" component
		 *
		 * @param value Defines the area of the block that collides with entities.
		 * If set to true, default values are used.
		 * If set to false, the block's collision with entities is disabled.
		 * If this component is omitted, default values are used.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetBoxCollision(bool value) {
			this->box_collision_ = value;

			return *this;
		}

		/**
		 * @brief Set the "collision_box" component
		 *
		 * @param origin Minimal position of the bounds of the collision box.
		 * "origin" is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the collision box.
		 * Size is specified as [x, y, z].
		 * "origin" + "size" must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetBoxCollision(std::vector<int> origin, std::vector<int> size) {
			this->box_collision_ = std::make_pair(origin, size);

			return *this;
		}

		/**
		 * @brief Set the "selection_box" component
		 *
		 * @param value Defines the area of the block that is selected by the player's cursor.
		 * If set to true, default values are used.
		 * If set to false, this block is not selectable by the player's cursor.
		 * If this component is omitted, default values are used.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetBoxSelection(bool value) {
			this->box_selection_ = value;

			return *this;
		}

		/**
		 * @brief Set the "selection_box" component
		 *
		 * @param origin Minimal position of the bounds of the collision box.
		 * "origin" is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the collision box.
		 * Size is specified as [x, y, z].
		 * "origin" + "size" must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetBoxSelection(std::vector<int> origin, std::vector<int> size) {
			this->box_selection_ = std::make_pair(origin, size);;

			return *this;
		}

		/**
		 * @brief Sets the "placement_filter" component
		 *
		 * @param value Sets rules for under what conditions the block can be placed/survive
		 *
		 * @return BlockProperty
		*/
		BlockProperty SetBlockPlacementFilter(BlockPlacementFilter value) {
			this->placement_filter_ = value;

			return *this;
		}

		/**
		 * @brief Gets the "light_dampening" value
		 *
		 * @return int
		 */
		int GetLightDampening() const { return light_dampening_; }

		/**
		 * @brief Gets the "crafting_table" component
		 *
		 * @return std::vector<std::string>
		*/
		BlockCraftingTable GetCrafting() const { return crafting_; }

		/**
		 * @brief Gets the "destructible_by_explosion" component
		 *
		 * @return std::variant<bool, double>
		 */
		std::variant<bool, double> GetDestructibleByExplosion() const { return explosion_; }

		/**
		 * @brief Gets the "destructible_by_mining" component
		 *
		 * @return std::variant<bool, double>
		 */
		std::variant<bool, double> GetDestructibleByMining() const { return mining_; }

		/**
		 * @brief Gets the "display_name" component
		 *
		 * @return std::string
		 */
		std::string GetDisplayName() const { return display_name_; }

		/**
		 * @brief Gets the "flamamble" component
		 *
		 * @return std::variant<bool, std::pair<int, int>>
		 */
		std::variant<bool, std::pair<int, int>> GetFlamamble() const { return flammable_; }

		/**
		 * @brief Gets the "friction" component
		 *
		 * @return double
		 */
		double GetFriction() const { return friction_; }

		/**
		 * @brief Gets the "light_emission" component
		 *
		 * @return int
		 */
		int GetLightEmission() const { return light_emission_; }

		/**
		 * @brief Gets the "loot" component
		 *
		 * @return std::string
		 */
		std::string GetLoot() const { return loot_; }

		/**
		 * @brief Gets the "map_color" component
		 *
		 * @return std::string
		 */
		std::variant<std::string, std::vector<int>> GetMapColor() const { return map_color_; }

		/**
		 * @brief Gets the "translation" field of "transformation" component
		 *
		 * @return std::vector<int>
		 */
		std::vector<double> GetTranslation() const { return translation_; }

		/**
		 * @brief Gets the "scale" field of "transformation" component
		 *
		 * @return std::vector<int>
		 */
		std::vector<double> GetScale() const { return scale_; }

		/**
		 * @brief Gets the "rotation" field of "transformation" component
		 *
		 * @return std::vector<int>
		 */
		std::vector<int> GetRotation() const { return rotation_; }

		/**
		 * @brief Gets the "collision_box" component
		 *
		 * @return std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
		 */
		std::variant<bool, std::pair<std::vector<int>, std::vector<int>>> GetBoxCollision() const {
			return box_collision_;
		}

		/**
		 * @brief Gets the "selection_box" component
		 *
		 * @return std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
		 */
		std::variant<bool, std::pair<std::vector<int>, std::vector<int>>> GetBoxSelection() const {
			return box_selection_;
		}

		/**
		 * @brief Gets the "placement_filter" component
		 *
		 * @return std::variant<BlockPlacementFilterStates, BlockPlacementFilterTags>
		 */
		BlockPlacementFilter GetPlacementFilter() const {
			return placement_filter_;
		}

		/**
		 * @brief Sets the "tags" component
		 *
		 * @param value The "tags" component determines which tags are attached to an item.
		 *
		 * @return BlockProperty
		*/
		BlockProperty SetTags(std::vector<std::string> value) {
			this->tags_ = value;

			return *this;
		}

		/**
		 * @brief Gets the "tags" component
		 *
		 * @return std::vector<std::string>
		*/
		std::vector<std::string> GetTags() const { return tags_; }

		/**
		 * @brief Sets the "custom_components" component
		 *
		 * @param value Array of custom components
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetCustomComponents(std::vector<std::string> value) {
			this->custom_components_ = value;

			return *this;
		}

		/**
		 * @brief Gets the "custom_components" component
		 *
		 * @return std::vector<std::string>
		 */
		std::vector<std::string> GetCustomComponents() const { return custom_components_; }

		/**
		 * @brief Sets the "tick" component
		 *
		 * @param minimum_tick Minimum number of ticks before the block can be ticked
		 *
		 * @param maximum_tick Maximum number of ticks before the block can be ticked
		 *
		 * @param loop If the block should loop the tick
		 *
		 * @return BlockProperty
		 */
		BlockProperty SetTick(int minimum_tick, int maximum_tick, bool loop = true) {
			this->tick_ = std::make_tuple(minimum_tick, maximum_tick, loop);

			return *this;
		}

		/**
		 * @brief Gets the "tick" component
		 *
		 * @return std::tuple<int, int, bool>
		 */
		std::optional<std::tuple<int, int, bool>> GetTick() const { return tick_; }
	private:
		int light_dampening_ = 15;
		BlockCraftingTable crafting_;
		std::variant<bool, double> explosion_ = true;
		std::variant<bool, double> mining_ = true;
		std::string display_name_;
		std::variant<bool, std::pair<int, int>> flammable_ = true;
		double friction_ = 0.4;
		int light_emission_;
		std::string loot_;
		std::variant<std::string, std::vector<int>> map_color_;
		std::vector<int> rotation_{ 0, 0, 0 };
		std::vector<double> scale_{ 0, 0, 0 };
		std::vector<double> translation_{ 0, 0, 0 };
		std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
			box_collision_ = true;
		std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
			box_selection_ = true;
		BlockPlacementFilter placement_filter_;
		std::vector<std::string> tags_;
		std::vector<std::string> custom_components_;
		std::optional<std::tuple<int, int, bool>> tick_;
	};
} // namespace adk