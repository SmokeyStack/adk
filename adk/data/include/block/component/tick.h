#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockTick : public Component {
	public:
		ComponentBlockTick() {}
		ComponentBlockTick(int min, int max) : interval_range_min_(min), interval_range_max_(max) {}
		ComponentBlockTick(int min, int max, bool loop) : interval_range_min_(min), interval_range_max_(max), looping_(loop) {}
		~ComponentBlockTick() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		int interval_range_min_ = 0;
		int interval_range_max_ = 0;
		bool looping_ = true;
	};
} // namespace adk