#include "block/component/tick.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockTick::Generate() {
		nlohmann::json::object_t output = { {"minecraft:tick", {{"interval_range", {interval_range_min_, interval_range_max_}}}} };

		if (!looping_) output["minecraft:tick"]["looping"] = looping_;

		return output;
	}
	std::string ComponentBlockTick::GetType() { return "minecraft:tick"; }
	ComponentBlockTick& ComponentBlockTick::SetIntervalRange(int min, int max) {
		interval_range_min_ = min;
		interval_range_max_ = max;

		return *this;
	}
	ComponentBlockTick& ComponentBlockTick::SetLooping(bool loop) {
		looping_ = loop;

		return *this;
	}
} // namespace adk