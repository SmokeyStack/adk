#pragma once

#include "component.h"

namespace adk {
	class ComponentBlockCraftingTable : public Component {
	public:
		ComponentBlockCraftingTable(std::string table_name) : table_name_(table_name) {}
		ComponentBlockCraftingTable(std::string table_name, std::vector<std::string> tags) : table_name_(table_name), tags_(tags) {}
		~ComponentBlockCraftingTable() {}
		nlohmann::json::object_t Generate() override;
		std::string GetType() override;
	private:
		std::string table_name_;
		std::vector<std::string> tags_;
	};
} // namespace adk