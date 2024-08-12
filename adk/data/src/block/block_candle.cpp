#include "block/block_candle.h"

#include <spdlog/fmt/fmt.h>

#include "block/component/box_collision.h"
#include "block/component/box_selection.h"
#include "block/component/custom.h"
#include "block/component/light_emission.h"

namespace adk {
	nlohmann::json BlockCandle::Generate(std::string mod_id, std::string id) {
		auto state_candles = std::make_unique<StateIntRange>(mod_id + ":candles", 1, 4);
		AddProperty(std::move(state_candles));

		auto& permutation = std::make_unique<Permutation>(fmt::format("q.block_state('{mod_id}:candles') == 1", fmt::arg("mod_id", mod_id)));
		ComponentBlockBoxCollision collision(Vector3(-1, 0, -1), Vector3(2, 6, 2));
		ComponentBlockBoxSelection selection(Vector3(-1, 0, -1), Vector3(2, 6, 2));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxCollision>(collision));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxSelection>(selection));
		AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>(fmt::format("q.block_state('{mod_id}:candles') == 2", fmt::arg("mod_id", mod_id)));
		collision.SetCollision(Vector3(-3, 0, -1), Vector3(6, 6, 3));
		selection.SetSelection(Vector3(-3, 0, -1), Vector3(6, 6, 3));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxCollision>(collision));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxSelection>(selection));
		AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>(fmt::format("q.block_state('{mod_id}:candles') == 3", fmt::arg("mod_id", mod_id)));
		collision.SetCollision(Vector3(-2, 0, -2), Vector3(5, 6, 5));
		selection.SetSelection(Vector3(-2, 0, -2), Vector3(5, 6, 5));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxCollision>(collision));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxSelection>(selection));
		AddPermutation(std::move(permutation));
		permutation = std::make_unique<Permutation>(fmt::format("q.block_state('{mod_id}:candles') == 4", fmt::arg("mod_id", mod_id)));
		collision.SetCollision(Vector3(-3, 0, -3), Vector3(6, 6, 5));
		selection.SetSelection(Vector3(-3, 0, -3), Vector3(6, 6, 5));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxCollision>(collision));
		permutation->AddComponent(std::make_unique<ComponentBlockBoxSelection>(selection));
		AddPermutation(std::move(permutation));

		for (int a = 1; a < 5; a++) {
			permutation = std::make_unique<Permutation>(fmt::format("q.block_state('{mod_id}:lit') && q.block_state('{mod_id}:candles') == {a}", fmt::arg("mod_id", mod_id), fmt::arg("a", a)));
			ComponentBlockLightEmission light_emission(3 * a);
			permutation->AddComponent(std::make_unique<ComponentBlockLightEmission>(light_emission));
			AddPermutation(std::move(permutation));
		}

		const std::string condition = fmt::format("q.block_state('{mod_id}:lit')", fmt::arg("mod_id", mod_id));
		auto& permutation_lit = std::find_if(std::begin(permutations_), std::end(permutations_), [condition](const auto& permutation) { return permutation->GetCondition() == condition; });
		if (permutation_lit != std::end(permutations_)) {
			auto& components = permutation_lit->get()->GetComponents();

			auto& custom_component = std::find_if(std::begin(components), std::end(components), [](const auto& component) { return component->GetType() == "minecraft:custom_components"; });
			if (custom_component == std::end(components_)) {
				auto component = std::make_unique<ComponentBlockCustom>();
				component->Add("adk-lib:on_player_interact_candle");
				components_.insert(std::move(component));
			}
			else {
				ComponentBlockCustom* component = dynamic_cast<ComponentBlockCustom*>(custom_component->get());
				component->Add("adk-lib:on_player_interact_candle");
			}
		}

		return BlockCandleAbstract::Generate(mod_id, id);
	}
} // namespace adk