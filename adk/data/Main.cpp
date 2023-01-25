#include "Block.h"
#include "Registry.h"

int main() {
    const std::string MODID = "custom_namespace";
    Registry<Block> mod(MODID);

    return 0;
}