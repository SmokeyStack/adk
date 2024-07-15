#pragma once

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:light_emission" component
	 * The amount of light this block will emit in a range (0-15).
	 * Higher value means more light will be emitted.
	 */
	class ComponentBlockLightEmission : public Component {
	public:
		/**
		 * @brief "minecraft:light_emission" component
		 * @param value The amount of light this block will emit
		 */
		ComponentBlockLightEmission(int light_emission) : light_emission_(light_emission) {}
		~ComponentBlockLightEmission() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int light_emission_ = 0;
	};
} // namespace adk