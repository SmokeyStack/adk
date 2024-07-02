#pragma once

#include "component.h"
#include "utility/vector3.h"

namespace adk {
	class ComponentBlockTransformation : public Component {
	public:
		ComponentBlockTransformation() {}
		~ComponentBlockTransformation() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
		ComponentBlockTransformation& SetRotation(Vector3 rotation);
		ComponentBlockTransformation& SetRotationPivot(Vector3 rotation_pivot);
		ComponentBlockTransformation& SetScale(Vector3 scale);
		ComponentBlockTransformation& SetScalePivot(Vector3 scale_pivot);
		ComponentBlockTransformation& SetTranslation(Vector3 translation);
	private:
		Vector3 rotation_{ 0,0,0 };
		Vector3 rotation_pivot_{ 0,0,0 };
		Vector3 scale_{ 1,1,1 };
		Vector3 scale_pivot_{ 0,0,0 };
		Vector3 translation_{ 0,0,0 };
	};
} // namespace adk