#pragma once

#include <string>

#include "json.hpp"

namespace adk {
	/**
	 * @brief Component class
	 */
	class Component {
	public:
		/**
		 * @brief Construct a new Component object
		 */
		Component() {}
		virtual ~Component() {}
		/**
		 * @brief Generates the component
		 *
		 * @return nlohmann::json::object_t
		 */
		virtual nlohmann::json::object_t Generate() = 0;
		/**
		 * @brief Returns the component type
		 *
		 * @return std::string
		 */
		virtual std::string GetType() = 0;
	};
} // namespace adk