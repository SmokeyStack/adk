#pragma once

#include <string>

#include "item/item_property.h"
#include "item/item_tool_mining.h"
#include "item/tool_material.h"
#include "json.hpp"
#include "tag.h"

namespace adk {
	/**
	 * @brief Represents a Pickaxe Item
	 */
	class ItemPickaxe : public ItemToolMining {
	public:
		/**
		 * @brief Construct a new Mining Tool Item object
		 *
		 * @param material ToolMaterial of the Item.
		 *
		 * @param attack_damage Attack damage of the Item.
		 *
		 * @param property ItemProperty.
		 */
		ItemPickaxe(ToolMaterial* material, float attack_damage, ItemProperty property)
			:ItemToolMining(attack_damage, material, pickaxe_mineable, property) {}
	};
} // namespace adk