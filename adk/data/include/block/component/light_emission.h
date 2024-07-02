#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockLightEmission : public Component {
	public:
		ComponentBlockLightEmission(int value) { light_emission = value; }
		~ComponentBlockLightEmission() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int light_emission = 0;
	};
} // namespace adk