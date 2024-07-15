#include "block/block_sugar_cane.h"

#include "block/component/custom.h"
#include "block/component/placement_filter.h"

namespace adk {
	nlohmann::json BlockSugarCane::Generate(std::string mod_id, std::string id) {
		auto property = std::make_unique<Property>();
		auto state = std::make_unique<StateIntRange>(mod_id + ":age", 0, 15);
		property->AddState(std::move(state));
		Block::AddProperty(std::move(property));

		ComponentBlockPlacementFilterCondition condition;
		BlockDescriptor block_descriptor;
		block_descriptor.tags = { "dirt", "sand" };
		condition.AddAllowedFaces(BlockFaces::UP).AddBlockFilter(block_descriptor);

		auto& placement_filter = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:placement_filter"; });
		if (placement_filter == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockPlacementFilter>();
			component->AddCondition(condition);
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockPlacementFilter* component = dynamic_cast<ComponentBlockPlacementFilter*>(placement_filter->get());
			component->AddCondition(condition);
		}

		auto& custom_component = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:custom_components"; });
		std::set<std::string> components = { "adk-lib:before_on_player_place_sugar_cane", "adk-lib:on_random_tick_sugar_cane" };
		if (custom_component == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockCustom>();
			component->Add(components);
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockCustom* component = dynamic_cast<ComponentBlockCustom*>(custom_component->get());
			component->Add(components);
		}

		return Block::Generate(mod_id, id);
	}
} // namespace adk