#pragma once

#include "json.hpp"
#include "utility/logger.h"

namespace adk {
	/**
	 * @brief Builds the function for a loot entry.
	 */
	class LootFunction {
	public:
		LootFunction() {}

		virtual nlohmann::json Generate() {
			log::error("LootFunction::Generate() - This function should be overridden!");

			return nlohmann::json();
		}
	};
}