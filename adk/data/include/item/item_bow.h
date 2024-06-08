#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "item/item_ranged_weapon.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Bow Item
	 */
	class ItemBow : public ItemRangedWeapon {
	public:
		/**
		 * @brief Construct a new Bow Item object
		 *
		 * @param property ItemProperty
		 */
		ItemBow(ItemProperty property) { internal_ = property; }

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
			ItemShooter shooter;
			for (std::string projectile : PROJECTILES_BOW) {
				ItemShooterAmmunition ammunition;
				ammunition.item = projectile;
				ammunition.search_inventory = true;
				ammunition.use_in_creative = true;
				ammunition.use_offhand = true;
				shooter.ammunition.push_back(ammunition);
			}
			shooter.scale_power_by_draw_duration = true;

			output_["minecraft:item"]["components"].update(
				helper_.UseModifiers(3600, 0.35, id)
			);
			output_["minecraft:item"]["components"].update(
				helper_.Shooter(shooter)
			);

			return output_;
		}
	};
} // namespace adk