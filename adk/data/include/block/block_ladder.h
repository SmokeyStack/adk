#pragma once

#include "block/block.h"

namespace adk {
	/**
	 * @brief Represents a Ladder Block
	 */
	class BlockLadder : public Block {
	public:
		/**
		 * @brief Construct a new Ladder Block object
		 */
		BlockLadder() {}
		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the block
		 *
		 * @return nlohmann::json
		 */
		nlohmann::json Generate(std::string mod_id, std::string id);
	};
} // namespace adk