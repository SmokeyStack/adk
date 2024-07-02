#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockLightDampening : public Component {
	public:
		ComponentBlockLightDampening(int light_dampening) : light_dampening_(light_dampening) {}
		~ComponentBlockLightDampening() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int light_dampening_ = 15;
	};
} // namespace adk