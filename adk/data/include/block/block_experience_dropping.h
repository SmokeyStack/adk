#pragma once

#include <string>

#include "block.h"
#include "block_component.h"
#include "block_property.h"
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
			internal_ = property;
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

			if (output_["minecraft:block"]["components"].contains("minecraft:custom_components"))
				output_["minecraft:block"]["components"]["minecraft:custom_components"].push_back({ "adk-lib:on_player_destroy_drop_experience" });
			else
				output_["minecraft:block"]["components"].update(
					helper_.CustomComponents(std::vector<std::string>{"adk-lib:on_player_destroy_drop_experience"})
				);
			std::string tag = "adk-lib:drop_experience_" + std::to_string(experienced_dropped_);
			output_["minecraft:block"]["components"]["tag:" + tag] = nlohmann::json::object();

			return output_;
		}
	private:
		int experienced_dropped_;
	};
} // namespace adk