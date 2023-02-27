#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "../adk/data/include/Block.h"
#include "../adk/data/include/BlockProperty.h"
#include "../adk/data/include/Registry.h"
#include "CheckFile.h"

namespace fs = std::filesystem;

TEST(BlockTest, BasicBlock) {
    const std::string MODID = "custom_namespace";
    Registry<Block> mod(MODID);

    std::vector<std::string> tags = {"custom_crafting_table"};

    mod.subscribe("basic_block", new Block(BlockProperty::Property()));
    mod.subscribe("basic_block_light",
                  new Block(BlockProperty::Property().setBlockLightFilter(5)));
    mod.subscribe("basic_block_crafting",
                  new Block(BlockProperty::Property().setCrafting(
                      tags, "Custom Crafting Table")));
    mod.subscribe("basic_block_explosion",
                  new Block(BlockProperty::Property().setExplosion(5.5)));
    mod.subscribe("basic_block_mining",
                  new Block(BlockProperty::Property().setMining(5.5)));

    bool basic = compareFiles("../../test/files/basic_block.json",
                              "./BP/blocks/basic_block.json");
    bool light = compareFiles("../../test/files/basic_block_light.json",
                              "./BP/blocks/basic_block_light.json");
    bool crafting = compareFiles("../../test/files/basic_block_crafting.json",
                                 "./BP/blocks/basic_block_crafting.json");
    bool explosion = compareFiles("../../test/files/basic_block_explosion.json",
                                  "./BP/blocks/basic_block_explosion.json");
    bool mining = compareFiles("../../test/files/basic_block_mining.json",
                               "./BP/blocks/basic_block_mining.json");

    EXPECT_EQ(true, basic) << "Block is not working as expected";
    EXPECT_EQ(true, light) << "setBlockLightFilter is not working as expected";
    EXPECT_EQ(true, crafting) << "setCrafting is not working as expected";
    EXPECT_EQ(true, explosion) << "setExplosion is not working as expected";
    EXPECT_EQ(true, mining) << "setMining is not working as expected";
}