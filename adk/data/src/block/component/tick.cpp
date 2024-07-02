#include "block/component/tick.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockTick::Generate() {
		nlohmann::json::object_t output = { {"minecraft:tick", {{"interval_range", {interval_range_min_, interval_range_max_}}}} };

		if (!looping_) output["minecraft:tick"]["looping"] = looping_;

		return output;
	}
	std::string ComponentBlockTick::GetType() { return "minecraft:tick"; }
} // namespace adk