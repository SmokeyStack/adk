#pragma once

#include <string>

#include "block/block.h"

namespace adk {
	/**
	 * @brief Represents a Stairs Block
	 */
	class BlockStairs : public Block {
	public:
		/**
		 * @brief Construct a new Stairs Block object
		 */
		BlockStairs() {}

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the block
		 *
		 * @return nlohmann::json
		 */
		nlohmann::json Generate(std::string mod_id, std::string id) override;
	};
} // namespace adk