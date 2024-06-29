#pragma once

#include "block/component/base.h"
#include "json.hpp"

namespace adk {
	class ComponentLightDampening : public Component {
	public:
		ComponentLightDampening(int value) { value_ = value; }
		~ComponentLightDampening() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int value_ = 15;
	};
} // namespace adk