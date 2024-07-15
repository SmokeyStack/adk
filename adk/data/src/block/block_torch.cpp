#include "block/block_torch.h"

#include <spdlog/fmt/fmt.h>

#include "block/component/box_collision.h"
#include "block/component/box_selection.h"
#include "block/component/custom.h"
#include "block/component/tick.h"
#include "block/component/transformation.h"

namespace adk {
	nlohmann::json BlockTorch::Generate(std::string mod_id, std::string id) {
		auto property = std::make_unique<Property>();
		auto placement_position = std::make_unique<PlacementPosition>();
		placement_position->AddEnabledState(PlacementPosition::EnabledStates::BLOCK_FACE);
		property->AddTrait(std::move(placement_position));
		Block::AddProperty(std::move(property));

		auto& permutation = std::make_unique<Permutation>("q.block_state('minecraft:block_face') == 'north'");
		ComponentBlockTransformation transformation;
		transformation.SetRotation(Vector3(0, 90, 0));
		permutation->AddComponent(std::make_unique<ComponentBlockTransformation>(transformation));
		Block::AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>("q.block_state('minecraft:block_face') == 'east'");
		transformation.SetRotation(Vector3(0, 0, 0));
		permutation->AddComponent(std::make_unique<ComponentBlockTransformation>(transformation));
		Block::AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>("q.block_state('minecraft:block_face') == 'west'");
		transformation.SetRotation(Vector3(0, 270, 0));
		permutation->AddComponent(std::make_unique<ComponentBlockTransformation>(transformation));
		Block::AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>("q.block_state('minecraft:block_face') == 'south'");
		transformation.SetRotation(Vector3(0, 180, 0));
		permutation->AddComponent(std::make_unique<ComponentBlockTransformation>(transformation));
		Block::AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>(fmt::format(
			"q.block_state('{state}') == 'north' || q.block_state('{state}') == 'east' || q.block_state('{state}') == 'south' || q.block_state('{state}') == 'west'",
			fmt::arg("state", "minecraft:block_face")
		));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxSelection>(Vector3(2, 3, -3), Vector3(6, 10, 6)));
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