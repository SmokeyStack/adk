#pragma once

#include <string>

#include "block.h"
#include "block_component.h"
#include "block_property.h"
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
		BlockTnt(BlockProperty property) : Block(property) { internal_ = property; }

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

			if (output_["minecraft:block"]["components"].contains("minecraft:custom_components"))
				output_["minecraft:block"]["components"]["minecraft:custom_components"].push_back({ "adk-lib:on_player_interact_prime_tnt"});
			else
				output_["minecraft:block"]["components"].update(
					helper_.CustomComponents(std::vector<std::string>{"adk-lib:on_player_interact_prime_tnt"})
				);

			return output_;
		}
	};
} // namespace adk