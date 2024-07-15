#include "block/permutation.h"

#include "utility/logger.h"

namespace adk {
	std::string Permutation::GetCondition() { return condition_; }
	nlohmann::json::object_t Permutation::Generate() {
		nlohmann::json::object_t output;
		output["condition"] = condition_;
		auto& components = output["components"];

		for (const auto& component : components_)
			components.update(component->Generate());

		return output;
	}
	Permutation& Permutation::AddComponent(std::unique_ptr<Component> component) {
		components_.insert(std::move(component));

		return *this;
	}
} // namespace adk