#include "block/block_slab.h"

#include "block/component/box_collision.h"
#include "block/component/box_selection.h"
#include "block/component/custom.h"
#include "block/component/loot.h"

namespace adk {
	nlohmann::json BlockSlab::Generate(std::string mod_id, std::string id) {
		auto property = std::make_unique<Property>();
		auto placement_position = std::make_unique<PlacementPosition>();
		placement_position->AddEnabledState(PlacementPosition::EnabledStates::VERTICAL_HALF);
		property->AddTrait(std::move(placement_position));
		auto state = std::make_unique<StateBoolean>(mod_id + ":is_double", false);
		property->AddState(std::move(state));
		Block::AddProperty(std::move(property));

		auto& permutation = std::make_unique<Permutation>("q.block_state('minecraft:vertical_half') == 'bottom' && !q.block_state('" + mod_id + ":is_double')");
		ComponentBlockCustom custom_component;
		custom_component.Add("adk-lib:before_on_player_place_double_slab");
		permutation->AddComponent(std::make_unique<ComponentBlockBoxCollision>(Vector3(-8, 0, -8), Vector3(16, 8, 16)));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxSelection>(Vector3(-8, 0, -8), Vector3(16, 8, 16)));
		permutation->AddComponent(std::make_unique<ComponentBlockCustom>(custom_component));
		Block::AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>("q.block_state('minecraft:vertical_half') == 'top' && !q.block_state('" + mod_id + ":is_double')");
		permutation->AddComponent(std::make_unique<ComponentBlockBoxCollision>(Vector3(-8, 8, -8), Vector3(16, 8, 16)));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxSelection>(Vector3(-8, 8, -8), Vector3(16, 8, 16)));
		permutation->AddComponent(std::make_unique<ComponentBlockCustom>(custom_component));
		Block::AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>("q.block_state('" + mod_id + ":is_double')");
		permutation->AddComponent(std::make_unique<ComponentBlockLoot>(is_double_loot_));
		Block::AddPermutation(std::move(permutation));

		return Block::Generate(mod_id, id);
	}
} // namespace adk