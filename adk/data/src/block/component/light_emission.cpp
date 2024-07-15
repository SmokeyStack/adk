#include "block/component/light_emission.h"

#include <spdlog/fmt/fmt.h>

namespace adk {
	nlohmann::json::object_t ComponentBlockLightEmission::Generate() {
		if (light_emission_ > 15 || light_emission_ < 0)
			throw std::runtime_error(fmt::format(
				"'minecraft:light_emission' can only be in range(0 - 15). Current value provided: {}",
				light_emission
			));

		nlohmann::json::object_t output = { {"minecraft:light_emission", light_emission_} };

		return output;
	}
	std::string ComponentBlockLightEmission::GetType() { return "minecraft:light_emission"; }
} // namespace adk