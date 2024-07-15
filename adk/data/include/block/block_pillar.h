#pragma once

#include "block/block.h"

namespace adk {
	/**
	 * @brief Represents a Pillar Block
	 */
	class BlockPillar : public Block {
	public:
		/**
		 * @brief Construct a new Pillar Block object
		 */
		BlockPillar() {}

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