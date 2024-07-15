#pragma once

#include "component.h"
#include "utility/vector3.h"

namespace adk {
	/**
	 * @brief "minecraft:transformation" component
	 */
	class ComponentBlockTransformation : public Component {
	public:
		ComponentBlockTransformation() {}
		~ComponentBlockTransformation() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;

		/**
		 * @brief Sets the "rotation" property
		 * 
		 * @param rotation How many degrees to rotate the geometry. [x ,y, z].
		 * Must be in increments of 90. Can be negative.
		 * If not in increment of 90, the game will round to the nearest 90 increment.
		 * 
		 * @return ComponentBlockTransformation&
		 */
		ComponentBlockTransformation& SetRotation(Vector3 rotation);

		/**
		 * @brief Sets the "rotation_pivot" property
		 *
		 * @param rotation_pivot The pivot point(in block units) to rotate the block on.
		 *
		 * @return ComponentBlockTransformation&
		 */
		ComponentBlockTransformation& SetRotationPivot(Vector3 rotation_pivot);

		/**
		 * @brief Sets the "scale" property
		 *
		 * @param scale How many points(in block units) to scale the geometry. [x ,y, z].
		 *
		 * @return ComponentBlockTransformation&
		 */
		ComponentBlockTransformation& SetScale(Vector3 scale);

		/**
		 * @brief Sets the "scale_pivot" property
		 *
		 * @param scale_pivot The pivot point(in block units) to scale the block on.
		 *
		 * @return ComponentBlockTransformation&
		 */
		ComponentBlockTransformation& SetScalePivot(Vector3 scale_pivot);

		/**
		 * @brief Sets the "translation" property
		 *
		 * @param translation How many points(in block units) to translate the geometry. [x ,y, z].
		 *
		 * @return ComponentBlockTransformation&
		 */
		ComponentBlockTransformation& SetTranslation(Vector3 translation);
	private:
		Vector3 rotation_{ 0,0,0 };
		Vector3 rotation_pivot_{ 0,0,0 };
		Vector3 scale_{ 1,1,1 };
		Vector3 scale_pivot_{ 0,0,0 };
		Vector3 translation_{ 0,0,0 };
	};
} // namespace adk