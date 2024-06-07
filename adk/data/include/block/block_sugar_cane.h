#pragma once

#include "block/block.h"
#include "block/block_component.h"
#include "block/block_property.h"
#include "json.hpp"
#include "shared_construct.h"

namespace adk {
	/**
	 * @brief Represents a Sugar Cane Block
	 */
	class BlockSugarCane : public Block {
	public:
		/**
		 * @brief Construct a new Plant Block object
		 *
		 * @param property BlockProperty
		 */
		BlockSugarCane(BlockProperty property) : Block(property) {}

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

			output_["minecraft:block"]["description"]["states"][mod_id + ":age"]["values"]["min"] = 0;
			output_["minecraft:block"]["description"]["states"][mod_id + ":age"]["values"]["max"] = 15;

			BlockPlacementFilter filter;
			filter.allowed_faces.push_back(BlockAllowedFaces::UP);
			BlockDescriptor block_descriptor;
			block_descriptor.tags = { "dirt", "sand" };
			filter.block_filter.push_back(block_descriptor);
			filter.block_filter.push_back(mod_id + ":" + id);

			output_["minecraft:block"]["components"].update(
				helper_.PlacementFilter(filter)
			);
			output_["minecraft:block"]["components"] = UpdateCustomComponents(output_["minecraft:block"]["components"], { "adk-lib:before_on_player_place_sugar_cane","adk-lib:on_random_tick_sugar_cane" });

			return output_;
		}
	};
} // namespace adk