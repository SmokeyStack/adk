#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockFriction : public Component {
	public:
		ComponentBlockFriction(double value) : friction_(value) {}
		~ComponentBlockFriction() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		double friction_ = 0.4;
	};
} // namespace adk