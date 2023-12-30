#ifndef ITEMCOMPONENT_H
#define ITEMCOMPONENT_H

#include <spdlog/spdlog.h>

#include <string>
#include <vector>

#include "json.hpp"


namespace adk {
	enum class EnchantableSlots {
		ALL,
		ARMOR_FEET,
		ARMOR_HEAD,
		ARMOR_LEGS,
		ARMOR_TORSO,
		AXE,
		BOW,
		COSMETIC_HEAD,
		CROSSBOW,
		ELYTRA,
		FISHING_ROD,
		FLINTSTEEL,
		HOE,
		PICKAXE,
		SHEARS,
		SHIELD,
		SHOVEL,
		SWORD
	};

	struct DiggerDestroySpeeds {
		std::vector<std::string> blocks;
		int speed;
	};

	struct ShooterAmmunition {
		std::string ammunition;
		bool offhand;
		bool search_inventory;
		bool use_in_creative;
	};
};

std::string getEnchantableSlot(adk::EnchantableSlots slot) {
	switch (slot) {
	case adk::EnchantableSlots::ALL:
		return "all";
	case adk::EnchantableSlots::ARMOR_FEET:
		return "armor_feet";
	case adk::EnchantableSlots::ARMOR_HEAD:
		return "armor_head";
	case adk::EnchantableSlots::ARMOR_LEGS:
		return "armor_legs";
	case adk::EnchantableSlots::ARMOR_TORSO:
		return "armor_torso";
	case adk::EnchantableSlots::AXE:
		return "axe";
	case adk::EnchantableSlots::BOW:
		return "bow";
	case adk::EnchantableSlots::COSMETIC_HEAD:
		return "cosmetic_head";
	case adk::EnchantableSlots::CROSSBOW:
		return "crossbow";
	case adk::EnchantableSlots::ELYTRA:
		return "elytra";
	case adk::EnchantableSlots::FISHING_ROD:
		return "fishing_rod";
	case adk::EnchantableSlots::FLINTSTEEL:
		return "flintsteel";
	case adk::EnchantableSlots::HOE:
		return "hoe";
	case adk::EnchantableSlots::PICKAXE:
		return "pickaxe";
	case adk::EnchantableSlots::SHEARS:
		return "shears";
	case adk::EnchantableSlots::SHIELD:
		return "shield";
	case adk::EnchantableSlots::SHOVEL:
		return "shovel";
	case adk::EnchantableSlots::SWORD:
		return "sword";
	default:
		return "Error";
	}
}

/**
 * @brief Creates the json components
 *
 */
class ItemComponent {
public:
	/**
	 * @brief
	 *
	 * @param value
	 * @return nlohmann::json::object_t
	 */
	nlohmann::json::object_t allowOffHand(bool value) {
		nlohmann::json::object_t temp = { {"minecraft:allow_off_hand", value} };

		return temp;
	}

	nlohmann::json::object_t blockPlacer(std::string block) {
		nlohmann::json::object_t temp = {
			{"minecraft:block_placer", {{"block", block}}} };

		return temp;
	}

	nlohmann::json::object_t blockPlacer(std::string block,
		std::vector<std::string> used_on) {
		nlohmann::json::object_t temp = {
			{"minecraft:block_placer",
			 {{"block", block}, {"used_on", used_on}}} };

		return temp;
	}

	nlohmann::json::object_t destroyInCreative(bool value) {
		nlohmann::json::object_t temp = {
			{"minecraft:can_destroy_in_creative", value} };

		return temp;
	}

	nlohmann::json::object_t cooldown(std::string category, float duration) {
		nlohmann::json::object_t temp = {
			{"minecraft:cooldown",
			 {{"category", category}, {"duration", duration}}} };

		return temp;
	}

	nlohmann::json::object_t damage(int value) {
		nlohmann::json::object_t temp = { {"minecraft:damage", value} };

		return temp;
	}

	nlohmann::json::object_t digger(std::vector<adk::DiggerDestroySpeeds> configs, bool use_efficiency = false) {
		nlohmann::json::array_t digger_configs;

		for (auto& config : configs) {
			digger_configs.push_back({ {"blocks", config.blocks}, {"speed", config.speed} });
		};

		nlohmann::json::object_t temp = { {"minecraft:digger", {{"destory_speeds", digger_configs}, {"use_efficiency", use_efficiency}}} };

		return temp;
	}

	nlohmann::json::object_t displayName(std::string name) {
		nlohmann::json::object_t temp = { {"minecraft:display_name", name } };

		return temp;
	}

	nlohmann::json::object_t durability(int max, int min_chance, int max_chance) {
		nlohmann::json::object_t temp = { {"minecraft:durability", {{"max_durability", max}, {"damage_chance", {{"min", min_chance},{"max", max_chance}}}}} };

		return temp;
	}

	nlohmann::json::object_t enchantable(adk::EnchantableSlots slot, int value) {
		nlohmann::json::object_t temp = { {"minecraft:enchantable", {{"slot", getEnchantableSlot(slot)}, {"value",value}}} };

		return temp;
	}

	nlohmann::json::object_t entityPlacer(std::string entity, std::vector<std::string> dispense_on, std::vector<std::string> use_on) {
		nlohmann::json::object_t temp = { {"minecraft:entity_placer", {{"entity", entity}, {"dispense_on", dispense_on}, {"use_on", use_on}}} };

		return temp;
	}

	nlohmann::json::object_t food() {}

	nlohmann::json::object_t fuel(float value) {
		nlohmann::json::object_t temp = { {"minecraft:fuel", value} };

		return temp;
	}

	nlohmann::json::object_t glint(bool value) {
		nlohmann::json::object_t temp = { {"minecraft:glint", value} };

		return temp;
	}

	nlohmann::json::object_t handEquipped(bool value) {
		nlohmann::json::object_t temp = { {"minecraft:hand_equipped", value} };

		return temp;
	}

	nlohmann::json::object_t icon(std::string texture) {
		nlohmann::json::object_t temp = { {"minecraft:icon", texture} };

		return temp;
	}

	nlohmann::json::object_t interactButton(std::string value) {
		nlohmann::json::object_t temp = { {"minecraft:interact_button", value} };

		return temp;
	}

	nlohmann::json::object_t liquidClipped(std::string value) {
		nlohmann::json::object_t temp = { {"minecraft:liquid_clipped", value} };

		return temp;
	}

	nlohmann::json::object_t maxStackSize(std::string value) {
		nlohmann::json::object_t temp = { {"minecraft:max_stack_size", value} };

		return temp;
	}

	nlohmann::json::object_t projectile(std::string projectile_entity, float minimum_critical_power) {
		nlohmann::json::object_t temp = { {"minecraft:projectile", {{"projectile_entity", projectile_entity},{"minimum_critical_power",minimum_critical_power}}} };

		return temp;
	}

	nlohmann::json::object_t shooter(std::vector<adk::ShooterAmmunition> ammunition, bool charge, float max_draw, bool scale) {
		nlohmann::json::object_t temp = { {"minecraft:shooter", {{"max_draw_duration", max_draw},{"scale_power_by_draw_duration",scale},{"charge_on_draw",charge}}} };

		return temp;
	}

	nlohmann::json::object_t despawn(std::string projectile_entity, float minimum_critical_power) {
		nlohmann::json::object_t temp = { {"minecraft:projectile", {{"projectile_entity", projectile_entity},{"minimum_critical_power",minimum_critical_power}}} };

		return temp;
	}

	nlohmann::json::object_t tags(std::string projectile_entity, float minimum_critical_power) {
		nlohmann::json::object_t temp = { {"minecraft:projectile", {{"projectile_entity", projectile_entity},{"minimum_critical_power",minimum_critical_power}}} };

		return temp;
	}

	nlohmann::json::object_t throwable(std::string projectile_entity, float minimum_critical_power) {
		nlohmann::json::object_t temp = { {"minecraft:projectile", {{"projectile_entity", projectile_entity},{"minimum_critical_power",minimum_critical_power}}} };

		return temp;
	}

	nlohmann::json::object_t use_modifiers(std::string projectile_entity, float minimum_critical_power) {
		nlohmann::json::object_t temp = { {"minecraft:projectile", {{"projectile_entity", projectile_entity},{"minimum_critical_power",minimum_critical_power}}} };

		return temp;
	}

	nlohmann::json::object_t use_animations(std::string projectile_entity, float minimum_critical_power) {
		nlohmann::json::object_t temp = { {"minecraft:projectile", {{"projectile_entity", projectile_entity},{"minimum_critical_power",minimum_critical_power}}} };

		return temp;
	}

	nlohmann::json::object_t wearable(std::string projectile_entity, float minimum_critical_power) {
		nlohmann::json::object_t temp = { {"minecraft:projectile", {{"projectile_entity", projectile_entity},{"minimum_critical_power",minimum_critical_power}}} };

		return temp;
	}
};

#endif