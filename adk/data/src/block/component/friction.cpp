#include "block/component/friction.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockFriction::Generate() {
		if (friction_ > 0.9 || friction_ < 0.0)
			throw std::runtime_error(fmt::format(
				"'minecraft:friction' can only be in range(0.9 - 0.9). Current value provided: {}",
				friction_
			));

		nlohmann::json::object_t output = { {"minecraft:friction", friction_} };

		return output;
	}
	std::string ComponentBlockFriction::GetType() { return "minecraft:friction"; }
} // namespace adk