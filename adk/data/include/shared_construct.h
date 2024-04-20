#pragma once

#include <string>
#include <variant>
#include <vector>

#include "json.hpp"
#include "utility/logger.h"

namespace adk {
	struct BlockDescriptor {
		std::string name;
		std::map<std::string, std::variant<std::string, int, bool>> states;
		std::string tags;
	};

	static void to_json(nlohmann::json& j, const BlockDescriptor& p) {
		if (!p.tags.empty()) {
			j.update({ { "tags", p.tags } });

			return;
		}

		j.update({ { "name", p.name } });

		for (auto const& [key, val] : p.states) {
			if (std::holds_alternative<std::string>(val)) {
				j["states"].update({{key, std::get<std::string>(val)}});
			}
			else if (std::holds_alternative<int>(val)) {
				j["states"].update({ { key, std::get<int>(val)} });
			}
			else if (std::holds_alternative<bool>(val)) {
				j["states"].update({ { key, std::get<bool>(val) } });
			}
		}
	}
} // namespace adk