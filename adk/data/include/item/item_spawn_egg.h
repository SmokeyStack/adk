#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Spawn Egg Item
	 */
	class ItemSpawnEgg : public Item {
	public:
		/**
		 * @brief Construct a new Spawn Egg Item object
		 *
		 * @param entity Entity identifier
		 *
		 * @param property ItemProperty
		 */
		ItemSpawnEgg(std::string entity, ItemProperty property) {
			internal_ = property;
			entity_ = entity;
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
				helper_.PlacerEntity(ItemEntityPlacer{ entity_ })
			);

			return output_;
		}
	private:
		std::string entity_;
	};
} // namespace adk