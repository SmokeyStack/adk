#pragma once

#include <variant>

#include "component.h"
#include "utility/vector3.h"

namespace adk {
	/**
	 * @brief "minecraft:map_color" component
	 * Sets the color of the block when rendered to a map.
	 * The color is represented as a hex value in the format #RRGGBB.
	 * May also be expressed as an array of [R, G, B] from 0 to 255.
	 * If this component is omitted, the block will not show up on the map.
	 */
	class ComponentBlockMapColor : public Component {
	public:
		/**
		 * @brief "minecraft:map_color" component
		 * @param map_color Hex value
		 */
		ComponentBlockMapColor(std::string map_color) : map_color_(map_color) {}

		/**
		 * @brief "minecraft:map_color" component
		 * @param map_color RGB value
		 */
		ComponentBlockMapColor(Vector3 map_color) : map_color_(map_color) {}
		~ComponentBlockMapColor() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::variant<std::string, Vector3> map_color_;
	};
} // namespace adk