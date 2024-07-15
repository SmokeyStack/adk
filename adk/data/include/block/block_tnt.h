#pragma once

#include "block/block.h"

namespace adk {
	/**
	 * @brief Represents a TnT Block
	 */
	class BlockTnt : public Block {
	public:
		/**
		 * @brief Construct a new Tnt Block object
		 */
		BlockTnt() {}

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