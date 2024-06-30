#include "block/component/light_emission.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t ComponentLightEmission::Generate() {
		if (value_ > 15 || value_ < 0) {
			log::error("\t'minecraft:light_emission' can only be in range(0 - 15). Current value provided: {}", value_);
			exit(EXIT_FAILURE);
		}

		nlohmann::json::object_t output = { {"minecraft:light_emission", value_} };

		return output;
	}
	std::string ComponentLightEmission::GetType() { return "minecraft:light_emission"; }
} // namespace adk