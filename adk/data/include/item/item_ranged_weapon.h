#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Ranged Weapon Item
	 */
	class ItemRangedWeapon : public Item {
	public:
		ItemRangedWeapon() {};
		/**
		 * @brief Construct a new Ranged Weapon Item object
		 *
		 * @param property ItemProperty
		 */
		ItemRangedWeapon(ItemProperty property) { internal_ = property; }

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the item
		 *
		 * @return nlohmann::json
		 */
		nlohmann::json Generate(std::string mod_id, std::string id) {
			output_ = Item::Generate(mod_id, id);

			return output_;
		}

		const std::vector<std::string> PROJECTILES_BOW = { "minecraft:arrow" };
		const std::vector<std::string> PROJECTILES_CROSSBOW = { "minecraft:arrow", "minecraft:firework_rocket" };
	};
} // namespace adk