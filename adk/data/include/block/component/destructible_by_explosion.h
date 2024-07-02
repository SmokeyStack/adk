#pragma once

#include <variant>

#include "component.h"

namespace adk {
	class ComponentBlockDestructibleByExplosion : public Component {
	public:
		ComponentBlockDestructibleByExplosion(bool value) : explosion_resistance_(value) {}
		ComponentBlockDestructibleByExplosion(double explosion_resistance) : explosion_resistance_(explosion_resistance) {}
		~ComponentBlockDestructibleByExplosion() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::variant<bool, double> explosion_resistance_ = true;
	};
} // namespace adk