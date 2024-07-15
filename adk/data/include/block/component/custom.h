#pragma once

#include <set>

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:custom_components" component
	 * Sets an ordered list of custom component names bound in script to be executed on a block event
	 */
	class ComponentBlockCustom : public Component {
	public:
		ComponentBlockCustom() {}
		~ComponentBlockCustom() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;

		/**
		 * @brief Add a custom component
		 *
		 * @param component Name of the custom component
		 *
		 * @return ComponentBlockCustom&
		 */
		ComponentBlockCustom& Add(std::string component);

		/**
		 * @brief Add a set of custom components
		 *
		 * @param components Set of custom components
		 *
		 * @return ComponentBlockCustom&
		 */
		ComponentBlockCustom& Add(std::set<std::string> components);

		/**
		 * @brief Remove a custom component
		 *
		 * @param component Name of the custom component
		 *
		 * @return ComponentBlockCustom&
		 */
		ComponentBlockCustom& Remove(std::string component);
	private:
		std::set<std::string> custom_components_;
	};
} // namespace adk