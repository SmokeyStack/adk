#include "block/component/box_selection.h"

#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ranges.h>

namespace adk {
	struct VisitBoxSelection {
		nlohmann::json::object_t& component;
		void operator()(const bool value) {
			component = { {"minecraft:selection_box", value} };
		}
		void operator()(const std::pair<Vector3, Vector3> value) const {
			ComponentBlockBoxSelection::EnsureValidity(value.first, value.second);
			component = { { "minecraft:selection_box", {
				{ "origin", value.first.Get() },{ "size", value.second.Get() }
			}} };
		}
	};
	nlohmann::json::object_t ComponentBlockBoxSelection::Generate() {
		nlohmann::json::object_t output;
		std::visit(VisitBoxSelection{ output }, selection_);

		return output;
	}
	std::string ComponentBlockBoxSelection::GetType() { return "minecraft:selection_box"; }
	void ComponentBlockBoxSelection::EnsureValidity(Vector3 origin, Vector3 size) {
		if (origin.GetX() < -8 || origin.GetX() > 8 ||
			origin.GetY() < 0 || origin.GetY() > 16 ||
			origin.GetZ() < -8 || origin.GetZ() > 8)
			throw std::runtime_error(fmt::format(
				"{} - 'origin' must be in the range (-8, 0, -8) to (8, 16, 8), inclusive. Current value provided: {}",
				"minecraft:selection_box", origin.Get()
			));
		if ((origin.GetX() + size.GetX() < -8) ||
			(origin.GetX() + size.GetX() > 8) ||
			(origin.GetY() + size.GetY() < 0) ||
			(origin.GetY() + size.GetY() > 16) ||
			(origin.GetZ() + size.GetZ() < -8) ||
			(origin.GetZ() + size.GetZ() > 8))
			throw std::runtime_error(fmt::format(
				"{} - 'origin' + 'size' must be in the range (-8, 0, -8) to (8, 16, 8), inclusive. Current value provided: {}",
				"minecraft:selection_box", CombineOriginAndSize(origin, size)
			));
	}
	std::tuple<double, double, double> ComponentBlockBoxSelection::CombineOriginAndSize(Vector3 origin, Vector3 size) {
		return { origin.GetX() + size.GetX(), origin.GetY() + size.GetY(), origin.GetZ() + size.GetZ() };
	}
	ComponentBlockBoxSelection& ComponentBlockBoxSelection::SetSelection(bool selection) {
		selection_ = selection;

		return *this;
	}
	ComponentBlockBoxSelection& ComponentBlockBoxSelection::SetSelection(Vector3 origin, Vector3 size) {
		EnsureValidity(origin, size);
		selection_ = std::make_pair(origin, size);

		return *this;
	}
} // namespace adk