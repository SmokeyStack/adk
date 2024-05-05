#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Elytra Item
	 */
	class ItemElytra : public Item {
	public:
		/**
		 * @brief Construct a new Elytra Item object
		 *
		 * @param property ItemProperty
		 */
		ItemElytra(ItemProperty property) { internal_ = property; }

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

			/*
			 * This was supposed to be a custom component that implements the elytra functionality of not being able to be damaged if the item has 1 durability left.
			 * Unfortunately, I forgot that onBeforeDurabilityDamage only activates if the item gets damaged by hitting an entity, not by using it.
			 * I'll leave this here for reference.
			 */
			output_["minecraft:item"]["components"].update(
				helper_.CustomComponents(std::vector<std::string>{"adk-lib:before_durability_damage_elytra_is_useable"})
			);
			output_["minecraft:item"]["components"].update(
				helper_.Wearable(GetWearableSlot(WearableSlot::ArmorChest), 0, id)
			);

			return output_;
		}
	};
} // namespace adk