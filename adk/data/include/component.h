#pragma once

#include <string>

#include "json.hpp"

namespace adk {
	class Component {
	public:
		Component() {}
		virtual ~Component() {}
		virtual nlohmann::json::object_t Generate() = 0;
		virtual std::string GetType() = 0;
	};
} // namespace adk