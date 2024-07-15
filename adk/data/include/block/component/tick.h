#pragma once

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:tick" component
	 * Triggers the specified custom component, either once, or at a regular interval equal to a number of ticks randomly chosen from the interval_range provided.
	 */
	class ComponentBlockTick : public Component {
	public:
		ComponentBlockTick() {}

		/**
		 * @brief "minecraft:tick" component
		 * 
		 * @param min Minimum ticks that the game will choose to tick the block.
		 * 
		 * @param max Maximum ticks that the game will choose to tick the block.
		 */
		ComponentBlockTick(int min, int max) : interval_range_min_(min), interval_range_max_(max) {}

		/**
		 * @brief "minecraft:tick" component
		 * 
		 * @param min Minimum ticks that the game will choose to tick the block.
		 * 
		 * @param max Maximum ticks that the game will choose to tick the block.
		 * 
		 * @param loop Determines whether or not the block should continue to tick once it has been ticked or not.
		 */
		ComponentBlockTick(int min, int max, bool loop) : interval_range_min_(min), interval_range_max_(max), looping_(loop) {}
		~ComponentBlockTick() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;

		/**
		 * @brief Sets the interval range
		 * 
		 * @param min Minimum ticks that the game will choose to tick the block.
		 * 
		 * @param max Maximum ticks that the game will choose to tick the block.
		 * 
		 * @return ComponentBlockTick&
		 */
		ComponentBlockTick& SetIntervalRange(int min, int max);

		/**
		 * @brief Sets whether the block should continue to tick once it has been ticked or not.
		 * 
		 * @param loop Boolean value determining whether the block should continue to tick once it has been ticked or not.
		 * 
		 * @return ComponentBlockTick&
		 */
		ComponentBlockTick& SetLooping(bool loop);
	private:
		int interval_range_min_ = 0;
		int interval_range_max_ = 0;
		bool looping_ = true;
	};
} // namespace adk