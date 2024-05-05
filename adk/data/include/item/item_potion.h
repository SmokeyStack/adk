#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Potion Item
	 */
	class ItemPotion : public Item {
	public:
		/**
		 * @brief Construct a new Potion Item object
		 *
		 * @param property ItemProperty
		 */
		ItemPotion(ItemProperty property) { internal_ = property; }

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
	};
} // namespace adk