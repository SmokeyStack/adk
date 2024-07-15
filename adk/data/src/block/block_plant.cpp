#include "block/block_plant.h"

#include "block/component/placement_filter.h"

namespace adk {
	nlohmann::json BlockPlant::Generate(std::string mod_id, std::string id) {
		ComponentBlockPlacementFilterCondition condition;
		BlockDescriptor block_descriptor;
		block_descriptor.tags = { "dirt", "farmland" };
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

		return Block::Generate(mod_id, id);
	}
} // namespace adk