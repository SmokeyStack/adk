#pragma once

#include "block/block.h"
#include "block/block_component.h"
#include "block/block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Abstract Candle Block
	 */
	class BlockCandleAbstract : public Block {
	public:
		BlockCandleAbstract() {};
		/**
		 * @brief Construct a new Plant Block object
		 *
		 * @param property BlockProperty
		 */
		BlockCandleAbstract(BlockProperty property) : Block(property) { internal_ = property; }

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

			output_["minecraft:block"]["description"]["states"][mod_id + ":lit"] = { false, true };
			nlohmann::json::object_t temp = {
			{"condition",
			 "q.block_state('" + mod_id + ":lit')"} };
			temp["components"].update(
				helper_.Tick(20, 100)
			);
			temp["components"] = UpdateCustomComponents(temp["components"], { "adk-lib:on_tick_candle_particles" });
			output_["minecraft:block"]["permutations"].push_back(temp);

			return output_;
		}
	};
} // namespace adk