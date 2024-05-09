#pragma once

#include <string>

#include "block_component.h"
#include "block_plant.h"
#include "block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Mushroom Block
	 */
	class BlockMushroom: public BlockPlant {
	public:
		/**
		 * @brief Construct a new Plant Block object
		 *
		 * @param property BlockProperty
		 */
		BlockMushroom(BlockProperty property) : BlockPlant(property) { internal_ = property; }

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
			output_ = BlockPlant::Generate(mod_id, id);

			output_["minecraft:block"]["components"].update(
				helper_.BoxCollision(false)
			);
			output_["minecraft:block"]["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-3, 0, -3}, 
					std::vector<int>{6, 6, 6},
					id
				)
			);

			return output_;
		}
	};
} // namespace adk