#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockEntityFallOn : public Component {
	public:
		ComponentBlockEntityFallOn() {}
		ComponentBlockEntityFallOn(int min_fall_distance) : min_fall_distance_(min_fall_distance) {}
		~ComponentBlockEntityFallOn() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int min_fall_distance_ = 0;
	};
} // namespace adk