#include "object.h"

#include <string>

#include "block/block.h"
#include "item/item.h"
#include "registry.h"
#include "registry_global.h"

namespace adk {
	Object::Object(std::string id) { mod_id = id; }

	void Object::init() {
		Registry<Block>* blocks = new Registry<Block>(mod_id);
		Registry<Item>* items = new Registry<Item>(mod_id);

		registry_global.push_back(blocks);
		registry_global.push_back(items);

		blocks->Subscribe("custom_block", new Block(BlockProperty()));
		items->Subscribe("custom_item", new Item(ItemProperty()));
	}
} // namespace adk