#pragma once

#include <string>

#include "block.h"
#include "block_component.h"
#include "block_property.h"
#include "json.hpp"
#include "shared_construct.h"

namespace adk {
	/**
	 * @brief Represents a Plant Block
	 */
	class BlockPlant : public Block {
	public:
		BlockPlant() {};
		/**
		 * @brief Construct a new Plant Block object
		 *
		 * @param property BlockProperty
		 */
		BlockPlant(BlockProperty property) : Block(property) { internal_ = property; }

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

			BlockPlacementFilter filter;
			filter.allowed_faces.push_back(BlockAllowedFaces::UP);
			BlockDescriptor block_descriptor;
			block_descriptor.tags = { "dirt", "farmland" };
			filter.block_filter.push_back(block_descriptor);

			output_["minecraft:block"]["components"].update(
				helper_.PlacementFilter(filter)
			);

			return output_;
		}
	};
} // namespace adk