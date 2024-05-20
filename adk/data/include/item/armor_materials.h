#pragma once

#include <string>
#include <unordered_map>

#include "item/armor_material.h"
#include "item/item.h"

namespace adk {
	/**
	 * @brief Contains all the default armour components used in vanilla armour items.
	 */
	class ArmorMaterials : public ArmorMaterial {
	public:
		static ArmorMaterials Leather;
		static ArmorMaterials Chain;
		static ArmorMaterials Iron;
		static ArmorMaterials Gold;
		static ArmorMaterials Diamond;
		static ArmorMaterials Turtle;
		static ArmorMaterials Netherite;

		int GetDurability(WearableSlot slot) override { return BaseDurability_.at(slot) * durability_multiplier_; }
		EnchantableSlot GetEnchantabilitySlot(WearableSlot slot) override { return WearableToEnchantable_.at(slot); }
		int GetProtection(WearableSlot slot) override { return protection_amounts_.at(slot); }
		int GetEnchantability() override { return enchantability_; }
		std::string GetRepairIngredient() override { return repair_ingredient_; }

	private:
		static const std::unordered_map<WearableSlot, int> BaseDurability_;
		static const std::unordered_map<WearableSlot, EnchantableSlot> WearableToEnchantable_;
		int durability_multiplier_;
		std::unordered_map<WearableSlot, int> protection_amounts_;
		int enchantability_;
		std::string repair_ingredient_;

		ArmorMaterials(int durability_multiplier, std::unordered_map<WearableSlot, int> protection_amounts, int enchantability, std::string repair_ingredient) {
			durability_multiplier_ = durability_multiplier;
			protection_amounts_ = protection_amounts;
			enchantability_ = enchantability;
			repair_ingredient_ = repair_ingredient;
		}
	};

	ArmorMaterials ArmorMaterials::Leather = ArmorMaterials(
		5,
		{ {WearableSlot::ArmorHead, 1},
		{WearableSlot::ArmorChest, 3},
		{WearableSlot::ArmorLegs, 2},
		{WearableSlot::ArmorFeet, 1} },
		15,
		"minecraft:leather"
	);

	ArmorMaterials ArmorMaterials::Chain = ArmorMaterials(
		15,
		{ {WearableSlot::ArmorHead, 1},
		{WearableSlot::ArmorChest, 4},
		{WearableSlot::ArmorLegs, 5},
		{WearableSlot::ArmorFeet, 2} },
		9,
		"minecraft:iron_ingot"
	);

	ArmorMaterials ArmorMaterials::Iron = ArmorMaterials(
		15,
		{ {WearableSlot::ArmorHead, 2},
		{WearableSlot::ArmorChest, 5},
		{WearableSlot::ArmorLegs, 6},
		{WearableSlot::ArmorFeet, 2} },
		25,
		"minecraft:iron_ingot"
	);

	ArmorMaterials ArmorMaterials::Gold = ArmorMaterials(
		7,
		{ {WearableSlot::ArmorHead, 1},
		{WearableSlot::ArmorChest, 3},
		{WearableSlot::ArmorLegs, 5},
		{WearableSlot::ArmorFeet, 2} },
		25,
		"minecraft:gold_ingot"
	);

	ArmorMaterials ArmorMaterials::Diamond = ArmorMaterials(
		33,
		{ {WearableSlot::ArmorHead, 3},
		{WearableSlot::ArmorChest, 6},
		{WearableSlot::ArmorLegs, 8},
		{WearableSlot::ArmorFeet, 3} },
		10,
		"minecraft:diamond"
	);
	
	ArmorMaterials ArmorMaterials::Turtle = ArmorMaterials(
		25,
		{ {WearableSlot::ArmorHead, 2},
		{WearableSlot::ArmorChest, 5},
		{WearableSlot::ArmorLegs, 6},
		{WearableSlot::ArmorFeet, 2} },
		9,
		"minecraft:turtle_scute"
	);
	
	ArmorMaterials ArmorMaterials::Netherite = ArmorMaterials(
		37,
		{ {WearableSlot::ArmorHead, 3},
		{WearableSlot::ArmorChest, 6},
		{WearableSlot::ArmorLegs, 8},
		{WearableSlot::ArmorFeet, 3} },
		15,
		"minecraft:netherite_ingot"
	);

	const std::unordered_map<WearableSlot, int> ArmorMaterials::BaseDurability_ = {
	   {WearableSlot::ArmorHead, 11},
	   {WearableSlot::ArmorChest, 16},
	   {WearableSlot::ArmorLegs, 15},
	   {WearableSlot::ArmorFeet, 13}
	};

	const std::unordered_map<WearableSlot, EnchantableSlot> ArmorMaterials::WearableToEnchantable_ = {
	   {WearableSlot::ArmorHead, EnchantableSlot::ArmorHead},
	   {WearableSlot::ArmorChest, EnchantableSlot::ArmorTorso},
	   {WearableSlot::ArmorLegs, EnchantableSlot::ArmorLegs},
	   {WearableSlot::ArmorFeet, EnchantableSlot::ArmorFeet}
	};
} // namespace adk