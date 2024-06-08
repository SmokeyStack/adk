#pragma once

#include <string>

#include "block/block.h"
#include "block/block_component.h"
#include "block/block_property.h"
#include "json.hpp"

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
		BlockTorch(BlockProperty property) : Block(property) {}

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

			output_["minecraft:block"]["description"]["traits"]["minecraft:placement_position"]["enabled_states"] = { "minecraft:block_face" };
			nlohmann::json::object_t temp = {
			{"condition",
			 "q.block_state('minecraft:block_face') == 'north'"} };
			temp["components"].update(
				helper_.Rotation(
					std::vector<int>{0, 90, 0},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('minecraft:block_face') == 'east'"} };
			temp["components"].update(
				helper_.Rotation(
					std::vector<int>{0, 0, 0},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('minecraft:block_face') == 'south'"} };
			temp["components"].update(
				helper_.Rotation(
					std::vector<int>{0, 270, 0},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			temp = {
			{"condition",
			 "q.block_state('minecraft:block_face') == 'west'"} };
			temp["components"].update(
				helper_.Rotation(
					std::vector<int>{0, 180, 0},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);
			std::string condition = fmt::format(
				"q.block_state('{state}') == 'north' || q.block_state('{state}') == 'east' || q.block_state('{state}') == 'south' || q.block_state('{state}') == 'west'",
				fmt::arg("state", "minecraft:block_face")
			);
			temp = { {"condition",condition} };
			temp["components"].update(
				helper_.BoxSelection(
					std::vector<int>{2, 3, -3},
					std::vector<int>{6, 10, 6},
					id
				)
			);
			output_["minecraft:block"]["permutations"].push_back(temp);

			output_["minecraft:block"]["components"].update(
				helper_.BoxCollision(false)
			);
			output_["minecraft:block"]["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-2, 0, -2},
					std::vector<int>{4, 10, 4},
					id
				)
			);
			output_["minecraft:block"]["components"].update(
				helper_.Tick(20, 20, true)
			);
			output_["minecraft:block"]["components"] = UpdateCustomComponents(output_["minecraft:block"]["components"], { "adk-lib:on_tick_torch_particles" });

			return output_;
		}
	};
} // namespace adk