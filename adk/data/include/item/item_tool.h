#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "item/tool_material.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Tool Item
	 */
	class ItemTool : public Item {
	public:
		ItemTool() {};
		/**
		 * @brief Construct a new Tool Item object
		 *
		 * @param material ToolMaterial of the Item.
		 *
		 * @param property ItemProperty.
		 */
		ItemTool(ToolMaterial* material, ItemProperty property) {
			internal_ = property;
			material_ = material;
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
				helper_.Enchantable(
					"all",
					material_->GetEnchantability(),
					id
				)
			);
			output_["minecraft:item"]["components"].update(
				helper_.Durability(
					ItemDurability{
						material_->GetDurability(),
						std::make_pair<int>(0,100)
					},
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

			return output_;
		}
	protected:
		ToolMaterial* material_;
	};
} // namespace adk