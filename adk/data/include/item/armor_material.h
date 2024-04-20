#pragma once

#include <string>

#include "item.h"

namespace adk {
	class ArmorMaterial {
	public:
		virtual int GetDurability(WearableSlot slot) = 0;
		virtual EnchantableSlot GetEnchantabilitySlot(WearableSlot slot) = 0;
		virtual int GetProtection(WearableSlot slot) = 0;
		virtual int GetEnchantability() = 0;
		virtual std::string GetRepairIngredient() = 0;
	};
} // namespace adk