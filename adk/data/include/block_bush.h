#pragma once	

#include "block.h"
#include "block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Bush Block
	 */
	class BlockBush : public Block {
	public:
		BlockBush() {};
		/**
		 * @brief Construct a new Bush Block object
		 *
		 * @param property BlockProperty
		 */
		BlockBush(BlockProperty property) { internal_ = property; }

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

			output_["minecraft:block"]["components"]["minecraft:placement_filter"]
				["conditions"] = { {{"allowed_faces", nlohmann::json::array({"up"})},
								   {"block_filter",
									nlohmann::json::array({{{"tags", "q.any_tag('dirt')"}},
												 {{"tags", "q.any_tag('grass')"}}})}} };

			return j;
		}
	};
} // namespace adk