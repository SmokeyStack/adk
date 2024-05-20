#include "data.h"

#include <string>

#include "builder_creative_menu.h"
#include "generator/state_block.h"
#include "registry_global.h"

namespace adk {
	Data::Data() {}

	void Data::init() { SimpleBlock("custom_block", BlockTextures{ "custom_texture" }); }

	void Data::RegisterToCreativeMenu() {
		BuilderCreativeMenu construction("construction");
		construction.AddItem("custom_block");
	}
}  // namespace adk