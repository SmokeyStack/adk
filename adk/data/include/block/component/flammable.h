#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockFlammable : public Component {
	public:
		ComponentBlockFlammable() {}
		~ComponentBlockFlammable() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
		ComponentBlockFlammable& SetCatchChanceModifier(int modifier);
		ComponentBlockFlammable& SetDestroyChanceModifier(int modifier);
	private:
		int catch_chance_modifier_ = 5;
		int destroy_chance_modifier_ = 20;
	};
} // namespace adk