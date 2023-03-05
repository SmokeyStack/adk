#include "Object.h"

#include <string>

#include "Block.h"
#include "GlobalRegistry.h"
#include "Item.h"
#include "Registry.h"

Object::Object(std::string id) { mod_id = id; }

void Object::init() {
    Registry<Block>* block = new Registry<Block>(mod_id);
    Registry<Item>* item = new Registry<Item>(mod_id);

    globalregistry.push_back(block);
    globalregistry.push_back(item);

    block->subscribe("custom_block", new Block(BlockProperty()));
    item->subscribe("custom_item", new Item(ItemProperty()));
}