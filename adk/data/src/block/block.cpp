#include "block/block.h"

#include "utility/logger.h"

namespace adk {
	std::string Block::GetType() { return "block"; }

	nlohmann::json Block::Generate(std::string mod_id, std::string id) {
		output_["format_version"] = "1.21.10";
		auto& block = output_["minecraft:block"];
		block["description"]["identifier"] = mod_id + ":" + id;
		block["components"] = nlohmann::json::object();

		for (const auto& component : components_) {
			//log::info("\tApplying '{}' component", component->GetType());
			block["components"].update(component->Generate());
		}

		return output_;
	}

	Block& Block::AddComponent(std::unique_ptr<Component> component) {
		components_.push_back(std::move(component));

		return *this;
	}
} // namespace adk