#pragma once

#include <unordered_map>
#include <string>

#include "item.h"

namespace adk {
	class ArmorMaterial {
	public:
		int GetDurability(WearableSlot slot) { return BaseDurability_.at(slot) * durability_multiplier_; }
		EnchantableSlot GetEnchantabilitySlot(WearableSlot slot) { return WearableToEnchantable_.at(slot); }
		int GetProtection(WearableSlot slot) { return protection_amounts_.at(slot); }
		int GetEnchantability() { return enchantability_; }
		std::string GetRepairIngredient() { return repair_ingredient_; }

		ArmorMaterial() {};

		ArmorMaterial(int durability_multiplier, std::unordered_map<WearableSlot, int> protection_amounts, int enchantability, std::string repair_ingredient)
			:durability_multiplier_(durability_multiplier), protection_amounts_(protection_amounts), enchantability_(enchantability), repair_ingredient_(repair_ingredient) {}
	private:
		static const std::unordered_map<WearableSlot, int> BaseDurability_;
		static const std::unordered_map<WearableSlot, EnchantableSlot> WearableToEnchantable_;
		int durability_multiplier_;
		std::unordered_map<WearableSlot, int> protection_amounts_;
		int enchantability_;
		std::string repair_ingredient_;
	};

	class ArmorMaterials : public ArmorMaterial {
	public:
		static const ArmorMaterial Leather;
	};

	const ArmorMaterial ArmorMaterials::Leather = ArmorMaterial(
		5,
		{ {WearableSlot::ArmorHead, 1},
		{WearableSlot::ArmorChest, 3},
		{WearableSlot::ArmorLegs, 2},
		{WearableSlot::ArmorFeet, 1} },
		15,
		"leather"
	);

	const std::unordered_map<WearableSlot, int> ArmorMaterial::BaseDurability_ = {
	   {WearableSlot::ArmorHead, 11},
	   {WearableSlot::ArmorChest, 16},
	   {WearableSlot::ArmorLegs, 15},
	   {WearableSlot::ArmorFeet, 13}
	};

	const std::unordered_map<WearableSlot, EnchantableSlot> ArmorMaterial::WearableToEnchantable_ = {
	   {WearableSlot::ArmorHead, EnchantableSlot::ArmorHead},
	   {WearableSlot::ArmorChest, EnchantableSlot::ArmorTorso},
	   {WearableSlot::ArmorLegs, EnchantableSlot::ArmorLegs},
	   {WearableSlot::ArmorFeet, EnchantableSlot::ArmorFeet}
	};
} // namespace adk