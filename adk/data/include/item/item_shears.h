#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Shears Item
	 */
	class ItemShears : public Item {
	public:
		/**
		 * @brief Construct a new Shears Item object
		 *
		 * @param property ItemProperty
		 */
		ItemShears(ItemProperty property) { internal_ = property; }

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
			ItemDigger digger;
			ItemDiggerDestroySpeeds destroy_speeds;
			BlockDescriptor block_descriptor;
			destroy_speeds.block = "minecraft:vine";
			destroy_speeds.speed = 2.0f;
			digger.destroy_speeds.push_back(destroy_speeds);
			destroy_speeds.block = "minecraft:glow_lichen";
			destroy_speeds.speed = 2.0f;
			digger.destroy_speeds.push_back(destroy_speeds);
			block_descriptor.tags = std::vector<std::string>{ "minecraft:wool" };
			destroy_speeds.block = block_descriptor;
			destroy_speeds.speed = 5.0f;
			digger.destroy_speeds.push_back(destroy_speeds);
			destroy_speeds.block = "minecraft:cobweb";
			destroy_speeds.speed = 15.0f;
			digger.destroy_speeds.push_back(destroy_speeds);
			destroy_speeds.block = "minecraft:leaves";
			destroy_speeds.speed = 15.0f;
			digger.destroy_speeds.push_back(destroy_speeds);
			destroy_speeds.block = "minecraft:leaves2";
			destroy_speeds.speed = 15.0f;
			digger.destroy_speeds.push_back(destroy_speeds);

			output_["minecraft:item"]["components"].update(
				helper_.Digger(digger)
			);

			return output_;
		}
	};
} // namespace adk