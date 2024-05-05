#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Brush Item
	 *
	 */
	class ItemBrush : public Item {
	public:
		/**
		 * @brief Construct a new Brush Item object
		 *
		 * @param property ItemProperty
		 */
		ItemBrush(ItemProperty property) { internal_ = property; }

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
			output_["minecraft:item"]["components"].update(helper_.InteractButton("action.interact.brush"));
			output_["minecraft:item"]["components"].update(helper_.UseModifiers(200, 0.35, id));

			return output_;
		}
	};
} // namespace adk