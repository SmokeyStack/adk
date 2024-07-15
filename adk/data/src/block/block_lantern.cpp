#include "block/block_lantern.h"

#include <spdlog/fmt/fmt.h>

#include "block/component/box_collision.h"
#include "block/component/box_selection.h"
#include "block/component/custom.h"
#include "block/component/tick.h"
#include "block/component/transformation.h"

namespace adk {
	nlohmann::json BlockLantern::Generate(std::string mod_id, std::string id) {
		auto property = std::make_unique<Property>();
		auto state_hanging = std::make_unique<StateBoolean>(mod_id + ":hanging", false);
		property->AddState(std::move(state_hanging));
		Block::AddProperty(std::move(property));

		auto& permutation = std::make_unique<Permutation>(fmt::format("q.block_state('{mod_id}:hanging')", fmt::arg("mod_id", mod_id)));
		ComponentBlockTransformation transformation;
		transformation.SetTranslation(Vector3(0, 0.5, 0));
		permutation->AddComponent(std::make_unique<ComponentBlockTransformation>(transformation));
		Block::AddPermutation(std::move(permutation));

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
		if (box_collision == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockBoxSelection>(Vector3(-2, 0, -2), Vector3(4, 10, 4));
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockBoxSelection* component = dynamic_cast<ComponentBlockBoxSelection*>(box_selection->get());
			component->SetSelection(Vector3(-2, 0, -2), Vector3(4, 10, 4));
		}

		auto& tick = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:tick"; });
		if (tick == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockTick>(20, 20, true);
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockTick* component = dynamic_cast<ComponentBlockTick*>(tick->get());
			component->SetIntervalRange(20, 20);
		}

		auto& custom_component = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:custom_components"; });
		if (custom_component == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockCustom>();
			component->Add("adk-lib:on_tick_torch_particles");
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockCustom* component = dynamic_cast<ComponentBlockCustom*>(custom_component->get());
			component->Add("adk-lib:on_tick_torch_particles");
		}

		return Block::Generate(mod_id, id);
	}
} // namespace adk