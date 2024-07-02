#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockDisplayName : public Component {
	public:
		ComponentBlockDisplayName(std::string display_name) : display_name_(display_name) {}
		~ComponentBlockDisplayName() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::string display_name_;
	};
} // namespace adk