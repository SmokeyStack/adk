#pragma once

#include <variant>

#include "component.h"
#include "utility/vector3.h"

namespace adk {
	/**
	 * @brief "minecraft:selection_box" component
	 * Defines the area of the block that is selected by the player's cursor.
	 * If set to true, default values are used.
	 * If set to false, this block is not selectable by the player's cursor.
	 * If this component is omitted, default values are used.
	 */
	class ComponentBlockBoxSelection : public Component {
	public:
		/**
		 * @brief "minecraft:selection_box" component
		 *
		 * @param selection If set to true, default values are used.
		 * If set to false, this block is not selectable by the player's cursor.
		 */
		ComponentBlockBoxSelection(bool selection) : selection_(selection) {}
		
		/**
		 * @brief "minecraft:selection_box" component
		 *
		 * @param origin Minimal position of the bounds of the selection box.
		 * origin is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the selection box.
		 * size specified as [x, y, z].
		 * origin + size must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 */
		ComponentBlockBoxSelection(Vector3 origin, Vector3 size) : selection_(std::make_pair(origin, size)) {}
		~ComponentBlockBoxSelection() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;

		/**
		 * @brief Ensures that the origin and size are valid
		 *
		 * @param origin Minimal position of the bounds of the selection box.
		 * origin is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the selection box.
		 * size specified as [x, y, z].
		 */
		static void EnsureValidity(Vector3 origin, Vector3 size);

		/**
		 * @brief Combines the origin and size into a tuple
		 *
		 * @param origin Minimal position of the bounds of the selection box.
		 * origin is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the selection box.
		 * size specified as [x, y, z].
		 *
		 * @return std::tuple<double, double, double>
		 */
		static std::tuple<double, double, double> CombineOriginAndSize(Vector3 origin, Vector3 size);

		/**
		 * @brief Sets the selection box
		 *
		 * @param collision If set to true, default values are used.
		 * If set to false, this block is not selectable by the player's cursor.
		 *
		 * @return ComponentBlockBoxSelection&
		 */
		ComponentBlockBoxSelection& SetSelection(bool selection);

		/**
		 * @brief Sets the selection box
		 *
		 * @param origin Minimal position of the bounds of the selection box.
		 * origin is specified as [x, y, z] and must be in the range (-8, 0, -8) to (8, 16, 8), inclusive.
		 *
		 * @param size Size of each side of the selection box.
		 * size specified as [x, y, z].
		 *
		 * @return ComponentBlockBoxSelection&
		 */
		ComponentBlockBoxSelection& SetSelection(Vector3 origin, Vector3 size);
	private:
		std::variant<bool, std::pair<Vector3, Vector3>> selection_ = true;
	};
} // namespace adk