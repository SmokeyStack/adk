#include "block/component/box_collision.h"

#include <variant>

#include "json.hpp"
#include "utility/logger.h"

namespace adk {
	struct VisitBoxCollision {
		nlohmann::json::object_t& component;

		void operator()(const bool value) {
			component = { {"minecraft:collision_box", value} };
		}
		void operator()(const std::pair<Vector3, Vector3> value) const {
			ComponentBoxCollision::EnsureValidity(value.first, value.second);
			component = { { "minecraft:collision_box", {
				{ "origin", value.first.Get() },{ "size", value.second.Get() }
			}} };
		}
	};

	nlohmann::json::object_t ComponentBoxCollision::Generate() {
		nlohmann::json::object_t output;
		std::visit(VisitBoxCollision{ output }, value_);

		return output;
	}
	std::string ComponentBoxCollision::GetType() { return "minecraft:collision_box"; }

	void ComponentBoxCollision::EnsureValidity(Vector3 origin, Vector3 size) {
		if (origin.GetX() < -8 || origin.GetX() > 8 ||
			origin.GetY() < 0 || origin.GetY() > 16 ||
			origin.GetZ() < -8 || origin.GetZ() > 8)
			throw std::runtime_error(fmt::format(
				"{} - 'origin' must be in the range (-8, 0, -8) to (8, 16, 8), inclusive. Current value provided: {}",
				"minecraft:collision_box", origin.Get()
			));

		if ((origin.GetX() + size.GetX() < -8) ||
			(origin.GetX() + size.GetX() > 8) ||
			(origin.GetY() + size.GetY() < 0) ||
			(origin.GetY() + size.GetY() > 16) ||
			(origin.GetZ() + size.GetZ() < -8) ||
			(origin.GetZ() + size.GetZ() > 8))
			throw std::runtime_error(fmt::format(
				"{} - 'origin' + 'size' must be in the range (-8, 0, -8) to (8, 16, 8), inclusive. Current value provided: {}",
				"minecraft:collision_box", CombineOriginAndSize(origin, size)
			));
	}

	std::tuple<double, double, double> ComponentBoxCollision::CombineOriginAndSize(Vector3 origin, Vector3 size) {
		return { origin.GetX() + size.GetX(), origin.GetY() + size.GetY(), origin.GetZ() + size.GetZ() };
	}
} // namespace adk