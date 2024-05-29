#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <variant>

#include "registry_global.h"
#include "registry.h"
#include "json.hpp"
#include "utility/logger.h"

namespace adk {
	class BuilderLanguage {
	public:
		BuilderLanguage(std::string locale) { locale_ = locale; };

		BuilderLanguage Add(std::string id, std::string value) {
			std::variant<Block*, Item*>* entry = NULL;

			for (const auto& entries : registry_global) {
				entry = entries->Get(id);
				if (std::get_if<Block*>(entry)) break;
				else if (std::get_if<Item*>(entry)) break;
			}

			if (entry == NULL) return;

			std::visit(
				[=](auto&& content) {
					if (content->GetType() == "block")
						this->entries_.push_back("tile." + id + ".name=" + value);
					else if (content->GetType() == "item")
						this->entries_.push_back("item." + id + "=" + value);
				},
				*entry);

			return *this;
		}

		void Build() {
			if (!std::filesystem::exists("./RP/texts/")) std::filesystem::create_directory("./RP/texts/");

			if (!std::filesystem::exists("./RP/texts/" + locale_ + ".lang")) {
				{
					std::ofstream OutputFile("./RP/texts/" + locale_ + ".lang");
					for (const auto& entry : entries_) OutputFile << entry << '\n';
				}
			}
			else {
				{
					std::ofstream OutputFile("./RP/texts/" + locale_ + ".lang", std::ios::app);
					for (const auto& entry : entries_) OutputFile << entry << '\n';
				}
			}
		}
	private:
		std::string locale_;
		std::vector<std::string> entries_;
	};
}  // namespace adk