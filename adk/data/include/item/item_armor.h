#pragma once

#include <string>

#include "item/armor_material.h"
#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Armor Item
	 */
	class ItemArmor : public Item {
	public:
		/**
		 * @brief Construct a new Armor Item object
		 *
		 * @param material ArmorMaterial of the Armor.
		 * 
		 * @param slot Determines where the item can be worn.
		 * 
		 * @param property ItemProperty.
		 */
		ItemArmor(ArmorMaterial* material, WearableSlot slot, ItemProperty property) {
			internal_ = property;
			material_ = material;
			slot_ = slot;
			protection_ = material->GetProtection(slot);
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
				helper_.Durability(
					ItemDurability{
						material_->GetDurability(slot_),
						std::make_pair<int>(60,100)
					},
					id
				)
			);
			output_["minecraft:item"]["components"].update(
				helper_.Wearable(
					GetWearableSlot(slot_),
					protection_,
					id
				)
			);
			output_["minecraft:item"]["components"].update(
				helper_.Enchantable(
					GetEnchantableSlot(material_->GetEnchantabilitySlot(slot_)),
					material_->GetEnchantability(),
					id
				)
			);
			output_["minecraft:item"]["components"].update(
				helper_.Repairable(
					ItemRepairable{
						std::vector<ItemRepairableItems>{{"math.floor(q.max_durability * 0.25)",std::vector<std::string>{{material_->GetRepairIngredient()}}}}
					}
				)
			);
			if (output_["minecraft:item"]["components"].contains("minecraft:tags"))
				output_["minecraft:item"]["components"]["minecraft:tags"]["tags"].push_back({ "minecraft:is_armor" ,"minecraft:trimmable_armors" });
			else
				output_["minecraft:item"]["components"].update(
					helper_.Tags(std::vector<std::string>{"minecraft:is_armor", "minecraft:trimmable_armors"})
				);

			return output_;
		}
	protected:
		WearableSlot slot_;
		ArmorMaterial* material_;
	private:
		int protection_;
	};
} // namespace adk