#pragma once

#include <string>

namespace adk {
	/**
	 * @brief Represents the category in Creative Menu
	 *
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
	 *
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
	 * @brief Get the Creative category object
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
}  // namespace adk