#include "block/component/property.h"

#include "block/component/light_dampening.h"
#include "block/component/light_emission.h"

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
} // namespace adk