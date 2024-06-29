#pragma once

#include "block/component/base.h"
#include "json.hpp"

namespace adk {
	class ComponentLightEmission : public Component {
	public:
		ComponentLightEmission(int value) { value_ = value; }
		~ComponentLightEmission() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int value_ = 15;
	};
} // namespace adk