#pragma once

#include <variant>

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:destructible_by_mining" component
	 * Describes the destructible by mining properties for this block.
	 * If set to true, the block will take the default number of seconds to destroy.
	 * If set to false, this block is indestructible by mining.
	 * If the component is omitted, the block will take the default number of seconds to destroy.
	 */
	class ComponentBlockDestructibleByMining : public Component {
	public:
		/**
		 * @brief "minecraft:destructible_by_mining" component
		 * 
		 * @param value If set to true, the block will take the default number of seconds to destroy.
		 * If set to false, this block is indestructible by mining.
		 */
		ComponentBlockDestructibleByMining(bool value) : seconds_to_destroy_(value) {}

		/**
		 * @brief "minecraft:destructible_by_mining" component
		 * 
		 * @param seconds_to_destroy Sets the number of seconds it takes to destroy the block with base equipment.
		 * Greater numbers result in greater mining times.
		 */
		ComponentBlockDestructibleByMining(double seconds_to_destroy) : seconds_to_destroy_(seconds_to_destroy) {}
		~ComponentBlockDestructibleByMining() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::variant<bool, double> seconds_to_destroy_ = true;
	};
} // namespace adk