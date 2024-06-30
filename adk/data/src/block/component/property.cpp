#include "block/component/property.h"

#include "block/component/light_dampening.h"
#include "block/component/light_emission.h"
#include "block/component/box_collision.h"

namespace adk {
	std::vector<Component*> Property::GetComponents() { return components_; }

	Property* Property::LightDampening(int value) {
		ComponentLightDampening* component = new ComponentLightDampening(value);
		components_.push_back(component);

		return this;
	}

	Property* Property::LightEmission(int value) {
		 ComponentLightEmission* component = new ComponentLightEmission(value);
		 components_.push_back(component);

		return this;
	}

	Property* Property::BoxCollision(bool value) {
		 ComponentBoxCollision* component = new ComponentBoxCollision(value);
		 components_.push_back(component);

		return this;
	}

	Property* Property::BoxCollision(Vector3 origin, Vector3 size) {
		 ComponentBoxCollision* component = new ComponentBoxCollision(origin, size);
		 components_.push_back(component);

		return this;
	}
} // namespace adk