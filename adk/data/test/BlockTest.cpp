#include <iostream>

#include "Block.h"
#include "BlockProperty.h"
#include "Registry.h"

int main() {
    const std::string MODID = "custom_namespace";
    Registry<Block> mod(MODID);

    mod.subscribe("basic_block", new Block(BlockProperty::Property()));

    return 0;
}