#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Goat Horn Item
	 */
	class ItemGoatHorn : public Item {
	public:
		/**
		 * @brief Construct a new Goat Horn Item object
		 * 
		 * @param sound Sound to play when the item is used
		 *
		 * @param property ItemProperty
		 */
		ItemGoatHorn(std::string sound, ItemProperty property) {
			internal_ = property;
			sound_ = sound;
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
				helper_.CustomComponents(std::vector<std::string>{"adk-lib:on_use_goat_horn"})
			);
			output_["minecraft:item"]["components"].update(helper_.Cooldown("custom_goat_horn", 7));

			if (output_["minecraft:item"]["components"].contains("minecraft:tags"))
				output_["minecraft:item"]["components"]["minecraft:tags"]["tags"].push_back(sound_);
			else
				output_["minecraft:item"]["components"].update(
					helper_.Tags(std::vector<std::string>{sound_})
				);

			return output_;
		}
	private:
		std::string sound_;
	};
} // namespace adk