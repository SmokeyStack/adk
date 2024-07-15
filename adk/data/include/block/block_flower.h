#pragma once

#include "block/block_plant.h"

namespace adk {
	/**
	 * @brief Represents a Flower Block
	 */
	class BlockFlower : public BlockPlant {
	public:
		/**
		 * @brief Construct a new Flower Block object
		 */
		BlockFlower() {}

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