#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockLoot : public Component {
	public:
		ComponentBlockLoot(std::string loot) : loot_(loot) {}
		~ComponentBlockLoot() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::string loot_;
	};
} // namespace adk