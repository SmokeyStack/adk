#pragma once

#include <variant>

#include "component.h"
#include "utility/vector3.h"

namespace adk {
	class ComponentBlockBoxCollision : public Component {
	public:
		ComponentBlockBoxCollision(bool collision) : collision_(collision) {}
		ComponentBlockBoxCollision(Vector3 origin, Vector3 size) : collision_(std::make_pair(origin, size)) {}
		~ComponentBlockBoxCollision() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
		static void EnsureValidity(Vector3 origin, Vector3 size);
		static std::tuple<double, double, double> CombineOriginAndSize(Vector3 origin, Vector3 size);
	private:
		std::variant<bool, std::pair<Vector3, Vector3>> collision_ = true;
	};
} // namespace adk