#include "block/component/custom.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockCustom::Generate() {
		nlohmann::json::object_t output = { {"minecraft:custom_components", nlohmann::json::array()} };
		auto& custom_components = output["minecraft:custom_components"];

		for (const auto& component : custom_components_)
			custom_components.push_back(component);

		return output;
	}
	std::string ComponentBlockCustom::GetType() { return "minecraft:custom_components"; }
	ComponentBlockCustom& ComponentBlockCustom::Add(std::string component) {
		custom_components_.insert(component);

		return *this;
	}
	ComponentBlockCustom& ComponentBlockCustom::Add(std::set<std::string> components) {
		for (const auto& component : components)
			custom_components_.insert(component);

		return *this;
	}
	ComponentBlockCustom& ComponentBlockCustom::Remove(std::string component) {
		custom_components_.erase(component);

		return *this;
	}
} // namespace adk