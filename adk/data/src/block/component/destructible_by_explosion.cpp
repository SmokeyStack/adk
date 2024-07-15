#include "block/component/destructible_by_explosion.h"

namespace adk {
	struct VisitDestructibleByExplosion {
		nlohmann::json::object_t& component;

		void operator()(const bool value) const {
			component = { {"minecraft:destructible_by_explosion", value} };
		}
		void operator()(const double value) const {
			component = { { "minecraft:destructible_by_explosion", {
				{ "explosion_resistance", value }
			}} };
		}
	};
	nlohmann::json::object_t ComponentBlockDestructibleByExplosion::Generate() {
		nlohmann::json::object_t output;
		std::visit(VisitDestructibleByExplosion{ output }, explosion_resistance_);

		return output;
	}
	std::string ComponentBlockDestructibleByExplosion::GetType() { return "minecraft:destructible_by_explosion"; }
} // namespace adk