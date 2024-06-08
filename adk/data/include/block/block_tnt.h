#pragma once

#include <string>

#include "block/block.h"
#include "block/block_component.h"
#include "block/block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a TnT Block
	 */
	class BlockTnt : public Block {
	public:
		/**
		 * @brief Construct a new Tnt Block object
		 *
		 * @param property BlockProperty
		 */
		BlockTnt(BlockProperty property) : Block(property) {}

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

			output_["minecraft:block"]["components"] = UpdateCustomComponents(output_["minecraft:block"]["components"], { "adk-lib:on_player_interact_prime_tnt" });

			return output_;
		}
	};
} // namespace adk