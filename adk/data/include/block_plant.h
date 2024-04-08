#pragma once	

#include "block.h"
#include "block_property.h"
#include "json.hpp"

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
		BlockPlant(BlockProperty property) { internal_ = property; }

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

			BlockPlacementFilter filter = {
				std::vector<BlockAllowedFaces>{BlockAllowedFaces::UP}
			};
			filter.tags = { "dirt","grass" };

			output_["minecraft:block"]["components"].update(helper_.PlacementFilter(filter));

			return output_;
		}
	};
} // namespace adk