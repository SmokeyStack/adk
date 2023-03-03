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

    mod.subscribe("basic_block", new Block(BlockProperty()));
    mod.subscribe("basic_block_light_filter",
                  new Block(BlockProperty().setBlockLightFilter(5)));
    mod.subscribe("basic_block_crafting", new Block(BlockProperty().setCrafting(
                                              tags, "Custom Crafting Table")));
    mod.subscribe("basic_block_explosion_bool",
                  new Block(BlockProperty().setExplosion(false)));
    mod.subscribe("basic_block_explosion_double",
                  new Block(BlockProperty().setExplosion(5.5)));
    mod.subscribe("basic_block_mining_bool",
                  new Block(BlockProperty().setMining(false)));
    mod.subscribe("basic_block_mining_double",
                  new Block(BlockProperty().setMining(5.5)));
    mod.subscribe("basic_block_name",
                  new Block(BlockProperty().setName("Custom Name")));
    mod.subscribe("basic_block_flammable",
                  new Block(BlockProperty().setFlammable(5, 5)));
    mod.subscribe("basic_block_friction",
                  new Block(BlockProperty().setFriction(0.5)));
    mod.subscribe("basic_block_geometry",
                  new Block(BlockProperty().setGeometry("custom_geometry")));
    mod.subscribe("basic_block_light_emission",
                  new Block(BlockProperty().setLightEmission(5)));
    mod.subscribe("basic_block_loot",
                  new Block(BlockProperty().setLoot("path/to/loot.json")));
    mod.subscribe("basic_block_color",
                  new Block(BlockProperty().setColor("000000")));
    mod.subscribe(
        "basic_block_rotation",
        new Block(BlockProperty().setRotation(std::vector<int>{90, 90, 90})));

    mod.subscribe("basic_block_collision_bool",
                  new Block(BlockProperty().setCollision(false)));
    mod.subscribe(
        "basic_block_collision_vector",
        new Block(BlockProperty().setCollision(std::make_pair(
            std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8}))));
    mod.subscribe("basic_block_selection_bool",
                  new Block(BlockProperty().setSelection(false)));
    mod.subscribe(
        "basic_block_selection_vector",
        new Block(BlockProperty().setSelection(std::make_pair(
            std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8}))));

    bool basic = compareFiles("../../test/files/blocks/basic_block.json",
                              "./BP/blocks/basic_block.json");
    bool light_filter =
        compareFiles("../../test/files/blocks/basic_block_light_filter.json",
                     "./BP/blocks/basic_block_light_filter.json");
    bool crafting =
        compareFiles("../../test/files/blocks/basic_block_crafting.json",
                     "./BP/blocks/basic_block_crafting.json");
    bool explosion_bool =
        compareFiles("../../test/files/blocks/basic_block_explosion_bool.json",
                     "./BP/blocks/basic_block_explosion_bool.json");
    bool explosion_double = compareFiles(
        "../../test/files/blocks/basic_block_explosion_double.json",
        "./BP/blocks/basic_block_explosion_double.json");
    bool mining_bool =
        compareFiles("../../test/files/blocks/basic_block_mining_bool.json",
                     "./BP/blocks/basic_block_mining_bool.json");
    bool mining_double =
        compareFiles("../../test/files/blocks/basic_block_mining_double.json",
                     "./BP/blocks/basic_block_mining_double.json");
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
    bool collision_bool =
        compareFiles("../../test/files/blocks/basic_block_collision_bool.json",
                     "./BP/blocks/basic_block_collision_bool.json");
    bool collision_vector = compareFiles(
        "../../test/files/blocks/basic_block_collision_vector.json",
        "./BP/blocks/basic_block_collision_vector.json");
    bool selection_bool =
        compareFiles("../../test/files/blocks/basic_block_selection_bool.json",
                     "./BP/blocks/basic_block_selection_bool.json");
    bool selection_vector = compareFiles(
        "../../test/files/blocks/basic_block_selection_vector.json",
        "./BP/blocks/basic_block_selection_vector.json");

    EXPECT_EQ(true, basic) << "Block is not working as expected";
    EXPECT_EQ(true, light_filter)
        << "setBlockLightFilter is not working as expected";
    EXPECT_EQ(true, crafting) << "setCrafting is not working as expected";
    EXPECT_EQ(true, explosion_bool)
        << "setExplosion(bool) is not working as expected";
    EXPECT_EQ(true, explosion_double)
        << "setExplosion(double) is not working as expected";
    EXPECT_EQ(true, mining_bool)
        << "setMining(bool) is not working as expected";
    EXPECT_EQ(true, mining_double)
        << "setMining(double) is not working as expected";
    EXPECT_EQ(true, name) << "setName is not working as expected";
    EXPECT_EQ(true, flammable) << "setFlammable is not working as expected";
    EXPECT_EQ(true, friction) << "setFriction is not working as expected";
    EXPECT_EQ(true, geometry) << "setGeometry is not working as expected";
    EXPECT_EQ(true, light_emission)
        << "setLightEmission is not working as expected";
    EXPECT_EQ(true, loot) << "setLoot is not working as expected";
    EXPECT_EQ(true, color) << "setColor is not working as expected";
    EXPECT_EQ(true, rotation) << "setRotation is not working as expected";
    EXPECT_EQ(true, collision_bool)
        << "setCollision(bool) is not working as expected";
    EXPECT_EQ(true, collision_vector)
        << "setCollision(vector) is not working as expected";
    EXPECT_EQ(true, selection_bool)
        << "setSelection(bool) is not working as expected";
    EXPECT_EQ(true, selection_vector)
        << "setSelection(vector) is not working as expected";
}