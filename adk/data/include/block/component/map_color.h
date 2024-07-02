#pragma once

#include <variant>

#include "component.h"
#include "utility/vector3.h"

namespace adk {
	class ComponentBlockMapColor : public Component {
	public:
		ComponentBlockMapColor(std::string map_color) : map_color_(map_color) {}
		ComponentBlockMapColor(Vector3 map_color) : map_color_(map_color) {}
		~ComponentBlockMapColor() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::variant<std::string, Vector3> map_color_;
	};
} // namespace adk