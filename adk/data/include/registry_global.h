#pragma once

#include <string>
#include <vector>

#include "registry.h"

namespace adk {
	/**
	 * @brief Stores the registry entries to be used across the whole api
	 */
	extern std::vector<Registrar*> registry_global;

	/**
	 * @brief Stores the vanilla entries to be used across the whole api
	 */
	extern std::vector<std::string> registry_vanilla;

	/**
	 * @brief Gets all the entries from the registry
	*/
	extern std::vector<std::string> GetIDs();
} // namespace adk