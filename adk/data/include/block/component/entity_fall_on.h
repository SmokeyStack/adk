#pragma once

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:entity_fall_on" component
	 * Triggers the specified custom component when an entity falls and lands on the block.
	 */
	class ComponentBlockEntityFallOn : public Component {
	public:
		/**
		 * @brief "minecraft:entity_fall_on" component
		 * Triggers the specified custom component when an entity falls and lands on the block.
		 */
		ComponentBlockEntityFallOn() {}

		/**
		 * @brief "minecraft:entity_fall_on" component
		 *
		 * @param min_fall_distance Determines the minimum distance an entity must fall to trigger the specified custom component
		 */
		ComponentBlockEntityFallOn(int min_fall_distance) : min_fall_distance_(min_fall_distance) {}
		~ComponentBlockEntityFallOn() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int min_fall_distance_ = 0;
	};
} // namespace adk