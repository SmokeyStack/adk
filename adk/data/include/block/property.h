#pragma once

#include <set>

#include "json.hpp"

namespace adk {
	class PropertyTrait {
	public:
		PropertyTrait() {}
		~PropertyTrait() {}
		virtual nlohmann::json::object_t Generate() = 0;
	};

	class PlacementDirection : public PropertyTrait {
	public:
		enum class EnabledStates {
			CARDINAL_DIRECTION,
			FACING_DIRECTION
		};
		PlacementDirection() {}
		~PlacementDirection() {}
		nlohmann::json::object_t Generate() override;
		PlacementDirection& AddEnabledState(EnabledStates state);
		void SetYRotationOffset(double offset);
	private:
		std::set<EnabledStates> enabled_states_;
		double y_rotation_offset_ = 0.0;
	};

	class PlacementPosition : public PropertyTrait {
	public:
		enum class EnabledStates {
			BLOCK_FACE,
			VERTICAL_HALF
		};
		PlacementPosition() {}
		~PlacementPosition() {}
		nlohmann::json::object_t Generate() override;
		PlacementPosition& AddEnabledState(EnabledStates state);
	private:
		std::set<EnabledStates> enabled_states_;
	};

	class PropertyState {
	public:
		PropertyState(std::string name) : name_(name) {}
		~PropertyState() {}
		virtual nlohmann::json::object_t Generate() = 0;
	protected:
		std::string name_;
	};

	class StateString : public PropertyState {
	public:
		StateString(std::string name) : PropertyState(name) {}
		~StateString() {}
		nlohmann::json::object_t Generate() override;
		StateString& AddValue(std::string value);
		StateString& AddValue(std::set<std::string> value);
	private:
		std::set<std::string> values_;
	};

	class StateBoolean : public PropertyState {
	public:
		StateBoolean(std::string name, bool default_value) : default_value_(default_value), PropertyState(name) {}
		~StateBoolean() {}
		nlohmann::json::object_t Generate() override;
	private:
		bool default_value_;
	};

	class StateInt : public PropertyState {
	public:
		StateInt(std::string name) : PropertyState(name) {}
		~StateInt() {}
		nlohmann::json::object_t Generate() override;
		StateInt& AddValue(int value);
		StateInt& AddValue(std::set<int> value);
	private:
		std::set<int> values_;
	};

	class StateIntRange : public PropertyState {
	public:
		StateIntRange(std::string name, int min, int max) : min_(min), max_(max), PropertyState(name) {}
		~StateIntRange() {}
		nlohmann::json::object_t Generate() override;
	private:
		int min_;
		int max_;
	};

	class Property {
	public:
		Property() {}
		~Property() {}
		nlohmann::json Generate();
		Property& AddTrait(std::unique_ptr<PropertyTrait> trait);
		Property& AddState(std::unique_ptr<PropertyState> state);
	private:
		std::set<std::unique_ptr<PropertyTrait>> traits_;
		std::set<std::unique_ptr<PropertyState>> states_;
	};
} // namespace adk