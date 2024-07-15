#include "block/component/crafting_table.h"

#include <spdlog/fmt/fmt.h>

namespace adk {
	nlohmann::json::object_t ComponentBlockCraftingTable::Generate() {
		nlohmann::json::object_t output = { {"minecraft:crafting_table", nlohmann::json::object()} };
		auto& crafting_table = output["minecraft:crafting_table"];
		crafting_table["table_name"] = table_name_;

		if (tags_.size() > 64)
			throw std::runtime_error(fmt::format(
				"'minecraft:crafting_table' -> 'crafting_tags' is limited to only 64 tags. Current size provided: {}", tags_.size()
			));

		crafting_table["crafting_tags"] = tags_;

		return output;
	}

	std::string ComponentBlockCraftingTable::GetType() { return "minecraft:crafting_table"; }
} // namespace adk