#pragma once

#include <set>

#include "component.h"

namespace adk {
	/**
	 * @brief Block Tag
	 */
	class ComponentBlockTag : public Component {
	public:
		ComponentBlockTag() {}
		~ComponentBlockTag() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;

		/**
		 * @brief Add a tag
		 * @param tag Name of the tag
		 * @return ComponentBlockTag&
		 */
		ComponentBlockTag& Add(std::string tag);

		/**
		 * @brief Adds a set of tags
		 * @param tags Set of tags
		 * @return ComponentBlockTag&
		 */
		ComponentBlockTag& Add(std::set<std::string> tags);
		
		/**
		 * @brief Removes a tag
		 * @param tag Name of the tag
		 * @return ComponentBlockTag&
		 */
		ComponentBlockTag& Remove(std::string tag);
	private:
		std::set<std::string> tags_;
	};
} // namespace adk