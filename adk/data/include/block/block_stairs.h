#pragma once

#include "block/block.h"
#include "block/block_component.h"
#include "block/block_property.h"
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
		BlockStairs(BlockProperty property) : Block(property) {}

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
			output_["minecraft:block"]["description"]["states"][mod_id + ":shape"] = { "straight", "inner_left","inner_right","outer_left","outer_right" };
			output_["minecraft:block"]["description"]["states"][mod_id + ":south"] = { false, true };
			output_["minecraft:block"]["components"] = UpdateCustomComponents(output_["minecraft:block"]["components"], { "adk-lib:before_on_player_place_stairs" });

			return output_;
		}
	};
} // namespace adk