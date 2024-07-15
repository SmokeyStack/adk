#pragma once

#include "block/block_plant.h"

namespace adk {
	/**
	 * @brief Represents a Mushroom Block
	 */
	class BlockMushroom : public BlockPlant {
	public:
		/**
		 * @brief Construct a new Mushroom Block object
		 */
		BlockMushroom() {}

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