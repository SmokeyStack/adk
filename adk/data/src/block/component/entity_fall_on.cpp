#include "block/component/entity_fall_on.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockEntityFallOn::Generate() {
		nlohmann::json::object_t output = { {"minecraft:entity_fall_on", nlohmann::json::object()} };

		if (min_fall_distance_ != 0) output["minecraft:entity_fall_on"]["min_fall_distance"] = min_fall_distance_;

		return output;
	}
	std::string ComponentBlockEntityFallOn::GetType() { return "minecraft:entity_fall_on"; }
} // namespace adk