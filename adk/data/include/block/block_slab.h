#pragma once

#include "block/block.h"

namespace adk {
	/**
	 * @brief Represents a Slab Block
	 */
	class BlockSlab : public Block {
	public:
		/**
		 * @brief Construct a new Slab Block object
		 * 
		 * @param is_double_loot Identifier for the loot table.
		 * This is used to determine what to drop when the slab is in the double state.
		 */
		BlockSlab(std::string is_double_loot) : is_double_loot_(is_double_loot) {}

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the block
		 *
		 * @return nlohmann::json
		 */
		nlohmann::json Generate(std::string mod_id, std::string id) override;
	private:
		std::string is_double_loot_;
	};
} // namespace adk