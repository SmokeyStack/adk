#pragma once

#include <optional>
#include <string>
#include <variant>
#include <vector>

#include "json.hpp"
#include "shared_construct.h"

namespace adk {
	/**
	 * @brief Represents the category in Creative Menu
	 */
	enum class CreativeCategory {
		COMMANDS,
		CONSTRUCTION,
		EQUIPMENT,
		ITEMS,
		NATURE,
		NONE
	};
	/**
	 * @brief Represents the groups in Creative Menu
	 */
	enum class CreativeGroup {
		ANVIL,
		ARROW,
		AXE,
		BANNER,
		BANNERPATTERN,
		BED,
		BOAT,
		BOOTS,
		BUTTONS,
		CANDLES,
		CHALKBOARD,
		CHEST,
		CHESTBOAT,
		CHESTPLATE,
		CONCRETE,
		CONCRETEPOWDER,
		COOKEDFOOD,
		COPPER,
		CORAL,
		CORALDECORATIONS,
		CROP,
		DOOR,
		DYE,
		ENCHANTEDBOOK,
		FENCE,
		FENCEGATE,
		FIREWORK,
		FIREWORKSTARS,
		FLOWER,
		GLASS,
		GLASSPANE,
		GLAZEDTERRACOTTA,
		GOATHORN,
		GRASS,
		HANGINGSIGN,
		HELMET,
		HOE,
		HORSEARMOR,
		LEAVES,
		LEGGINGS,
		LINGERINGPOTION,
		LOG,
		MINECART,
		MISCFOOD,
		MOBEGG,
		MONSTERSTONEEGG,
		MUSHROOM,
		NETHERWARTBLOCK,
		ORE,
		PERMISSION,
		PICKAXE,
		PLANKS,
		POTION,
		POTTERYSHERDS,
		PRESSUREPLATE,
		RAIL,
		RAWFOOD,
		RECORD,
		SANDSTONE,
		SAPLING,
		SCULK,
		SEED,
		SHOVEL,
		SHULKERBOX,
		SIGN,
		SKULL,
		SLAB,
		SMITHINGTEMPLATES,
		SPLASHPOTION,
		STAINEDCLAY,
		STAIRS,
		STONE,
		STONEBRICK,
		SWORD,
		TRAPDOOR,
		WALLS,
		WOOD,
		WOOL,
		WOOLCARPET,
		NONE
	};

	/**
	 * @brief Get the Creative Category object
	 *
	 * @param category enum CreativeCategory
	 *
	 * @return std::string
	 */
	inline std::string GetCreativeCategory(adk::CreativeCategory category) {
		switch (category) {
		case adk::CreativeCategory::COMMANDS:
			return "commands";
		case adk::CreativeCategory::CONSTRUCTION:
			return "construction";
		case adk::CreativeCategory::EQUIPMENT:
			return "equipment";
		case adk::CreativeCategory::ITEMS:
			return "items";
		case adk::CreativeCategory::NATURE:
			return "nature";
		case adk::CreativeCategory::NONE:
			return "none";
		default:
			return "Error";
		}
	}

	/**
	 * @brief Get the Creative Group object
	 *
	 * @param group enum CreativeGroup
	 *
	 * @return std::string
	 */
	inline std::string GetCreativeGroup(adk::CreativeGroup group) {
		switch (group) {
		case adk::CreativeGroup::ANVIL:
			return "itemGroup.name.anvil";
		case adk::CreativeGroup::ARROW:
			return "itemGroup.name.arrow";
		case adk::CreativeGroup::AXE:
			return "itemGroup.name.axe";
		case adk::CreativeGroup::BANNER:
			return "itemGroup.name.banner";
		case adk::CreativeGroup::BANNERPATTERN:
			return "itemGroup.name.banner_pattern";
		case adk::CreativeGroup::BED:
			return "itemGroup.name.bed";
		case adk::CreativeGroup::BOAT:
			return "itemGroup.name.boat";
		case adk::CreativeGroup::BOOTS:
			return "itemGroup.name.boots";
		case adk::CreativeGroup::BUTTONS:
			return "itemGroup.name.buttons";
		case adk::CreativeGroup::CANDLES:
			return "itemGroup.name.candles";
		case adk::CreativeGroup::CHALKBOARD:
			return "itemGroup.name.chalkboard";
		case adk::CreativeGroup::CHEST:
			return "itemGroup.name.chest";
		case adk::CreativeGroup::CHESTBOAT:
			return "itemGroup.name.chestboat";
		case adk::CreativeGroup::CHESTPLATE:
			return "itemGroup.name.chestplate";
		case adk::CreativeGroup::CONCRETE:
			return "itemGroup.name.concrete";
		case adk::CreativeGroup::CONCRETEPOWDER:
			return "itemGroup.name.concretePowder";
		case adk::CreativeGroup::COOKEDFOOD:
			return "itemGroup.name.cookedFood";
		case adk::CreativeGroup::COPPER:
			return "itemGroup.name.copper";
		case adk::CreativeGroup::CORAL:
			return "itemGroup.name.coral";
		case adk::CreativeGroup::CORALDECORATIONS:
			return "itemGroup.name.coralDecorations";
		case adk::CreativeGroup::CROP:
			return "itemGroup.name.crop";
		case adk::CreativeGroup::DOOR:
			return "itemGroup.name.door";
		case adk::CreativeGroup::DYE:
			return "itemGroup.name.dye";
		case adk::CreativeGroup::ENCHANTEDBOOK:
			return "itemGroup.name.enchantedBook";
		case adk::CreativeGroup::FENCE:
			return "itemGroup.name.fence";
		case adk::CreativeGroup::FENCEGATE:
			return "itemGroup.name.fenceGate";
		case adk::CreativeGroup::FIREWORK:
			return "itemGroup.name.firework";
		case adk::CreativeGroup::FIREWORKSTARS:
			return "itemGroup.name.fireworkStars";
		case adk::CreativeGroup::FLOWER:
			return "itemGroup.name.flower";
		case adk::CreativeGroup::GLASS:
			return "itemGroup.name.glass";
		case adk::CreativeGroup::GLASSPANE:
			return "itemGroup.name.glassPane";
		case adk::CreativeGroup::GLAZEDTERRACOTTA:
			return "itemGroup.name.glazedTerracotta";
		case adk::CreativeGroup::GOATHORN:
			return "itemGroup.name.goatHorn";
		case adk::CreativeGroup::GRASS:
			return "itemGroup.name.grass";
		case adk::CreativeGroup::HELMET:
			return "itemGroup.name.helmet";
		case adk::CreativeGroup::HOE:
			return "itemGroup.name.hoe";
		case adk::CreativeGroup::HORSEARMOR:
			return "itemGroup.name.horseArmor";
		case adk::CreativeGroup::LEAVES:
			return "itemGroup.name.leaves";
		case adk::CreativeGroup::LEGGINGS:
			return "itemGroup.name.leggings";
		case adk::CreativeGroup::LINGERINGPOTION:
			return "itemGroup.name.lingeringPotion";
		case adk::CreativeGroup::LOG:
			return "itemGroup.name.log";
		case adk::CreativeGroup::MINECART:
			return "itemGroup.name.minecart";
		case adk::CreativeGroup::MISCFOOD:
			return "itemGroup.name.miscFood";
		case adk::CreativeGroup::MOBEGG:
			return "itemGroup.name.mobEgg";
		case adk::CreativeGroup::MONSTERSTONEEGG:
			return "itemGroup.name.monsterStoneEgg";
		case adk::CreativeGroup::MUSHROOM:
			return "itemGroup.name.mushroom";
		case adk::CreativeGroup::NETHERWARTBLOCK:
			return "itemGroup.name.netherWartBlock";
		case adk::CreativeGroup::ORE:
			return "itemGroup.name.ore";
		case adk::CreativeGroup::PERMISSION:
			return "itemGroup.name.permission";
		case adk::CreativeGroup::PICKAXE:
			return "itemGroup.name.pickaxe";
		case adk::CreativeGroup::PLANKS:
			return "itemGroup.name.planks";
		case adk::CreativeGroup::POTION:
			return "itemGroup.name.potion";
		case adk::CreativeGroup::PRESSUREPLATE:
			return "itemGroup.name.pressurePlate";
		case adk::CreativeGroup::RAIL:
			return "itemGroup.name.rail";
		case adk::CreativeGroup::RAWFOOD:
			return "itemGroup.name.rawFood";
		case adk::CreativeGroup::RECORD:
			return "itemGroup.name.record";
		case adk::CreativeGroup::SANDSTONE:
			return "itemGroup.name.sandstone";
		case adk::CreativeGroup::SAPLING:
			return "itemGroup.name.sapling";
		case adk::CreativeGroup::SCULK:
			return "itemGroup.name.sculk";
		case adk::CreativeGroup::SEED:
			return "itemGroup.name.seed";
		case adk::CreativeGroup::SHOVEL:
			return "itemGroup.name.shovel";
		case adk::CreativeGroup::SHULKERBOX:
			return "itemGroup.name.shulkerBox";
		case adk::CreativeGroup::SIGN:
			return "itemGroup.name.sign";
		case adk::CreativeGroup::SKULL:
			return "itemGroup.name.skull";
		case adk::CreativeGroup::SLAB:
			return "itemGroup.name.slab";
		case adk::CreativeGroup::SPLASHPOTION:
			return "itemGroup.name.splashPotion";
		case adk::CreativeGroup::STAINEDCLAY:
			return "itemGroup.name.stainedClat";
		case adk::CreativeGroup::STAIRS:
			return "itemGroup.name.stairs";
		case adk::CreativeGroup::STONE:
			return "itemGroup.name.stone";
		case adk::CreativeGroup::STONEBRICK:
			return "itemGroup.name.stoneBrick";
		case adk::CreativeGroup::SWORD:
			return "itemGroup.name.sword";
		case adk::CreativeGroup::TRAPDOOR:
			return "itemGroup.name.trapdoor";
		case adk::CreativeGroup::WALLS:
			return "itemGroup.name.walls";
		case adk::CreativeGroup::WOOD:
			return "itemGroup.name.wood";
		case adk::CreativeGroup::WOOL:
			return "itemGroup.name.wool";
		case adk::CreativeGroup::WOOLCARPET:
			return "itemGroup.name.woolCarpet";
		case adk::CreativeGroup::HANGINGSIGN:
			return "itemGroup.name.hanging_sign";
		case adk::CreativeGroup::POTTERYSHERDS:
			return "itemGroup.name.potterySherds";
		case adk::CreativeGroup::SMITHINGTEMPLATES:
			return "itemGroup.name.smithing_templates";
		case adk::CreativeGroup::NONE:
			return "";
		default:
			return "Error";
		}
	}

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
		struct BlockCraftingTable {
			std::vector<std::string> crafting_tags;
			std::string table_name;
		};

		void to_json(nlohmann::json& j, const BlockCraftingTable& p) {
			j.update({ {"crafting_tags", p.crafting_tags} });

			if (!p.table_name.empty()) j.update({ {"table_name", p.table_name} });
		}

		struct BlockPlacementFilter {
			std::vector<BlockAllowedFaces> allowed_faces;
			std::vector<std::variant<std::string, BlockDescriptor>> block_filter;
		};

		void to_json(nlohmann::json& j, const BlockPlacementFilter& p) {
			std::vector<std::string> allowed_faces;
			for each (BlockAllowedFaces var in p.allowed_faces) {
				allowed_faces.push_back(GetBlockAllowedFaces(var));
			}
			nlohmann::json j2 = nlohmann::json::array();
			for each (auto entries in p.block_filter) {
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
			this->light_dampening = value;

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
				this->explosion = std::get<bool>(value);

				return *this;
			}

			this->explosion = std::get<double>(value);

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
				this->mining = std::get<bool>(value);

				return *this;
			}

			this->mining = std::get<double>(value);

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
			this->display_name = value;

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
			this->flammable = value;

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
			this->flammable = std::make_pair(catch_chance, destroy_chance);

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
			this->friction = value;

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
			this->light_emission = value;

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
			this->loot = value;

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
			this->map_color = value;

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
			this->map_color = value;

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
			this->translation = translation;

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
			this->scale = scale;

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
			this->rotation = rotation;
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
			this->box_selection = value;

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
			this->box_selection = std::make_pair(origin, size);;

			return *this;
		}

		/**
		 * @brief Registers the block to a tab in the creative menu
		 *
		 * @param category Tab the block is placed under
		 * @param group Optional - Group the block is placed into
		 *
		 * @return BlockProperty
		*/
		BlockProperty SetCreativeCategory(adk::CreativeCategory category, adk::CreativeGroup group = adk::CreativeGroup::NONE) {
			this->creative_category = category;
			this->creative_group = group;

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
			this->placement_filter = value;

			return *this;
		}

		/**
		 * @brief Gets the "light_dampening" value
		 *
		 * @return int
		 */
		int GetLightDampening() const { return light_dampening; }

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
		std::variant<bool, double> GetDestructibleByExplosion() const { return explosion; }

		/**
		 * @brief Gets the "destructible_by_mining" component
		 *
		 * @return std::variant<bool, double>
		 */
		std::variant<bool, double> GetDestructibleByMining() const { return mining; }

		/**
		 * @brief Gets the "display_name" component
		 *
		 * @return std::string
		 */
		std::string GetDisplayName() const { return display_name; }

		/**
		 * @brief Gets the "flamamble" component
		 *
		 * @return std::variant<bool, std::pair<int, int>>
		 */
		std::variant<bool, std::pair<int, int>> GetFlamamble() const { return flammable; }

		/**
		 * @brief Gets the "friction" component
		 *
		 * @return double
		 */
		double GetFriction() const { return friction; }

		/**
		 * @brief Gets the "light_emission" component
		 *
		 * @return int
		 */
		int GetLightEmission() const { return light_emission; }

		/**
		 * @brief Gets the "loot" component
		 *
		 * @return std::string
		 */
		std::string GetLoot() const { return loot; }

		/**
		 * @brief Gets the "map_color" component
		 *
		 * @return std::string
		 */
		std::variant<std::string, std::vector<int>> GetMapColor() const { return map_color; }

		/**
		 * @brief Gets the "translation" field of "transformation" component
		 *
		 * @return std::vector<int>
		 */
		std::vector<double> GetTranslation() const { return translation; }

		/**
		 * @brief Gets the "scale" field of "transformation" component
		 *
		 * @return std::vector<int>
		 */
		std::vector<double> GetScale() const { return scale; }

		/**
		 * @brief Gets the "rotation" field of "transformation" component
		 *
		 * @return std::vector<int>
		 */
		std::vector<int> GetRotation() const { return rotation; }

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
			return box_selection;
		}

		/**
		 * @brief Gets the Creative Category component
		 *
		 * @return adk::CreativeCategory
		 */
		adk::CreativeCategory GetCreativeCategory() const {
			return creative_category;
		}

		/**
		 * @brief Gets the Creative Group component
		 *
		 * @return adk::CreativeGroup
		 */
		adk::CreativeGroup GetCreativeGroup() const {
			return creative_group;
		}

		/**
		 * @brief Gets the "placement_filter" component
		 *
		 * @return std::variant<BlockPlacementFilterStates, BlockPlacementFilterTags>
		 */
		BlockPlacementFilter GetPlacementFilter() const {
			return placement_filter;
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
	private:
		int light_dampening = 15;
		BlockCraftingTable crafting_;
		std::variant<bool, double> explosion = true;
		std::variant<bool, double> mining = true;
		std::string display_name;
		std::variant<bool, std::pair<int, int>> flammable = true;
		double friction = 0.4;
		int light_emission;
		std::string loot;
		std::variant<std::string, std::vector<int>> map_color;
		std::vector<int> rotation{ 0, 0, 0 };
		std::vector<double> scale{ 0, 0, 0 };
		std::vector<double> translation{ 0, 0, 0 };
		std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
			box_collision_ = true;
		std::variant<bool, std::pair<std::vector<int>, std::vector<int>>>
			box_selection = true;
		adk::CreativeCategory creative_category = adk::CreativeCategory::NONE;
		adk::CreativeGroup creative_group = adk::CreativeGroup::NONE;
		BlockPlacementFilter placement_filter;
		std::vector<std::string> tags_;
		std::vector<std::string> custom_components_;
	};
} // namespace adk