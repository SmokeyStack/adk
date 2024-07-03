#include "block/property.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t PlacementDirection::Generate() {
		nlohmann::json::object_t output = { {"minecraft:placement_direction",{{"enabled_states", nlohmann::json::array()}}} };
		auto& enabled_states = output["minecraft:placement_direction"]["enabled_states"];

		for (const auto& state : enabled_states_) {
			switch (state) {
			case EnabledStates::CARDINAL_DIRECTION:
				enabled_states.push_back("minecraft:cardinal_direction");
				break;
			case EnabledStates::FACING_DIRECTION:
				enabled_states.push_back("minecraft:facing_direction");
				break;
			}
		}

		if (y_rotation_offset_ != 0.0) output["minecraft:placement_direction"]["y_rotation_offset"] = y_rotation_offset_;

		return output;
	}
	PlacementDirection& PlacementDirection::AddEnabledState(EnabledStates state) {
		enabled_states_.insert(state);

		return *this;
	}
	void PlacementDirection::SetYRotationOffset(double offset) { y_rotation_offset_ = offset; }

	nlohmann::json::object_t PlacementPosition::Generate() {
		nlohmann::json::object_t output = { {"minecraft:placement_position",{{"enabled_states", nlohmann::json::array()}}} };
		auto& enabled_states = output["minecraft:placement_position"]["enabled_states"];

		for (const auto& state : enabled_states_) {
			switch (state) {
			case EnabledStates::BLOCK_FACE:
				enabled_states.push_back("minecraft:block_face");
				break;
			case EnabledStates::VERTICAL_HALF:
				enabled_states.push_back("minecraft:vertical_half");
				break;
			}
		}

		return output;
	}
	PlacementPosition& PlacementPosition::AddEnabledState(EnabledStates state) {
		enabled_states_.insert(state);

		return *this;
	}

	nlohmann::json Property::Generate() {
		nlohmann::json output;
		auto& traits = output["traits"];
		auto& states = output["states"];

		for (const auto& trait : traits_)
			traits.update(trait->Generate());

		for (const auto& state : states_)
			states.update(state->Generate());

		return output;
	}
	Property& Property::AddTrait(std::unique_ptr<PropertyTrait> trait) {
		traits_.insert(std::move(trait));

		return *this;
	}
	Property& Property::AddState(std::unique_ptr<PropertyState> state) {
		states_.insert(std::move(state));

		return *this;
	}

	nlohmann::json::object_t StateString::Generate() {
		nlohmann::json::object_t output = { {name_, values_} };

		return output;
	}
	StateString& StateString::AddValue(std::string value) {
		values_.insert(value);

		return *this;
	}
	StateString& StateString::AddValue(std::set<std::string> value) {
		for (const auto& val : value)
			values_.insert(val);

		return *this;
	}

	nlohmann::json::object_t StateBoolean::Generate() {
		nlohmann::json::object_t output = { {name_, {default_value_, !default_value_}} };

		return output;
	}

	nlohmann::json::object_t StateInt::Generate() {
		nlohmann::json::object_t output = { {name_, values_} };

		return output;
	}
	StateInt& StateInt::AddValue(int value) {
		values_.insert(value);

		return *this;
	}
	StateInt& StateInt::AddValue(std::set<int> value) {
		for (const auto& val : value)
			values_.insert(val);

		return *this;
	}

	nlohmann::json::object_t StateIntRange::Generate() {
		nlohmann::json::object_t output = { {name_, {{"values",{{"min", min_},{"max", max_}}}}} };

		return output;
	}
} // namespace adk