#include <gtest/gtest.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <variant>

#include "block.h"
#include "block_property.h"
#include "CheckFile.h"
#include "registry_global.h"
#include "registry.h"
#include "utility/logger.h"

namespace fs = std::filesystem;

TEST(BlockTest, BasicBlock) {
    std::filesystem::create_directory("BP");
    std::filesystem::create_directory("RP");

    adk::SetupLoggerStage1();

    auto console_log_level = adk::Level::Info;
    auto file_log_level = adk::Level::Trace;
    std::filesystem::path log_directory = "logs/debug.log";

    adk::SetupLoggerStage2(log_directory, console_log_level, file_log_level);

    adk::log::info("Starting Block Test");

    const std::string MODID = "custom_namespace";
    adk::Registry<adk::Block>* mod = new adk::Registry<adk::Block>(MODID);

    adk::registry_global.push_back(mod);

    std::vector<std::string> tags = {"custom_crafting_table"};

    mod->Subscribe("basic_block", new adk::Block(BlockProperty()));

    mod->Subscribe("basic_block_light_filter",
                   new adk::Block(BlockProperty().setBlockLightFilter(5)));
    mod->Subscribe(
        "basic_block_crafting",
        new adk::Block(BlockProperty().setCrafting(tags, "Custom Crafting Table")));
    mod->Subscribe("basic_block_explosion_bool",
                   new adk::Block(BlockProperty().setExplosion(false)));
    mod->Subscribe("basic_block_explosion_double",
                   new adk::Block(BlockProperty().setExplosion(5.5)));
    mod->Subscribe("basic_block_mining_bool",
                   new adk::Block(BlockProperty().setMining(false)));
    mod->Subscribe("basic_block_mining_double",
                   new adk::Block(BlockProperty().setMining(5.5)));
    mod->Subscribe("basic_block_name",
                   new adk::Block(BlockProperty().setName("Custom Name")));
    mod->Subscribe("basic_block_flammable",
                   new adk::Block(BlockProperty().setFlammable(5, 5)));
    mod->Subscribe("basic_block_friction",
                   new adk::Block(BlockProperty().setFriction(0.5)));
    mod->Subscribe("basic_block_geometry",
                   new adk::Block(BlockProperty().setGeometry("custom_geometry")));
    mod->Subscribe("basic_block_light_emission",
                   new adk::Block(BlockProperty().setLightEmission(5)));
    mod->Subscribe("basic_block_loot",
                   new adk::Block(BlockProperty().setLoot("path/to/loot.json")));
    mod->Subscribe("basic_block_color",
                   new adk::Block(BlockProperty().setColor("000000")));
    mod->Subscribe(
        "basic_block_rotation",
        new adk::Block(BlockProperty().setRotation(std::vector<int>{90, 90, 90})));

    mod->Subscribe("basic_block_collision_bool",
                   new adk::Block(BlockProperty().setCollision(false)));
    mod->Subscribe(
        "basic_block_collision_vector",
        new adk::Block(BlockProperty().setCollision(std::make_pair(
            std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8}))));
    mod->Subscribe("basic_block_selection_bool",
                   new adk::Block(BlockProperty().setSelection(false)));
    mod->Subscribe(
        "basic_block_selection_vector",
        new adk::Block(BlockProperty().setSelection(std::make_pair(
            std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8}))));

    bool basic = compareFiles("./files/blocks/basic_block.json",
                              "./BP/blocks/basic_block.json");
    bool light_filter =
        compareFiles("./files/blocks/basic_block_light_filter.json",
                     "./BP/blocks/basic_block_light_filter.json");
    bool crafting =
        compareFiles("./files/blocks/basic_block_crafting.json",
                     "./BP/blocks/basic_block_crafting.json");
    bool explosion_bool =
        compareFiles("./files/blocks/basic_block_explosion_bool.json",
                     "./BP/blocks/basic_block_explosion_bool.json");
    bool explosion_double = compareFiles(
        "./files/blocks/basic_block_explosion_double.json",
        "./BP/blocks/basic_block_explosion_double.json");
    bool mining_bool =
        compareFiles("./files/blocks/basic_block_mining_bool.json",
                     "./BP/blocks/basic_block_mining_bool.json");
    bool mining_double =
        compareFiles("./files/blocks/basic_block_mining_double.json",
                     "./BP/blocks/basic_block_mining_double.json");
    bool name = compareFiles("./files/blocks/basic_block_name.json",
                             "./BP/blocks/basic_block_name.json");
    bool flammable =
        compareFiles("./files/blocks/basic_block_flammable.json",
                     "./BP/blocks/basic_block_flammable.json");
    bool friction =
        compareFiles("./files/blocks/basic_block_friction.json",
                     "./BP/blocks/basic_block_friction.json");
    bool geometry =
        compareFiles("./files/blocks/basic_block_geometry.json",
                     "./BP/blocks/basic_block_geometry.json");
    bool light_emission =
        compareFiles("./files/blocks/basic_block_light_emission.json",
                     "./BP/blocks/basic_block_light_emission.json");
    bool loot = compareFiles("./files/blocks/basic_block_loot.json",
                             "./BP/blocks/basic_block_loot.json");
    bool color = compareFiles("./files/blocks/basic_block_color.json",
                              "./BP/blocks/basic_block_color.json");
    bool rotation =
        compareFiles("./files/blocks/basic_block_rotation.json",
                     "./BP/blocks/basic_block_rotation.json");
    bool collision_bool =
        compareFiles("./files/blocks/basic_block_collision_bool.json",
                     "./BP/blocks/basic_block_collision_bool.json");
    bool collision_vector = compareFiles(
        "./files/blocks/basic_block_collision_vector.json",
        "./BP/blocks/basic_block_collision_vector.json");
    bool selection_bool =
        compareFiles("./files/blocks/basic_block_selection_bool.json",
                     "./BP/blocks/basic_block_selection_bool.json");
    bool selection_vector = compareFiles(
        "./files/blocks/basic_block_selection_vector.json",
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