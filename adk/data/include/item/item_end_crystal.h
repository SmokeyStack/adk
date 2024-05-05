#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an End Crystal Item
	 */
	class ItemEndCrystal : public Item {
	public:
		/**
		 * @brief Construct a new End Crystal Item object
		 *
		 * @param property ItemProperty
		 */
		ItemEndCrystal(ItemProperty property) { internal_ = property; }

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

			output_["minecraft:item"]["components"].update(
				helper_.PlacerEntity(ItemEntityPlacer{ "minecraft:ender_crystal",std::vector<std::string>{"minecraft:bedrock","minecraft:obsidian"}})
			);

			return output_;
		}
	};
} // namespace adk