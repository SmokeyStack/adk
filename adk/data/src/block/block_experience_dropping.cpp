#include "block/block_experience_dropping.h"

namespace adk {
	nlohmann::json BlockExperienceDropping::Generate(std::string mod_id, std::string id) {
		auto& custom_component = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:custom_components"; });
		if (custom_component == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockCustom>();
			component->Add("adk-lib:on_player_destroy_drop_experience");
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockCustom* component = dynamic_cast<ComponentBlockCustom*>(custom_component->get());
			component->Add("adk-lib:on_player_destroy_drop_experience");
		}

		auto& tags = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:tags"; });
		if (tags == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockTag>();
			component->Add("adk-lib:drop_experience_" + std::to_string(experienced_dropped_));
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockTag* component = dynamic_cast<ComponentBlockTag*>(tags->get());
			component->Add("adk-lib:drop_experience_" + std::to_string(experienced_dropped_));
		}

		return Block::Generate(mod_id, id);
	}
} // namespace adk