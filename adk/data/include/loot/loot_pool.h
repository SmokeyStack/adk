#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "json.hpp"
#include "loot/loot_entry.h"
#include "registry.h"

namespace adk {
	/**
	 * @brief Builds the loot table
	 */
	class LootPool {
	public:
		LootPool rolls(int rolls) {
			rolls_ = rolls;

			return *this;
		}

		LootPool with(LootEntry entry) {
			entries_.push_back(entry);

			return *this;
		}

		int GetRolls() const {
			return rolls_;
		}

		std::vector<LootEntry> GetEntries() const {
			return entries_;
		}
	private:
		int rolls_ = 1;
		std::vector<LootEntry> entries_;
	};

	void to_json(nlohmann::json& j, const LootPool& pool) {
		j = nlohmann::json::object();
		j["rolls"] = pool.GetRolls();
		j["entries"] = nlohmann::json::array();

		for (auto& entry : pool.GetEntries()) {
			j["entries"].push_back(entry);
		}
	}
} // namespace adk