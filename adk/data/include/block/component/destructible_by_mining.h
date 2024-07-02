#pragma once

#include <variant>

#include "component.h"

namespace adk {
	class ComponentBlockDestructibleByMining : public Component {
	public:
		ComponentBlockDestructibleByMining(bool value) : seconds_to_destroy_(value) {}
		ComponentBlockDestructibleByMining(double seconds_to_destroy) : seconds_to_destroy_(seconds_to_destroy) {}
		~ComponentBlockDestructibleByMining() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::variant<bool, double> seconds_to_destroy_ = true;
	};
} // namespace adk