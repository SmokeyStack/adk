#pragma once

#include "block/block.h"

namespace adk {
	/**
	 * @brief Represents a Torch Block
	 */
	class BlockTorch : public Block {
	public:
		/**
		 * @brief Construct a new Torch Block object
		 *
		 * @param property BlockProperty
		 */
		BlockTorch() {}

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