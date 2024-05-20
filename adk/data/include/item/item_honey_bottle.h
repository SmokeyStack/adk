#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Honey Bottle Item
	 */
	class ItemHoneyBottle : public Item {
	public:
		/**
		 * @brief Construct a new Honey Bottle Item object
		 *
		 * @param property ItemProperty
		 */
		ItemHoneyBottle(ItemProperty property) { internal_ = property; }

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
				helper_.CustomComponents(std::vector<std::string>{"adk-lib:on_consume_food_effect"})
			);
			if (output_["minecraft:item"]["components"].contains("minecraft:tags"))
				output_["minecraft:item"]["components"]["minecraft:tags"]["tags"].push_back("adk-lib:food_poison_0_0_false");
			else
				output_["minecraft:item"]["components"].update(
					helper_.Tags(std::vector<std::string>{"adk-lib:food_poison_0_0_false"})
				);

			return output_;
		}
	};
} // namespace adk