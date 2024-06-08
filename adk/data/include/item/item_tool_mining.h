#pragma once

#include <string>

#include "item/item_property.h"
#include "item/item_tool.h"
#include "item/tool_material.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Mining Tool Item
	 */
	class ItemToolMining : public ItemTool {
	public:
		ItemToolMining() {};
		/**
		 * @brief Construct a new Mining Tool Item object
		 *
		 * @param attack_damage Attack damage of the Item.
		 *
		 * @param material ToolMaterial of the Item.
		 *
		 * @param effective_blocks List of blocks that the tool can mine.
		 *
		 * @param property ItemProperty.
		 */
		ItemToolMining(float attack_damage, ToolMaterial* material, std::vector<std::string> effective_blocks, ItemProperty property)
			:ItemTool(material, property) {
			effective_blocks_ = effective_blocks;
			attack_damage_ = attack_damage;
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
			output_ = ItemTool::Generate(mod_id, id);

			ItemDigger digger;
			ItemDiggerDestroySpeeds destroy_speeds;

			for (std::string block : effective_blocks_) {
				destroy_speeds.block = block;
				destroy_speeds.speed = material_->GetMiningSpeed();
				digger.destroy_speeds.push_back(destroy_speeds);
			}

			output_["minecraft:item"]["components"].update(
				helper_.Digger(digger)
			);

			return output_;
		}
	protected:
		float mining_speed_;
	private:
		std::vector<std::string> effective_blocks_;
		float attack_damage_;
	};
} // namespace adk