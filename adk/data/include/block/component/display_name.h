#pragma once

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:display_name" component
	 * Specifies the language file key that maps to what text will be displayed when you hover over the block in your inventory and hotbar.
	 * If the string given can not be resolved as a loc string, the raw string given will be displayed.
	 * If this component is omitted, the name of the block will be used as the display name.
	 */
	class ComponentBlockDisplayName : public Component {
	public:
		/**
		 * @brief Construct a new Component Block Display Name object
		 *
		 * @param display_name The language file key that maps to what text will be displayed when you hover over the block in your inventory and hotbar.
		 */
		ComponentBlockDisplayName(std::string display_name) : display_name_(display_name) {}
		~ComponentBlockDisplayName() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::string display_name_;
	};
} // namespace adk