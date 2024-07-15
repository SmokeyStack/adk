#pragma once

#include <variant>

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:destructible_by_explosion" component
	 * Describes the destructible by mining properties for this block.
	 * If set to true, the block will take the default number of seconds to destroy.
	 * If set to false, this block is indestructible by mining.
	 * If the component is omitted, the block will take the default number of seconds to destroy.
	 */
	class ComponentBlockDestructibleByExplosion : public Component {
	public:
		/**
		 * @brief "minecraft:destructible_by_explosion" component
		 * 
		 * @param value If set to true, the block will take the default number of seconds to destroy.
		 * If set to false, this block is indestructible by mining.
		 */
		ComponentBlockDestructibleByExplosion(bool value) : explosion_resistance_(value) {}

		/**
		 * @brief "minecraft:destructible_by_explosion" component
		 * 
		 * @param explosion_resistance Describes how resistant the block is to explosion.
		 * Greater values mean the block is less likely to break when near an explosion (or has higher resistance to explosions).
		 * The scale will be different for different explosion power levels.
		 * A negative value or 0 means it will easily explode; larger numbers increase level of resistance.
		 */
		ComponentBlockDestructibleByExplosion(double explosion_resistance) : explosion_resistance_(explosion_resistance) {}
		~ComponentBlockDestructibleByExplosion() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::variant<bool, double> explosion_resistance_ = true;
	};
} // namespace adk