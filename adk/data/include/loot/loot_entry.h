#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#include "json.hpp"
#include "registry.h"
#include "loot/loot_type.h"
#include "loot/function/loot_function.h"

namespace adk {
	/**
	 * @brief Builds the entry for a loot pool.
	 */
	class LootEntry {
	public:
		LootEntry type(std::string type) {
			type_ = type;

			return *this;
		}

		LootEntry entry(std::string entry) {
			entry_ = entry;

			return *this;
		}

		LootEntry weight(int weight) {
			weight_ = weight;

			return *this;
		}

		LootEntry apply(LootFunction* function) {
			functions_.push_back(function);

			return *this;
		}

		std::string GetType() const {
			return type_;
		}

		std::string GetEntry() const {
			return entry_;
		}

		int GetWeight() const {
			return weight_;
		}

		std::vector<LootFunction*> GetFunctions() const {
			return functions_;
		}
	private:
		std::string type_;
		std::string entry_;
		int weight_ = 1;
		std::vector<LootFunction*> functions_;
	};

	void to_json(nlohmann::json& j, const LootEntry& entry) {
		j = nlohmann::json::object();
		j["type"] = entry.GetType();
		j["name"] = entry.GetEntry();
		j["weight"] = entry.GetWeight();

		if (!entry.GetFunctions().empty()) {
			nlohmann::json functions = nlohmann::json::array();
			for (auto& function : entry.GetFunctions()) {
				nlohmann::json function_json;
				function_json = function->Generate();;
				functions.push_back(function_json);
			}

			j["functions"] = functions;
		}
	}
}