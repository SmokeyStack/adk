#pragma once

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:loot" component
	 * The path to the loot table, relative to the behavior pack.
	 */
	class ComponentBlockLoot : public Component {
	public:
		/**
		 * @brief "minecraft:loot" component
		 * 
		 * @param loot The path to the loot table, relative to the behavior pack.
		 */
		ComponentBlockLoot(std::string loot) : loot_(loot) {}
		~ComponentBlockLoot() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::string loot_;
	};
} // namespace adk