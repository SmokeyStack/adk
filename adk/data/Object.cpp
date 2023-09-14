#include "Object.h"

#include <string>

#include "Block.h"
#include "GlobalRegistry.h"
#include "Item.h"
#include "Registry.h"

Object::Object(std::string id) { mod_id = id; }

void Object::init() {
    Registry<Block> blocks(mod_id);
    Registry<Item> items(mod_id);

    globalregistry.push_back(blocks);
    globalregistry.push_back(items);

    blocks.subscribe("custom_block", new Block(BlockProperty()));
    items.subscribe("custom_item", new Item(ItemProperty()));
}