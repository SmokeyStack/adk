#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Ender Pearl Item
	 */
	class ItemEnderPearl : public Item {
	public:
		/**
		 * @brief Construct a new Ender Pearl Item object
		 *
		 * @param property ItemProperty
		 */
		ItemEnderPearl(ItemProperty property) { internal_ = property; }

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
				helper_.Projectile("minecraft:ender_pearl")
			);
			ItemThrowable throwable;
			throwable.do_swing_animation = true;
			output_["minecraft:item"]["components"].update(
				helper_.Throwable(throwable)
			);

			return output_;
		}
	};
} // namespace adk