#pragma once

#include <string>

#include "block/block_component.h"
#include "block/block_plant.h"
#include "block/block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Flower Block
	 */
	class BlockFlower : public BlockPlant {
	public:
		/**
		 * @brief Construct a new Flower Block object
		 *
		 * @param property BlockProperty
		 */
		BlockFlower(BlockProperty property) : BlockPlant(property) {}

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
				helper_.Translation(std::vector<double>{0.0, -0.0625, 0.0})
			);
			output_["minecraft:block"]["components"].update(
				helper_.BoxCollision(false)
			);
			output_["minecraft:block"]["components"].update(
				helper_.BoxSelection(
					std::vector<int>{-3, 0, -3},
					std::vector<int>{6, 10, 6},
					id
				)
			);

			return output_;
		}
	};
} // namespace adk