#include "block/block_abstract_candle.h"

#include <spdlog/fmt/fmt.h>

#include "block/component/custom.h"
#include "block/component/tick.h"

namespace adk {
	nlohmann::json BlockCandleAbstract::Generate(std::string mod_id, std::string id) {
		auto property = std::make_unique<Property>();
		auto state_lit = std::make_unique<StateBoolean>(mod_id + ":lit", false);
		property->AddState(std::move(state_lit));
		Block::AddProperty(std::move(property));

		auto& permutation = std::make_unique<Permutation>(fmt::format("q.block_state('{mod_id}:lit')", fmt::arg("mod_id", mod_id)));
		ComponentBlockTick tick;
		tick.SetIntervalRange(20, 100);
		permutation->AddComponent(std::make_unique<ComponentBlockTick>(tick));
		Block::AddPermutation(std::move(permutation));

		auto& custom_component = std::find_if(std::begin(components_), std::end(components_), [](const auto& component) { return component->GetType() == "minecraft:custom_components"; });
		if (custom_component == std::end(components_)) {
			auto component = std::make_unique<ComponentBlockCustom>();
			component->Add("adk-lib:on_tick_candle_particles");
			components_.insert(std::move(component));
		}
		else {
			ComponentBlockCustom* component = dynamic_cast<ComponentBlockCustom*>(custom_component->get());
			component->Add("adk-lib:on_tick_candle_particles");
		}

		return Block::Generate(mod_id, id);
	}
} // namespace adk