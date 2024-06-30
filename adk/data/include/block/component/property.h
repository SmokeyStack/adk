#pragma once

#include <memory>
#include <vector>

#include "block/component/base.h"
#include "utility/vector3.h"

namespace adk {
	class Property {
	public:
		Property() {}
		~Property() {}
		std::vector<Component*> GetComponents();
		Property* LightDampening(int value);
		Property* LightEmission(int value);
		Property* BoxCollision(bool value);
		Property* BoxCollision(Vector3 origin, Vector3 size);
	private:
		std::vector<Component*> components_;
	};
} // namespace adk