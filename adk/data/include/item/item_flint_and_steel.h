#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Flint and Steel Item
	 */
	class ItemFlintAndSteel : public Item {
	public:
		/**
		 * @brief Construct a new Flint and Steel Item object
		 *
		 * @param property ItemProperty
		 */
		ItemFlintAndSteel(ItemProperty property) { internal_ = property; }

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
				helper_.CustomComponents(std::vector<std::string>{"adk-lib:on_use_on_fire"})
			);

			return output_;
		}
	};
} // namespace adk