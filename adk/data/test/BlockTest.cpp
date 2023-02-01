#include <iostream>

#include "Block.h"
#include "BlockProperty.h"
#include "Registry.h"

int main() {
    const std::string MODID = "custom_namespace";
    Registry<Block> mod(MODID);

    mod.subscribe("basic_block", new Block(BlockProperty::Property()));

    try {
        mod.subscribe("error");
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}