#include "Data.h"

#include <string>

#include "GlobalRegistry.h"
#include "generator/BlockState.h"

Data::Data() {}

void Data::init() { simpleBlock("custom_block", "custom_texture"); }