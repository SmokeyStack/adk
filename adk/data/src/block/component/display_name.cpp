#include "block/component/display_name.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockDisplayName::Generate() {
		nlohmann::json::object_t output = { {"minecraft:display_name", display_name_} };

		return output;
	}
	std::string ComponentBlockDisplayName::GetType() { return "minecraft:display_name"; }
} // namespace adk