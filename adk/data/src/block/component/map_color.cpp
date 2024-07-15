#include "block/component/map_color.h"

namespace adk {
	struct VisitMapColor {
		nlohmann::json::object_t& component;

		void operator()(const std::string value) {
			component = { {"minecraft:map_color", value} };
		}
		void operator()(const Vector3 value) const {
			component = { { "minecraft:map_color", value.Get()} };
		}
	};

	nlohmann::json::object_t ComponentBlockMapColor::Generate() {
		nlohmann::json::object_t output;
		std::visit(VisitMapColor{ output }, map_color_);

		return output;
	}
	std::string ComponentBlockMapColor::GetType() { return "minecraft:map_color"; }
} // namespace adk