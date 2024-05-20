#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"
#include "utility/dye_color.h"

namespace adk {
	/**
	 * @brief Represents a Dye Item
	 */
	class ItemDye : public Item {
	public:
		/**
		 * @brief Construct a new Dye Item object
		 *
		 * @param color DyeColor
		 * 
		 * @param property ItemProperty
		 */
		ItemDye(DyeColor color, ItemProperty property) {
			internal_ = property;
			color_ = color;
		}

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
				helper_.CustomComponents(std::vector<std::string>{"adk-lib:item_dye_use_on"})
			);

			if (output_["minecraft:item"]["components"].contains("minecraft:tags"))
				output_["minecraft:item"]["components"]["minecraft:tags"]["tags"].push_back(GetDyeColor(color_));
			else
				output_["minecraft:item"]["components"].update(
					helper_.Tags(std::vector<std::string>{GetDyeColor(color_)})
				);

			return output_;
		}
	private:
		DyeColor color_;
	};
} // namespace adk