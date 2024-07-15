#include "block/component/flammable.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockFlammable::Generate() {
		nlohmann::json::object_t output = { {"minecraft:flammable", nlohmann::json::object()} };

		if (catch_chance_modifier_ != 5) output["minecraft:flammable"]["catch_chance_modifier"] = catch_chance_modifier_;
		if (destroy_chance_modifier_ != 20) output["minecraft:flammable"]["destroy_chance_modifier"] = destroy_chance_modifier_;

		return output;
	}
	std::string ComponentBlockFlammable::GetType() { return "minecraft:flammable"; }
	ComponentBlockFlammable& ComponentBlockFlammable::SetCatchChanceModifier(int modifier) {
		catch_chance_modifier_ = modifier;

		return *this;
	}
	ComponentBlockFlammable& ComponentBlockFlammable::SetDestroyChanceModifier(int modifier) {
		destroy_chance_modifier_ = modifier;

		return *this;
	}
} // namespace adk