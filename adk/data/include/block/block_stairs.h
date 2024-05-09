#pragma once

#include <string>

#include "block.h"
#include "block_component.h"
#include "block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Stairs Block
	 */
	class BlockStairs : public Block {
	public:
		/**
		 * @brief Construct a new Stairs Block object
		 *
		 * @param property BlockProperty
		 */
		BlockStairs(BlockProperty property) : Block(property) { internal_ = property; }

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
			output_["minecraft:block"]["description"]["traits"]["minecraft:placement_direction"]["enabled_states"] = { "minecraft:cardinal_direction" };
			output_["minecraft:block"]["description"]["states"][mod_id + ":north_east"] = { true, false };
			output_["minecraft:block"]["description"]["states"][mod_id + ":south_east"] = { false, true };
			output_["minecraft:block"]["description"]["states"][mod_id + ":south_west"] = { false, true };
			output_["minecraft:block"]["description"]["states"][mod_id + ":north_west"] = { true, false };

			if (output_["minecraft:block"]["components"].contains("minecraft:custom_components"))
				output_["minecraft:block"]["components"]["minecraft:custom_components"].push_back({ "adk-lib:before_on_player_place_stairs" });
			else
				output_["minecraft:block"]["components"].update(
					helper_.CustomComponents(std::vector<std::string>{"adk-lib:before_on_player_place_stairs"})
				);

			nlohmann::json::object_t temp = {
			{"condition",
			 "q.block_state('minecraft:vertical_half') == 'top'"} };
			temp["components"].update(
				helper_.Scale(
					std::vector<int>{0, 1, 0},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);

			return output_;
		}
	};
} // namespace adk