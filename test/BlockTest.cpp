#include <gtest/gtest.h>

#include <filesystem>

#include "../adk/data/include/Block.h"
#include "../adk/data/include/BlockProperty.h"
#include "../adk/data/include/Registry.h"
#include "CheckFile.h"

namespace fs = std::filesystem;

class BlockTest : public ::testing::Test {};
TEST_F(BlockTest, BasicBlock) {
    if (!fs::exists("../../test/files/basic_block.json")) std::cout << "Whaaa";

    const std::string MODID = "custom_namespace";
    Registry<Block> mod(MODID);

    mod.subscribe("basic_block", new Block(BlockProperty::Property()));
    bool check = compareFiles("../../test/files/basic_block.json",
                              "./BP/blocks/basic_block.json");

    EXPECT_EQ(true, check);
}

TEST_F(BlockTest, BasicBlockLight) {
    if (!fs::exists("../../test/files/basic_block.json")) std::cout << "Whaaa";

    const std::string MODID = "custom_namespace";
    Registry<Block> mod(MODID);

    mod.subscribe("basic_block_light",
                  new Block(BlockProperty::Property().setBlockLightFilter(5)));
    bool check = compareFiles("../../test/files/basic_block_light.json",
                              "./BP/blocks/basic_block_light.json");

    EXPECT_EQ(true, check);
}