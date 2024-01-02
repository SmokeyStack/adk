#pragma once

#include "block.h"
#include "block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Axis Block
	 */
	class BlockAxis : public Block {
	public:
		BlockAxis() {}

		/**
		 * @brief Construct a new Axis Block object
		 *
		 * @param property BlockProperty
		 */
		BlockAxis(BlockProperty property) { internal_ = property; }

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the block
		 *
		 * @return json
		 */
		nlohmann::json Generate(std::string mod_id, std::string id) {
			output_ = Block::Generate(mod_id, id);

			// Properties
			output_["minecraft:block"]["description"]["states"][mod_id + ":axis"] = nlohmann::json::array({ 0, 1, 2 });

			// Components
			output_["minecraft:block"]["components"]["minecraft:on_player_placing"]["event"] = mod_id + ":set_axis";

			// Events
			output_["minecraft:block"]["events"][mod_id + ":set_axis"]["set_block_state"][mod_id + ":axis"] = "math.floor(q.block_face/2)";

			// Permutations
			nlohmann::json::object_t permutation = { {"condition", "q.block_state('" + mod_id + ":axis') == 0"} };
			permutation["components"].update(helper_.Rotation(std::vector<int>{0, 0, 0}, id));
			output_["minecraft:block"]["permutations"].push_back(permutation);
			permutation = { {"condition", "q.block_state('" + mod_id + ":axis') == 1"} };
			permutation["components"].update(helper_.Rotation(std::vector<int>{90, 0, 0}, id));
			output_["minecraft:block"]["permutations"].push_back(permutation);
			permutation = { {"condition", "q.block_state('" + mod_id + ":axis') == 2"} };
			permutation["components"].update(helper_.Rotation(std::vector<int>{0, 0, 90}, id));
			output_["minecraft:block"]["permutations"].push_back(permutation);

			return output_;
		}
	};
} // namespace adk