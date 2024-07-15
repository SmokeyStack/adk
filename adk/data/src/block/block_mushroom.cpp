#include "block/block_mushroom.h"

#include "block/component/box_collision.h"
#include "block/component/box_selection.h"

namespace adk {
	nlohmann::json BlockMushroom::Generate(std::string mod_id, std::string id) {
		auto& box_collision = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:collision_box"; });
		if (box_collision == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockBoxCollision>(false);
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockBoxCollision* component = dynamic_cast<ComponentBlockBoxCollision*>(box_collision->get());
			component->SetCollision(false);
		}

		auto& box_selection = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:selection_box"; });
		if (box_selection == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockBoxSelection>(Vector3(-3, 0, -3), Vector3(6, 6, 6));
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockBoxSelection* component = dynamic_cast<ComponentBlockBoxSelection*>(box_selection->get());
			component->SetSelection(Vector3(-3, 0, -3), Vector3(6, 6, 6));
		}

		return BlockPlant::Generate(mod_id, id);
	}
} // namespace adk