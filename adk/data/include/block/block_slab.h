#pragma once

#include <string>

#include "block/block.h"
#include "block/block_component.h"
#include "block/block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Slab Block
	 */
	class BlockSlab : public Block {
	public:
		/**
		 * @brief Construct a new Slab Block object
		 *
		 * @param property BlockProperty
		 * 
		 * @param is_double_loot Identifier for the loot table.
		 * This is used to determine what to drop when the slab is in the double state.
		 */
		BlockSlab(BlockProperty property, std::string is_double_loot) : Block(property) {
			is_double_loot_ = is_double_loot;
		}

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the block
		 *
		 * @return nlohmann::json
		 */
		nlohmann::json Generate(std::string mod_id, std::string id) {
			output_ = Block::Generate(mod_id, id);

			output_["minecraft:block"]["description"]["traits"]["minecraft:placement_position"]["enabled_states"] = { "minecraft:vertical_half" };
			output_["minecraft:block"]["description"]["states"][mod_id + ":is_double"] = { false, true };
			nlohmann::json::object_t temp = {
			{"condition",
			 "q.block_state('minecraft:vertical_half') == 'bottom' && !q.block_state('" + mod_id + ":is_double')"} };
			temp["components"].update(
				helper_.BoxCollision(
					std::vector<int>{-8, 0, -8},
					std::vector<int>{16, 8, 16},
					id
				)
			);
			temp["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-8, 0, -8},
					std::vector<int>{16, 8, 16},
					id
				)
			);
			temp["components"].update(
				helper_.CustomComponents({ "adk-lib:before_on_player_place_double_slab" })
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('minecraft:vertical_half') == 'top' && !q.block_state('" + mod_id + ":is_double')"} };
			temp["components"].update(
				helper_.BoxCollision(
					std::vector<int>{-8, 8, -8},
					std::vector<int>{16, 8, 16},
					id
				)
			);
			temp["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-8, 8, -8},
					std::vector<int>{16, 8, 16},
					id
				)
			);
			temp["components"].update(
				helper_.CustomComponents({ "adk-lib:before_on_player_place_double_slab" })
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('" + mod_id + ":is_double')"} };
			temp["components"].update(
				helper_.Loot(is_double_loot_)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);

			return output_;
		}
	private:
		std::string is_double_loot_;
	};
} // namespace adk