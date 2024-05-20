#pragma once

#include <string>

#include "item/item.h"

namespace adk {
	/**
	 * @brief Defines the material stats of an ArmorItem item.
     * To view available vanilla armor materials, visit ArmorMaterials.
     */
	class ArmorMaterial {
	public:
		/**
		 * @brief Gets the total amount of durability that an ItemArmor using this ArmorMaterial has.
		 * 
		 * @param slot The slot of the armor piece.
		 * 
		 * @return The total durability that an ItemArmor with this ArmorMaterial has.
		 */
		virtual int GetDurability(WearableSlot slot) = 0;
		/**
		 * @brief Converts the given WearableSlot to an EnchantableSlot.
		 * 
		 * @param slot The slot of the armor piece.
		 * 
		 * @return The EnchantableSlot.
		 */
		virtual EnchantableSlot GetEnchantabilitySlot(WearableSlot slot) = 0;
		/**
		 * @brief Gets the amount of armor protection points this ItemArmor using this ArmorMaterial has while it is worn by a player.
		 * 
		 * @param slot The slot of the armor piece.
		 * 
		 * @return The amount of armor protection points this ItemArmor using this ArmorMaterial has.
		 */
		virtual int GetProtection(WearableSlot slot) = 0;
		/**
		 * @brief Returns the enchantability factor of the ArmorMaterial.
		 * 
		 * @return The enchantability factor of the ArmorMaterial.
		 */
		virtual int GetEnchantability() = 0;
		/**
		 * @brief Gets the repair ingredient for the ArmorMaterial.
		 * 
		 * @return The repair ingredient for the ArmorMaterial.
		 */
		virtual std::string GetRepairIngredient() = 0;
	};
} // namespace adk