#pragma once

#include <variant>

#include "component.h"
#include "utility/vector3.h"

namespace adk {
	/**
	 * @brief "minecraft:collision_box" component
	 * Defines the area of the block that collides with entities.
	 * If set to true, default values are used.
	 * If set to false, the block's collision with entities is disabled.
	 * If this component is omitted, default values are used.
	 */
	class ComponentBlockBoxCollision : public Component {
	public:
		/**
		 * @brief "minecraft:collision_box" component
		 *
		 * @param collision If set to true, default values are used.
		 * If set to false, the block's collision with entities is disabled.
		 */
		ComponentBlockBoxCollision(bool collision) : collision_(collision) {}

		/**
		 * @brief "minecraft:collision_box" component
		 *
		 * @param origin Minimal position of the bounds of the collision box.
		 * origin is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the collision box.
		 * size specified as [x, y, z].
		 * origin + size must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 */
		ComponentBlockBoxCollision(Vector3 origin, Vector3 size) : collision_(std::make_pair(origin, size)) {}
		~ComponentBlockBoxCollision() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;

		/**
		 * @brief Ensures that the origin and size are valid
		 *
		 * @param origin Minimal position of the bounds of the collision box.
		 * origin is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the collision box.
		 * size specified as [x, y, z].
		 */
		static void EnsureValidity(Vector3 origin, Vector3 size);

		/**
		 * @brief Combines the origin and size into a tuple
		 *
		 * @param origin Minimal position of the bounds of the collision box.
		 * origin is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the collision box.
		 * size specified as [x, y, z].
		 *
		 * @return std::tuple<double, double, double>
		 */
		static std::tuple<double, double, double> CombineOriginAndSize(Vector3 origin, Vector3 size);

		/**
		 * @brief Sets the collision box
		 *
		 * @param collision If set to true, default values are used.
		 * If set to false, the block's collision with entities is disabled.
		 *
		 * @return ComponentBlockBoxCollision&
		 */
		ComponentBlockBoxCollision& SetCollision(bool collision);

		/**
		 * @brief Sets the collision box
		 *
		 * @param origin Minimal position of the bounds of the collision box.
		 * origin is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the collision box.
		 * size specified as [x, y, z].
		 *
		 * @return ComponentBlockBoxCollision&
		 */
		ComponentBlockBoxCollision& SetCollision(Vector3 origin, Vector3 size);
	private:
		std::variant<bool, std::pair<Vector3, Vector3>> collision_ = true;
	};
} // namespace adk