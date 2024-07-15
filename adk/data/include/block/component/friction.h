#pragma once

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:friction" component
	 * Describes the friction for this block in a range of (0.0-0.9).
	 * Friction affects an entity's movement speed when it travels on the block.
	 * Greater value results in more friction.
	 */
	class ComponentBlockFriction : public Component {
	public:
		/**
		 * @brief "minecraft:friction" component
		 * 
		 * @param value The friction value
		 */
		ComponentBlockFriction(double value) : friction_(value) {}
		~ComponentBlockFriction() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		double friction_ = 0.4;
	};
} // namespace adk