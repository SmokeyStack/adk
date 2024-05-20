#pragma once

#include <string>
#include <unordered_map>

#include "item/item.h"
#include "item/tool_material.h"

namespace adk {
	class ToolMaterials : public ToolMaterial {
	public:
		static ToolMaterials Wood;
		static ToolMaterials Stone;
		static ToolMaterials Iron;
		static ToolMaterials Diamond;
		static ToolMaterials Gold;
		static ToolMaterials Netherite;

		int GetDurability() override { return durability_; }
		int GetMiningSpeed() override { return mining_speed_; }
		int GetAttackDamage() override { return attack_damage_; }
		int GetEnchantability() override { return enchantability_; }
		std::string GetRepairIngredient() override { return repair_ingredient_; }

	private:
		int mining_level_;
		int durability_;
		float mining_speed_;
		float attack_damage_;
		int enchantability_;
		std::string repair_ingredient_;

		ToolMaterials(int mining_level, int durability, float mining_speed, float attack_damage, int enchantability, std::string repair_ingredient) {
			mining_level_ = mining_level;
			durability_ = durability;
			mining_speed_ = mining_speed;
			attack_damage_ = attack_damage;
			enchantability_ = enchantability;
			repair_ingredient_ = repair_ingredient;
		}
	};

	ToolMaterials ToolMaterials::Wood = ToolMaterials(
		0,
		59,
		2.0f,
		0.0f,
		15,
		"minecraft:planks"
	);
	ToolMaterials ToolMaterials::Stone = ToolMaterials(
		1,
		131,
		4.0f,
		1.0f,
		5,
		"minecraft:stone"
	);
	ToolMaterials ToolMaterials::Iron = ToolMaterials(
		2,
		1561,
		6.0f,
		2.0f,
		14,
		"minecraft:iron_ingot"
	);
	ToolMaterials ToolMaterials::Diamond = ToolMaterials(
		3,
		250,
		8.0f,
		3.0f,
		10,
		"minecraft:diamond"
	);
	ToolMaterials ToolMaterials::Gold = ToolMaterials(
		0,
		32,
		12.0f,
		0.0f,
		22,
		"minecraft:gold_ingot"
	);
	ToolMaterials ToolMaterials::Netherite = ToolMaterials(
		4,
		2031,
		9.0f,
		4.0f,
		15,
		"minecraft:netherite_ingot"
	);
} // namespace adk