#pragma once

#include <string>

#include "item/item.h"

namespace adk {
	/**
	 * @brief Defines the material stats of an ArmorItem item.
     * To view available vanilla tool materials, visit ToolMaterials.
     */
	class ToolMaterial {
	public:
		/**
		 * @brief Gets the total amount of durability that an ItemTool using this ToolMaterial has.
		 * 
		 * @return The total durability that an ItemTool with this ToolMaterial has.
		 */
		virtual int GetDurability() = 0;
		/**
		 * @brief Gets the mining speed that an ItemTool using this ToolMaterial has.
		 *
		 * @return The mining speed that an ItemTool with this ToolMaterial has.
		 */
		virtual int GetMiningSpeed() = 0;
		/**
		 * @brief Gets the attack damage that an ItemTool using this ToolMaterial has.
		 *
		 * @return The attack damage that an ItemTool with this ToolMaterial has.
		 */
		virtual int GetAttackDamage() = 0;
		/**
		 * @brief Returns the enchantability factor of the ToolMaterial.
		 * 
		 * @return The enchantability factor of the ToolMaterial.
		 */
		virtual int GetEnchantability() = 0;
		/**
		 * @brief Gets the repair ingredient for the ToolMaterial.
		 * 
		 * @return The repair ingredient for the ToolMaterial.
		 */
		virtual std::string GetRepairIngredient() = 0;
	};
} // namespace adk