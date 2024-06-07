#pragma once

#include <string>

#include "block/block.h"
#include "block/block_component.h"
#include "block/block_property.h"
#include "json.hpp"
#include "shared_construct.h"

namespace adk {
	/**
	 * @brief Represents an Experience Dropping Block
	 */
	class BlockExperienceDropping : public Block {
	public:
		/**
		 * @brief Construct a new Experience Dropping Block object
		 *
		 * @param experienced_dropped Amount of experience dropped
		 *
		 * @param property BlockProperty
		 */
		BlockExperienceDropping(int experienced_dropped, BlockProperty property) : Block(property) {
			experienced_dropped_ = experienced_dropped;
		}

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

			output_["minecraft:block"]["components"] = UpdateCustomComponents(output_["minecraft:block"]["components"], { "adk-lib:on_player_destroy_drop_experience" });
			std::string tag = "adk-lib:drop_experience_" + std::to_string(experienced_dropped_);
			output_["minecraft:block"]["components"]["tag:" + tag] = nlohmann::json::object();

			return output_;
		}
	private:
		int experienced_dropped_;
	};
} // namespace adk