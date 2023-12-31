#include "data.h"

#include <string>

#include "registry_global.h"
#include "generator/block_state.h"

Data::Data() {}

void Data::init() { simpleBlock("custom_block", "custom_texture"); }