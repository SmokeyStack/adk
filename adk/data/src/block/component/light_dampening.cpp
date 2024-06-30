#include "block/component/light_dampening.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t ComponentLightDampening::Generate() {
		if (value_ > 15 || value_ < 0) {
			log::error("\t'minecraft:light_dampening' can only be in range(0 - 15). Current value provided: {}", value_);
			exit(EXIT_FAILURE);
		}

		nlohmann::json::object_t output = { {"minecraft:light_dampening", value_} };

		return output;
	}
	std::string ComponentLightDampening::GetType() { return "minecraft:light_dampening"; }
} // namespace adk