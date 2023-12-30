#ifndef GLOBALREGISTRY_H
#define GLOBALREGISTRY_H

#include <string>
#include <vector>

#include "Registry.h"

/**
 * @brief Stores the registry entries to be used across the whole api
 *
 */
extern std::vector<Registrar*> globalregistry;

/**
 * @brief Stores the vanilla entries to be used across the whole api
 *
 */
extern std::vector<std::string> vanillaRegistry;

extern std::vector<std::string> getIds();

#endif