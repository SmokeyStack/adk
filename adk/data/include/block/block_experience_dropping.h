#pragma once

#include "block/block.h"
#include "component/custom.h"
#include "component/tag.h"

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
		 */
		BlockExperienceDropping(int experienced_dropped) : experienced_dropped_(experienced_dropped) {}

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
		int experienced_dropped_;
	};
} // namespace adk