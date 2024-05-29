#pragma once

#include <variant>

#include "block/block.h"
#include "item/item.h"
#include "json.hpp"
#include "registry.h"
#include "registry_global.h"
#include "utility/logger.h"

namespace adk {
	class BuilderCreativeMenu {
	public:
		BuilderCreativeMenu(std::string id) { mod_id_ = id; }

		void AddItem(std::string id, std::string group = "") {
			std::variant<Block*, Item*>* entry = NULL;

			for (const auto& entries : registry_global) {
				entry = entries->Get(id);
				if (std::get_if<Block*>(entry)) break;
				else if (std::get_if<Item*>(entry)) break;
			}

			if (entry == NULL) return;

			std::visit(
				[=](auto&& content) {
					std::string entry_id = id.substr(id.find(":") + 1);
					const std::string file_path = fmt::format(
						"./BP/{type}s/{id}.json",
						fmt::arg("type", content->GetType()),
						fmt::arg("id", entry_id)
					);
					nlohmann::json output;

					{
						std::ifstream TempFile(file_path);
						TempFile >> output;
					}

					output["minecraft:" + content->GetType()]["description"]["menu_category"]["category"] = mod_id_;

					if (!group.empty())
						output["minecraft:" + content->GetType()]["description"]["menu_category"]["group"] = group;

					{
						std::ofstream OutputFile(file_path);
						OutputFile << output.dump();
					}
				},
				*entry);
		}
	private:
		std::string mod_id_;
	};
} // namespace adk