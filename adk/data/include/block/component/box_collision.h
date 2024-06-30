#pragma once

#include <variant>

#include "block/component/base.h"
#include "json.hpp"
#include "utility/vector3.h"

namespace adk {
	class ComponentBoxCollision : public Component {
	public:
		ComponentBoxCollision(bool value) { value_ = value; }
		ComponentBoxCollision(Vector3 origin, Vector3 size) { value_ = std::make_pair(origin, size); }
		~ComponentBoxCollision() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
		static void EnsureValidity(Vector3 origin, Vector3 size);
		static std::tuple<double, double, double> CombineOriginAndSize(Vector3 origin, Vector3 size);
	private:
		std::variant<bool, std::pair<Vector3, Vector3>> value_ = true;
	};
} // namespace adk