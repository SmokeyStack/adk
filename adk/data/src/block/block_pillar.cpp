#include "block/block_pillar.h"

#include "block/component/placement_filter.h"
#include "block/component/transformation.h"
#include "block/property.h"

namespace adk {
	nlohmann::json BlockPillar::Generate(std::string mod_id, std::string id) {
		auto property = std::make_unique<Property>();
		auto placement_position = std::make_unique<PlacementPosition>();
		placement_position->AddEnabledState(PlacementPosition::EnabledStates::BLOCK_FACE);
		property->AddTrait(std::move(placement_position));
		Block::AddProperty(std::move(property));

		auto& permutation = std::make_unique<Permutation>("q.block_state('minecraft:block_face') == 'north' || q.block_state('minecraft:block_face') == 'south'");
		ComponentBlockTransformation transformation;
		transformation.SetRotation(Vector3(90, 0, 0));
		permutation->AddComponent(std::make_unique<ComponentBlockTransformation>(transformation));
		Block::AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>("q.block_state('minecraft:block_face') == 'east' || q.block_state('minecraft:block_face') == 'west'");
		transformation.SetRotation(Vector3(0, 0, 270));
		permutation->AddComponent(std::make_unique<ComponentBlockTransformation>(transformation));
		Block::AddPermutation(std::move(permutation));

		return Block::Generate(mod_id, id);
	}
} // namespace adk