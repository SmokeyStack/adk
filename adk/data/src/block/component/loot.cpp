#include "block/component/loot.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockLoot::Generate() {
		nlohmann::json::object_t output = { {"minecraft:loot", loot_} };

		return output;
	}
	std::string ComponentBlockLoot::GetType() { return "minecraft:loot"; }
} // namespace adk