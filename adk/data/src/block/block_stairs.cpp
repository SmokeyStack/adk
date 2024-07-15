#include "block/block_stairs.h"

#include "block/component/custom.h"

namespace adk {
	nlohmann::json BlockStairs::Generate(std::string mod_id, std::string id) {
		auto property = std::make_unique<Property>();
		auto placement_position = std::make_unique<PlacementPosition>();
		auto placement_direction = std::make_unique<PlacementDirection>();
		placement_position->AddEnabledState(PlacementPosition::EnabledStates::VERTICAL_HALF);
		placement_direction->AddEnabledState(PlacementDirection::EnabledStates::CARDINAL_DIRECTION);
		property->AddTrait(std::move(placement_position));
		auto state_string = std::make_unique<StateString>(mod_id + ":shape");
		auto state = std::make_unique<StateBoolean>(mod_id + ":south", false);
		state_string->AddValue({ "straight", "inner_left", "inner_right", "outer_left", "outer_right" });
		property->AddState(std::move(state));
		property->AddState(std::move(state_string));
		Block::AddProperty(std::move(property));

		auto& custom_component = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:custom_components"; });
		if (custom_component == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockCustom>();
			component->Add("adk-lib:before_on_player_place_stairs");
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockCustom* component = dynamic_cast<ComponentBlockCustom*>(custom_component->get());
			component->Add("adk-lib:before_on_player_place_stairs");
		}

		return Block::Generate(mod_id, id);
	}
} // namespace adk