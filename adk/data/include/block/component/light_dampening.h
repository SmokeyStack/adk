#pragma once

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:light_dampening" component
	 * The amount that light will be dampened when it passes through the block, in a range (0-15).
	 * Higher value means the light will be dampened more.
	 */
	class ComponentBlockLightDampening : public Component {
	public:
		/**
		 * @brief "minecraft:light_dampening" component
		 * @param light_dampening The amount that light will be dampened when it passes through the block
		 */
		ComponentBlockLightDampening(int light_dampening) : light_dampening_(light_dampening) {}
		~ComponentBlockLightDampening() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int light_dampening_ = 15;
	};
} // namespace adk