#pragma once

#include <vector>
#include <memory>

#include "block/component/base.h"

namespace adk {
	class Property {
	public:
		Property() {}
		~Property() {}
		std::vector<Component*> GetComponents();
		Property* LightDampening(int value);
		Property* LightEmission(int value);
	private:
		std::vector<Component*> components_;
	};
} // namespace adk