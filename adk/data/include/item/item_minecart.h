#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Minecart Item
	 */
	class ItemMinecart : public Item {
	public:
		/**
		 * @brief Construct a new Minecart Item object
		 *
		 * @param type Type of the minecart
		 *
		 * @param property ItemProperty
		 */
		ItemMinecart(std::string type, ItemProperty property) {
			internal_ = property;
			type_ = type;
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
			ItemEntityPlacer minecart;
			minecart.entity = type_;
			minecart.use_on = std::vector<std::string>{ "minecraft:rail","minecraft:golden_rail","minecraft:detector_rail","minecraft:activator_rail" };
			minecart.dispense_on = std::vector<std::string>{ "minecraft:rail","minecraft:golden_rail","minecraft:detector_rail","minecraft:activator_rail" };

			output_["minecraft:item"]["components"].update(
				helper_.PlacerEntity(minecart)
			);
			if (output_["minecraft:item"]["components"].contains("minecraft:tags"))
				output_["minecraft:item"]["components"]["minecraft:tags"]["tags"].push_back("minecraft:is_minecart");
			else
				output_["minecraft:item"]["components"].update(
					helper_.Tags(std::vector<std::string>{"minecraft:is_minecart"})
				);

			return output_;
		}
	private:
		std::string type_;
	};
} // namespace adk