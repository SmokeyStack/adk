#pragma once

#include <string>

#include "block.h"
#include "block_component.h"
#include "block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Pillar Block
	 */
	class BlockPillar : public Block {
	public:
		/**
		 * @brief Construct a new Pillar Block object
		 *
		 * @param property BlockProperty
		 */
		BlockPillar(BlockProperty property) : Block(property) {}

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

			output_["minecraft:block"]["description"]["traits"]["minecraft:placement_position"]["enabled_states"] = { "minecraft:block_face" };
			nlohmann::json::object_t temp = {
			{"condition",
			 "q.block_state('minecraft:block_face') == 'north' || q.block_state('minecraft:block_face') == 'south'"} };
			temp["components"].update(
				helper_.Rotation(
					std::vector<int>{90, 0, 0},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('minecraft:block_face') == 'east' || q.block_state('minecraft:block_face') == 'west'"} };
			temp["components"].update(
				helper_.Rotation(
					std::vector<int>{0, 0, 270},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);

			return output_;
		}
	};
} // namespace adk