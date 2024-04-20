#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Armor Item
	 *
	 */
	class ItemArmorStand : public Item {
	public:
		/**
		 * @brief Construct a new Armor Item object
		 *
		 * @param property An ItemProperty object
		 * @param protection How much protection point should this armor give
		 * @param slot Which slot should the armor go in
		 * @param durability How much durability point should this armor have
		 * @param damage_chance_min Minimum chance the armor takes damage
		 * @param damage_chance_max Maximum chance the armor takes damage
		 * @param dispensable Can this armor be equipped by a dispenser
		 */
		ItemArmorStand(ItemProperty property) { internal_ = property; }

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 * @param id Identifier for the item
		 * @return nlohmann::json
		 */
		nlohmann::json Generate(std::string mod_id, std::string id) {
			output_ = Item::Generate(mod_id, id);

			output_["minecraft:item"]["components"].update(
				helper_.PlacerEntity(
					ItemEntityPlacer{"minecraft:armor_stand"}
				)
			);

			return output_;
		}
	};
} // namespace adk