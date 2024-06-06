#pragma once

#include <string>

#include "block.h"
#include "block/block_abstract_candle.h"
#include "block_component.h"
#include "block_property.h"
#include "json.hpp"
#include "shared_construct.h"

namespace adk {
	/**
	 * @brief Represents a Candle Block
	 */
	class BlockCandle: public BlockCandleAbstract {
	public:
		/**
		 * @brief Construct a new Plant Block object
		 *
		 * @param property BlockProperty
		 */
		BlockCandle(BlockProperty property) : BlockCandleAbstract(property) { internal_ = property; }

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
			output_ = BlockCandleAbstract::Generate(mod_id, id);

			output_["minecraft:block"]["description"]["states"][mod_id + ":candles"]["values"]["min"] = 1;
			output_["minecraft:block"]["description"]["states"][mod_id + ":candles"]["values"]["max"] = 4;
			nlohmann::json::object_t temp = {
			{"condition",
			 "q.block_state('" + mod_id + ":candles') == 1"} };
			temp["components"].update(
				helper_.BoxCollision(
					std::vector<int>{-1, 0, -1},
					std::vector<int>{2, 6, 2},
					id
				)
			);
			temp["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-1, 0, -1},
					std::vector<int>{2, 6, 2},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('" + mod_id + ":candles') == 2"} };
			temp["components"].update(
				helper_.BoxCollision(
					std::vector<int>{-3, 0, -1},
					std::vector<int>{6, 6, 3},
					id
				)
			);
			temp["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-3, 0, -1},
					std::vector<int>{6, 6, 3},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('" + mod_id + ":candles') == 3"} };
			temp["components"].update(
				helper_.BoxCollision(
					std::vector<int>{-2, 0, -2},
					std::vector<int>{5, 6, 5},
					id
				)
			);
			temp["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-2, 0, -2},
					std::vector<int>{5, 6, 5},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('" + mod_id + ":candles') == 4"} };
			temp["components"].update(
				helper_.BoxCollision(
					std::vector<int>{-3, 0, -3},
					std::vector<int>{6, 6, 5},
					id
				)
			);
			temp["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-3, 0, -3},
					std::vector<int>{6, 6, 5},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			for (const auto& [key, value] : output_["minecraft:block"]["permutations"].items()) {
				if (value.contains("condition") && value["condition"].dump() == fmt::format("\"q.block_state('{namespace}:lit')\"", fmt::arg("namespace", mod_id))) {
					/*value["components"].update(
						helper_.CustomComponents({ "adk-lib:on_player_interact_candle" })
					);*/

					value["components"] = UpdateCustomComponents(value["components"], { "adk-lib:on_player_interact_candle" });
				}
			}
			output_["minecraft:block"]["components"] = UpdateCustomComponents(output_["minecraft:block"]["components"], { "adk-lib:on_player_interact_candle" });

			return output_;
		}
	};
} // namespace adk