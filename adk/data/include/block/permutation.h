#pragma once

#include <set>
#include <string>

#include "component.h"
#include "json.hpp"

namespace adk {
	class Permutation {
	public:
		Permutation(std::string condition) : condition_(condition) {}
		~Permutation() {}
		nlohmann::json::object_t Generate();
		std::string GetCondition();
		Permutation& AddComponent(std::unique_ptr<Component> component);
	private:
		std::string condition_;
		std::set<std::unique_ptr<Component>> components_;
	};
} // namespace adk