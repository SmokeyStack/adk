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
		std::vector<std::string> tags;
	};

	static void to_json(nlohmann::json& j, const BlockDescriptor& p) {
		if (!p.tags.empty()) {
			std::string query;
			for (std::string var : p.tags) {
				query.append("'" + var + "',");
			}
			query.pop_back();
			j.update({ { "tags", "q.any_tag(" + query + ")" } });

			return;
		}

		j.update({ { "name", p.name } });

		for (auto const& [key, val] : p.states) {
			if (std::holds_alternative<std::string>(val)) {
				j["states"].update({ {key, std::get<std::string>(val)} });
			}
			else if (std::holds_alternative<int>(val)) {
				j["states"].update({ { key, std::get<int>(val)} });
			}
			else if (std::holds_alternative<bool>(val)) {
				j["states"].update({ { key, std::get<bool>(val) } });
			}
		}
	}

	enum class BlockFaces {
		UP,
		DOWN,
		NORTH,
		EAST,
		SOUTH,
		WEST,
		SIDE,
		ALL
	};

	inline std::string BlockFacesToString(BlockFaces face) {
		switch (face) {
		case BlockFaces::UP:
			return "up";
		case BlockFaces::DOWN:
			return "down";
		case BlockFaces::NORTH:
			return "north";
		case BlockFaces::EAST:
			return "east";
		case BlockFaces::SOUTH:
			return "south";
		case BlockFaces::WEST:
			return "west";
		case BlockFaces::SIDE:
			return "side";
		case BlockFaces::ALL:
			return "all";
		default:
			throw std::runtime_error(fmt::format("Invalid BlockFaces value provided: {}", static_cast<int>(face)));
		}
	}
} // namespace adk