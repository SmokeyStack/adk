#pragma once

#include "block/block.h"

namespace adk {
	/**
	 * @brief Represents an Abstract Candle Block
	 */
	class BlockCandleAbstract : public Block {
	public:
		/**
		 * @brief Construct a new Abstract Candle Block object
		 *
		 * @param property BlockProperty
		 */
		BlockCandleAbstract() {}

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