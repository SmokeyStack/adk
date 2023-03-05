#ifndef GLOBALREGISTRY_H
#define GLOBALREGISTRY_H

#include <vector>

#include "Registry.h"

/**
 * @brief Stores the registry entries to be used across the whole api
 *
 */
extern std::vector<Registrar*> globalregistry;

#endif