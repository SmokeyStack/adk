#pragma once

#include "block/block_abstract_candle.h"

namespace adk {
	/**
	 * @brief Represents a Candle Block
	 */
	class BlockCandle : public BlockCandleAbstract {
	public:
		/**
		 * @brief Construct a new Candle Block object
		 *
		 * @param property BlockProperty
		 */
		BlockCandle() {}

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