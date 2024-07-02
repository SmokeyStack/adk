#include "block/component/transformation.h"

#include "utility/logger.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockTransformation::Generate() {
		nlohmann::json::object_t output = { {"minecraft:transformation", nlohmann::json::object()} };

		if (rotation_ != Vector3(0, 0, 0))
			output["minecraft:transformation"]["rotation"] = rotation_.Get();
		if(rotation_pivot_ != Vector3(0, 0, 0))
			output["minecraft:transformation"]["rotation_pivot"] = rotation_pivot_.Get();
		if (scale_ != Vector3(1, 1, 1))
			output["minecraft:transformation"]["scale"] = scale_.Get();
		if (scale_pivot_ != Vector3(0, 0, 0))
			output["minecraft:transformation"]["scale_pivot"] = scale_pivot_.Get();
		if (translation_ != Vector3(0, 0, 0))
			output["minecraft:transformation"]["translation"] = translation_.Get();

		return output;
	}
	std::string ComponentBlockTransformation::GetType() { return "minecraft:transformation"; }
	ComponentBlockTransformation& ComponentBlockTransformation::SetRotation(Vector3 rotation) {
		rotation_ = rotation;

		return *this;
	}
	ComponentBlockTransformation& ComponentBlockTransformation::SetRotationPivot(Vector3 rotation_pivot) {
		rotation_pivot_ = rotation_pivot;

		return *this;
	}
	ComponentBlockTransformation& ComponentBlockTransformation::SetScale(Vector3 scale) {
		scale_ = scale;

		return *this;
	}
	ComponentBlockTransformation& ComponentBlockTransformation::SetScalePivot(Vector3 scale_pivot) {
		scale_pivot_ = scale_pivot;

		return *this;
	}
	ComponentBlockTransformation& ComponentBlockTransformation::SetTranslation(Vector3 translation) {
		translation_ = translation;

		return *this;
	}
} // namespace adk