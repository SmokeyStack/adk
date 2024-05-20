#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "item/item_ranged_weapon.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Crossbow Item
	 */
	class ItemCrossbow : public ItemRangedWeapon {
	public:
		/**
		 * @brief Construct a new Crossbow Item object
		 *
		 * @param property ItemProperty
		 */
		ItemCrossbow(ItemProperty property) { internal_ = property; }

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
			for each (std::string projectile in PROJECTILES_CROSSBOW) {
				ItemShooterAmmunition ammunition;
				ammunition.item = projectile;
				ammunition.search_inventory = true;
				ammunition.use_in_creative = true;
				ammunition.use_offhand = true;
				shooter.ammunition.push_back(ammunition);
			}
			shooter.charge_on_draw = true;
			shooter.max_draw_duration = 0.5;
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