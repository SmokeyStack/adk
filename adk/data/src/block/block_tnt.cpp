#include "block/block_tnt.h"

#include "block/component/custom.h"

namespace adk {
	nlohmann::json BlockTnt::Generate(std::string mod_id, std::string id) {
		auto& custom_component = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:custom_components"; });
		if (custom_component == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockCustom>();
			component->Add("adk-lib:on_player_interact_prime_tnt");
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockCustom* component = dynamic_cast<ComponentBlockCustom*>(custom_component->get());
			component->Add("adk-lib:on_player_interact_prime_tnt");
		}

		return Block::Generate(mod_id, id);
	}
} // namespace adk