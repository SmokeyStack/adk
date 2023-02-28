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
    mod.subscribe("basic_block_light_filter",
                  new Block(BlockProperty::Property().setBlockLightFilter(5)));
    mod.subscribe("basic_block_crafting",
                  new Block(BlockProperty::Property().setCrafting(
                      tags, "Custom Crafting Table")));
    mod.subscribe("basic_block_explosion",
                  new Block(BlockProperty::Property().setExplosion(5.5)));
    mod.subscribe("basic_block_mining",
                  new Block(BlockProperty::Property().setMining(5.5)));
    mod.subscribe("basic_block_name",
                  new Block(BlockProperty::Property().setName("Custom Name")));
    mod.subscribe("basic_block_flammable",
                  new Block(BlockProperty::Property().setFlammable(5, 5)));
    mod.subscribe("basic_block_friction",
                  new Block(BlockProperty::Property().setFriction(0.5)));
    mod.subscribe(
        "basic_block_geometry",
        new Block(BlockProperty::Property().setGeometry("custom_geometry")));
    mod.subscribe("basic_block_light_emission",
                  new Block(BlockProperty::Property().setLightEmission(5)));
    mod.subscribe(
        "basic_block_loot",
        new Block(BlockProperty::Property().setLoot("path/to/loot.json")));
    mod.subscribe("basic_block_color",
                  new Block(BlockProperty::Property().setColor("000000")));
    mod.subscribe("basic_block_rotation",
                  new Block(BlockProperty::Property().setRotation(
                      std::vector<int>{90, 90, 90})));
    mod.subscribe(
        "basic_block_collision",
        new Block(BlockProperty::Property().setCollision(
            std::vector<int>{-8, 0, -8}, std::vector<int>{16, 16, 16})));
    mod.subscribe(
        "basic_block_selection",
        new Block(BlockProperty::Property().setSelection(
            std::vector<int>{-8, 0, -8}, std::vector<int>{16, 16, 16})));

    bool basic = compareFiles("../../test/files/blocks/basic_block.json",
                              "./BP/blocks/basic_block.json");
    bool light_filter =
        compareFiles("../../test/files/blocks/basic_block_light_filter.json",
                     "./BP/blocks/basic_block_light_filter.json");
    bool crafting =
        compareFiles("../../test/files/blocks/basic_block_crafting.json",
                     "./BP/blocks/basic_block_crafting.json");
    bool explosion =
        compareFiles("../../test/files/blocks/basic_block_explosion.json",
                     "./BP/blocks/basic_block_explosion.json");
    bool mining =
        compareFiles("../../test/files/blocks/basic_block_mining.json",
                     "./BP/blocks/basic_block_mining.json");
    bool name = compareFiles("../../test/files/blocks/basic_block_name.json",
                             "./BP/blocks/basic_block_name.json");
    bool flammable =
        compareFiles("../../test/files/blocks/basic_block_flammable.json",
                     "./BP/blocks/basic_block_flammable.json");
    bool friction =
        compareFiles("../../test/files/blocks/basic_block_friction.json",
                     "./BP/blocks/basic_block_friction.json");
    bool geometry =
        compareFiles("../../test/files/blocks/basic_block_geometry.json",
                     "./BP/blocks/basic_block_geometry.json");
    bool light_emission =
        compareFiles("../../test/files/blocks/basic_block_light_emission.json",
                     "./BP/blocks/basic_block_light_emission.json");
    bool loot = compareFiles("../../test/files/blocks/basic_block_loot.json",
                             "./BP/blocks/basic_block_loot.json");
    bool color = compareFiles("../../test/files/blocks/basic_block_color.json",
                              "./BP/blocks/basic_block_color.json");
    bool rotation =
        compareFiles("../../test/files/blocks/basic_block_rotation.json",
                     "./BP/blocks/basic_block_rotation.json");
    bool collision =
        compareFiles("../../test/files/blocks/basic_block_collision.json",
                     "./BP/blocks/basic_block_collision.json");
    bool selection =
        compareFiles("../../test/files/blocks/basic_block_selection.json",
                     "./BP/blocks/basic_block_selection.json");

    EXPECT_EQ(true, basic) << "Block is not working as expected";
    EXPECT_EQ(true, light_filter)
        << "setBlockLightFilter is not working as expected";
    EXPECT_EQ(true, crafting) << "setCrafting is not working as expected";
    EXPECT_EQ(true, explosion) << "setExplosion is not working as expected";
    EXPECT_EQ(true, mining) << "setMining is not working as expected";
    EXPECT_EQ(true, name) << "setName is not working as expected";
    EXPECT_EQ(true, flammable) << "setFlammable is not working as expected";
    EXPECT_EQ(true, friction) << "setFriction is not working as expected";
    EXPECT_EQ(true, geometry) << "setGeometry is not working as expected";
    EXPECT_EQ(true, light_emission)
        << "setLightEmission is not working as expected";
    EXPECT_EQ(true, loot) << "setLoot is not working as expected";
    EXPECT_EQ(true, color) << "setColor is not working as expected";
    EXPECT_EQ(true, rotation) << "setRotation is not working as expected";
    EXPECT_EQ(true, collision) << "setCollision is not working as expected";
    EXPECT_EQ(true, selection) << "setSelection is not working as expected";
}