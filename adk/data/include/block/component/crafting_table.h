#pragma once

#include "component.h"

namespace adk {
	/**
	 * @brief "minecraft:crafting_table" component
	 * Makes your block into a custom crafting table which enables the crafting table UI and the ability to craft recipes
	 */
	class ComponentBlockCraftingTable : public Component {
	public:
		/**
		 * @brief "minecraft:crafting_table" component
		 * 
		 * @param table_name Specifies the language file key that maps to what text will be displayed in the UI of this table.
		 * If the string given can not be resolved as a loc string, the raw string given will be displayed.
		 * If this field is omitted, the name displayed will default to the name specified in the minecraft:display_name component.
		 * If this block has no minecraft:display_name component, the name displayed will default to the name of the block.
		 */
		ComponentBlockCraftingTable(std::string table_name) : table_name_(table_name) {}

		/**
		 * @brief "minecraft:crafting_table" component
		 *
		 * @param table_name Specifies the language file key that maps to what text will be displayed in the UI of this table.
		 * If the string given can not be resolved as a loc string, the raw string given will be displayed.
		 * If this field is omitted, the name displayed will default to the name specified in the minecraft:display_name component.
		 * If this block has no minecraft:display_name component, the name displayed will default to the name of the block.
		 * 
		 * @param tags Defines the tags recipes should define to be crafted on this table.
		 * Limited to 64 tags.
		 * Each tag is limited to 64 characters.
		 */
		ComponentBlockCraftingTable(std::string table_name, std::vector<std::string> tags) : table_name_(table_name), tags_(tags) {}
		~ComponentBlockCraftingTable() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::string table_name_;
		std::vector<std::string> tags_;
	};
} // namespace adk