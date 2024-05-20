#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Bucket Item
	 */
	class ItemBucket : public Item {
	public:
		/**
		 * @brief Construct a new Bucket Item object
		 *
		 * @param fluid The fluid that the bucket can hold
		 *
		 * @param property ItemProperty
		 */
		ItemBucket(std::string fluid, ItemProperty property) {
			internal_ = property;
			fluid_ = fluid;
		}

		/**
		 * @brief Construct a new Bucket Item object
		 *
		 * @param fluid The fluid that the bucket can hold
		 *
		 * @param fluid_pickup The fluids that the bucket can pick up
		 *
		 * @param property ItemProperty
		 */
		ItemBucket(std::string fluid, std::vector<std::string> fluid_pickup, ItemProperty property) {
			internal_ = property;
			fluid_ = fluid;
			fluid_pickup_ = fluid_pickup;
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
				helper_.CustomComponents(std::vector<std::string>{"adk-lib:use_on_bucket"})
			);
			output_["minecraft:item"]["components"].update(
				helper_.LiquidClipped(true)
			);

			if (fluid_ == "adk-lib:fluid_empty") {

				if (output_["minecraft:item"]["components"].contains("minecraft:tags"))
					output_["minecraft:item"]["components"]["minecraft:tags"]["tags"].push_back(fluid_);
				else
					output_["minecraft:item"]["components"].update(
						helper_.Tags(std::vector<std::string>{fluid_})
					);
				for (auto& fluid : fluid_pickup_)
					output_["minecraft:item"]["components"]["minecraft:tags"]["tags"].push_back(fluid);

				return output_;
			}

			if (output_["minecraft:item"]["components"].contains("minecraft:tags"))
				output_["minecraft:item"]["components"]["minecraft:tags"]["tags"].push_back(fluid_);
			else
				output_["minecraft:item"]["components"].update(
					helper_.Tags(std::vector<std::string>{fluid_})
				);

			return output_;
		}
	protected:
		std::string fluid_;
		std::vector<std::string> fluid_pickup_;
	};
} // namespace adk