#pragma once

#include <variant>

#include "component.h"
#include "utility/vector3.h"

namespace adk {
	class ComponentBlockBoxSelection : public Component {
	public:
		ComponentBlockBoxSelection(bool selection) : selection_(selection) {}
		ComponentBlockBoxSelection(Vector3 origin, Vector3 size) : selection_(std::make_pair(origin, size)) {}
		~ComponentBlockBoxSelection() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
		static void EnsureValidity(Vector3 origin, Vector3 size);
		static std::tuple<double, double, double> CombineOriginAndSize(Vector3 origin, Vector3 size);
	private:
		std::variant<bool, std::pair<Vector3, Vector3>> selection_ = true;
	};
} // namespace adk