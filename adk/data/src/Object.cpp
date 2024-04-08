#include "object.h"

#include <string>

#include "block.h"
#include "registry_global.h"
#include "item.h"
#include "registry.h"

Object::Object(std::string id) { mod_id = id; }

void Object::init() {
    Registry<Block>* blocks = new Registry<Block>(mod_id);
    Registry<Item>* items = new Registry<Item>(mod_id);

    globalregistry.push_back(blocks);
    globalregistry.push_back(items);

    blocks->subscribe("custom_block", new Block(BlockProperty()));
    items->subscribe("custom_item", new Item(ItemProperty()));
}