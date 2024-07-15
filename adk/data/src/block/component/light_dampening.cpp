#include "block/component/light_dampening.h"

#include <spdlog/fmt/fmt.h>

namespace adk {
	nlohmann::json::object_t ComponentBlockLightDampening::Generate() {
		if (light_dampening_ > 15 || light_dampening_ < 0)
			throw std::runtime_error(fmt::format(
				"'minecraft:light_dampening' can only be in range(0 - 15). Current value provided: {}",
				light_dampening_
			));

		nlohmann::json::object_t output = { {"minecraft:light_dampening", light_dampening_} };

		return output;
	}
	std::string ComponentBlockLightDampening::GetType() { return "minecraft:light_dampening"; }
} // namespace adk