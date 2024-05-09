#pragma once

#include <string>

#include "block.h"
#include "block_component.h"
#include "block_property.h"
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
		 */
		BlockSlab(BlockProperty property) : Block(property) { internal_ = property; }

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
				helper_.CustomComponents({ "adk-lib:on_player_destroy_spawn_item" })
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			std::string tag = "adk-lib:spawn_item_" + mod_id + ":" + id;
			output_["minecraft:block"]["components"]["tag:" + tag] = nlohmann::json::object();

			return output_;
		}
	};
} // namespace adk