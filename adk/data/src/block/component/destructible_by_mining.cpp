#include "block/component/destructible_by_mining.h"

namespace adk {
	struct VisitDestructibleByMining {
		nlohmann::json::object_t& component;

		void operator()(const bool value) const {
			component = { {"minecraft:destructible_by_mining", value} };
		}
		void operator()(const double value) const {
			component = { { "minecraft:destructible_by_mining", {
				{ "seconds_to_destroy", value }
			}} };
		}
	};

	nlohmann::json::object_t ComponentBlockDestructibleByMining::Generate() {
		nlohmann::json::object_t output;
		std::visit(VisitDestructibleByMining{ output }, seconds_to_destroy_);

		return output;
	}
	std::string ComponentBlockDestructibleByMining::GetType() { return "minecraft:destructible_by_explosion"; }
} // namespace adk