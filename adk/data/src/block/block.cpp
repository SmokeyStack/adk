#include "block/block.h"

#include "utility/logger.h"

namespace adk {
	Block::Block(Property property) { internal_ = property; }

	std::string Block::GetType() { return "block"; }

	nlohmann::json Block::Generate(std::string mod_id, std::string id) {
		output_["format_version"] = "1.21.10";
		auto& block = output_["minecraft:block"];
		block["description"]["identifier"] = mod_id + ":" + id;
		block["components"] = nlohmann::json::object();

		for (const auto& component : internal_.GetComponents()) {
			//log::info("\tApplying '{}' component", component->GetType());
			block["components"].update(component->Generate());
		}

		return output_;
	}
} // namespace adk