#include "data.h"

#include <string>

#include "generator/state_block.h"
#include "registry_global.h"

namespace adk {
	Data::Data() {}

	void Data::init() { simpleBlock("custom_block", "custom_texture"); }
}  // namespace adk