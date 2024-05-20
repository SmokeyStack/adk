#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#include "json.hpp"
#include "loot/loot_pool.h"

namespace adk {
	/**
	 * @brief Builds the loot table
	 */
	class BuilderLoot {
	public:
		BuilderLoot pool(LootPool pool){
			pools_.push_back(pool);

			return *this;
		}

		nlohmann::json save(std::string id) {
			id_ = id;
			nlohmann::json result;
			result["pools"] = nlohmann::json::array();

			for (auto& pool : pools_) {
				result["pools"].push_back(pool);
			}

			CreateLootTable(id_, result);
			
			return result;
		}
	protected:
		/**
		 * @brief Create the loot table
		 *
		 * @param id Loot table file path
		 *
		 * @param loot The loot table
		 */
		void CreateLootTable(std::string id, nlohmann::json loot) {
			if (!std::filesystem::exists("./BP/loot_tables/")) std::filesystem::create_directory("./BP/loot_tables/");

			{
				std::ofstream OutputFile("./BP/loot_tables/" + id + ".json");
				OutputFile << loot.dump();
			}
		}
	private:
		std::string id_;
		std::vector<LootPool> pools_;
	};
}