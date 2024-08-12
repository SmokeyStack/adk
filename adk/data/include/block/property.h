#pragma once

#include <unordered_set>
#include <vector>

#include "json.hpp"

namespace adk {
	/**
	 * @brief Property Class
	 */
	class Property {
	public:
		Property() {}
		~Property() {}
		virtual nlohmann::json::object_t Generate() = 0;
	};

	// Property Traits

	/**
	 * @brief Block Trait
	 */
	class PropertyTrait : public Property {
	public:
		PropertyTrait() {}
		~PropertyTrait() {}
		virtual nlohmann::json::object_t Generate() = 0;
	};

	/**
	 * @brief Block Trait - Placement Direction
	 */
	class PlacementDirection : public PropertyTrait {
	public:
		enum class EnabledStates {
			CARDINAL_DIRECTION,
			FACING_DIRECTION
		};
		PlacementDirection() {}
		~PlacementDirection() {}
		nlohmann::json::object_t Generate() override;

		/**
		 * @brief Adds the enabled state
		 * 
		 * @param state EnabledStates enum
		 * 
		 * @return PlacementDirection&
		 */
		PlacementDirection& AddEnabledState(EnabledStates state);

		/**
		 * @brief Sets the Y rotation offset
		 * 
		 * @param offset Rotation Offset in Degrees
		 */
		void SetYRotationOffset(double offset);
	private:
		std::unordered_set<EnabledStates> enabled_states_;
		double y_rotation_offset_ = 0.0;
	};

	/**
	 * @brief Block Trait - Placement Position
	 */
	class PlacementPosition : public PropertyTrait {
	public:
		enum class EnabledStates {
			BLOCK_FACE,
			VERTICAL_HALF
		};
		PlacementPosition() {}
		~PlacementPosition() {}
		nlohmann::json::object_t Generate() override;

		/**
		 * @brief Adds the enabled state
		 * @param state 
		 * @return 
		 */
		PlacementPosition& AddEnabledState(EnabledStates state);
	private:
		std::unordered_set<EnabledStates> enabled_states_;
	};

	// Property States

	/**
	 * @brief Block State
	 */
	class PropertyState : public Property {
	public:
		/**
		 * @brief Block State
		 * 
		 * @param name The name of the block state
		 */
		PropertyState(std::string name) : name_(name) {}
		~PropertyState() {}
	protected:
		std::string name_;
	};

	/**
	 * @brief Block State - String
	 */
	class StateString : public PropertyState {
	public:
		/**
		 * @brief Block State - String
		 * 
		 * @param name The name of the block state
		 */
		StateString(std::string name) : PropertyState(name) {}
		~StateString() {}
		nlohmann::json::object_t Generate() override;

		/**
		 * @brief Adds a value to the block state
		 * 
		 * @param value The value to add
		 * 
		 * @return StateString&
		 */
		StateString& AddValue(std::string value);

		/**
		 * @brief Adds a value to the block state
		 * 
		 * @param value The value to add
		 * 
		 * @return StateString&
		 */
		StateString& AddValue(std::unordered_set<std::string> value);
	private:
		std::vector<std::string> values_;
		std::unordered_set<std::string> internal_values_;
	};

	/**
	 * @brief Block State - Boolean
	 */
	class StateBoolean : public PropertyState {
	public:
		/**
		 * @brief Block State - Boolean
		 * 
		 * @param name The name of the block state
		 * 
		 * @param default_value The default value of the block state
		 */
		StateBoolean(std::string name, bool default_value) : default_value_(default_value), PropertyState(name) {}
		~StateBoolean() {}
		nlohmann::json::object_t Generate() override;
	private:
		bool default_value_;
	};

	/**
	 * @brief Block State - Integer
	 */
	class StateInt : public PropertyState {
	public:
		/**
		 * @brief Block State - Integer
		 * 
		 * @param name The name of the block state
		 */
		StateInt(std::string name) : PropertyState(name) {}
		~StateInt() {}
		nlohmann::json::object_t Generate() override;

		/**
		 * @brief Adds a value to the block state
		 * 
		 * @param value The value to add
		 * 
		 * @return StateInt&
		 */
		StateInt& AddValue(int value);

		/**
		 * @brief Adds a value to the block state
		 * 
		 * @param value The value to add
		 * 
		 * @return StateInt&
		 */
		StateInt& AddValue(std::unordered_set<int> value);
	private:
		std::vector<int> values_;
		std::unordered_set<int> internal_values_;
	};

	/**
	 * @brief Block State - Integer Range
	 */
	class StateIntRange : public PropertyState {
	public:
		/**
		 * @brief Block State - Integer Range
		 * 
		 * @param name The name of the block state
		 * 
		 * @param min The minimum value of the block state
		 * 
		 * @param max The maximum value of the block state
		 */
		StateIntRange(std::string name, int min, int max) : min_(min), max_(max), PropertyState(name) {}
		~StateIntRange() {}
		nlohmann::json::object_t Generate() override;
	private:
		int min_;
		int max_;
	};
} // namespace adk