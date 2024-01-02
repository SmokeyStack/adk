#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "block.h"
#include "block_axis.h"
#include "block_property.h"
#include "CheckFile.h"
#include "registry.h"
#include "registry_global.h"
#include "utility/logger.h"

namespace fs = std::filesystem;
using namespace adk;

TEST(BlockTest, BlockBasic) {
	std::filesystem::create_directory("BP");
	std::filesystem::create_directory("RP");

	SetupLoggerStage1();

	auto console_log_level = Level::Info;
	auto file_log_level = Level::Trace;
	std::filesystem::path log_directory = "logs/debug.log";

	SetupLoggerStage2(log_directory, console_log_level, file_log_level);

	log::info("Starting Block Basic Test");

	const std::string MOD_ID = "custom_namespace";
	Registry<Block>* mod = new Registry<Block>(MOD_ID);
	registry_global.push_back(mod);
	std::vector<std::string> crafting_tags = { "custom_crafting_table" };

	mod->Subscribe("block_basic", new Block(BlockProperty()));
	mod->Subscribe("block_basic_light_dampening", new Block(BlockProperty().SetLightDampening(5)));
	mod->Subscribe("block_basic_crafting", new Block(BlockProperty().SetCrafting(crafting_tags, "Custom Crafting Table")));
	mod->Subscribe("block_basic_destructible_by_explosion_bool", new Block(BlockProperty().SetDestructibleByExplosion(false)));
	mod->Subscribe("block_basic_destructible_by_explosion_double", new Block(BlockProperty().SetDestructibleByExplosion(5.5)));
	mod->Subscribe("block_basic_destructible_by_mining_bool", new Block(BlockProperty().SetDestructibleByMining(false)));
	mod->Subscribe("block_basic_destructible_by_mining_double", new Block(BlockProperty().SetDestructibleByMining(5.5)));
	mod->Subscribe("block_basic_display_name", new Block(BlockProperty().SetDisplayName("Custom Name")));
	mod->Subscribe("block_basic_flammable_bool", new Block(BlockProperty().SetFlammable(false)));
	mod->Subscribe("block_basic_flammable_object", new Block(BlockProperty().SetFlammable(5, 5)));
	mod->Subscribe("block_basic_friction", new Block(BlockProperty().SetFriction(0.5)));
	mod->Subscribe("block_basic_light_emission", new Block(BlockProperty().SetLightEmission(5)));
	mod->Subscribe("block_basic_loot", new Block(BlockProperty().SetLoot("path/to/loot.json")));
	mod->Subscribe("block_basic_map_color_hex", new Block(BlockProperty().SetMapColor("#FF9900")));
	mod->Subscribe("block_basic_map_color_rgb", new Block(BlockProperty().SetMapColor(std::vector<int>{33, 33, 33})));
	mod->Subscribe("block_basic_translation", new Block(BlockProperty().SetTranslation(std::vector<double>{5, 5, 5})));
	mod->Subscribe("block_basic_scale", new Block(BlockProperty().SetScale(std::vector<double>{5, 5, 5})));
	mod->Subscribe("block_basic_rotation", new Block(BlockProperty().SetRotation(std::vector<int>{90, 90, 90})));
	mod->Subscribe("block_basic_box_collision_bool", new Block(BlockProperty().SetBoxCollision(false)));
	mod->Subscribe("block_basic_box_collision_vector", new Block(BlockProperty().SetBoxCollision(std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8})));
	mod->Subscribe("block_basic_box_selection_bool", new Block(BlockProperty().SetBoxSelection(false)));
	mod->Subscribe("block_basic_box_selection_vector", new Block(BlockProperty().SetBoxSelection(std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8})));
	mod->Subscribe("block_basic_creative_category", new Block(BlockProperty().SetCreativeCategory(adk::CreativeCategory::CONSTRUCTION)));
	mod->Subscribe("block_basic_creative_group", new Block(BlockProperty().SetCreativeCategory(adk::CreativeCategory::CONSTRUCTION, adk::CreativeGroup::SMITHINGTEMPLATES)));

	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic.json", "./BP/blocks/block_basic.json")) << "Block is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_light_dampening.json", "./BP/blocks/block_basic_light_dampening.json")) << "SetLightDampening is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_crafting.json", "./BP/blocks/block_basic_crafting.json")) << "SetCrafting is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_destructible_by_explosion_bool.json", "./BP/blocks/block_basic_destructible_by_explosion_bool.json")) << "SetDestructibleByExplosion (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_destructible_by_explosion_double.json", "./BP/blocks/block_basic_destructible_by_explosion_double.json")) << "SetDestructibleByExplosion (double) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_destructible_by_mining_bool.json", "./BP/blocks/block_basic_destructible_by_mining_bool.json")) << "SetDestructibleByMining (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_destructible_by_mining_double.json", "./BP/blocks/block_basic_destructible_by_mining_double.json")) << "SetDestructibleByMining (double) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_display_name.json", "./BP/blocks/block_basic_display_name.json")) << "SetDisplayName is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_flammable_bool.json", "./BP/blocks/block_basic_flammable_bool.json")) << "SetFlammable (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_flammable_object.json", "./BP/blocks/block_basic_flammable_object.json")) << "SetFlammable (object) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_friction.json", "./BP/blocks/block_basic_friction.json")) << "SetFriction is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_light_emission.json", "./BP/blocks/block_basic_light_emission.json")) << "SetLightEmission is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_loot.json", "./BP/blocks/block_basic_loot.json")) << "SetLoot is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_map_color_hex.json", "./BP/blocks/block_basic_map_color_hex.json")) << "SetMapColor (hex) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_map_color_rgb.json", "./BP/blocks/block_basic_map_color_rgb.json")) << "SetMapColor (rgb) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_translation.json", "./BP/blocks/block_basic_translation.json")) << "SetTranslation is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_scale.json", "./BP/blocks/block_basic_scale.json")) << "SetScale is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_rotation.json", "./BP/blocks/block_basic_rotation.json")) << "SetRotation is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_box_collision_bool.json", "./BP/blocks/block_basic_box_collision_bool.json")) << "SetBoxCollision (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_box_collision_vector.json", "./BP/blocks/block_basic_box_collision_vector.json")) << "SetBoxCollision (vector) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_box_selection_bool.json", "./BP/blocks/block_basic_box_selection_bool.json")) << "SetBoxSelection (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_box_selection_vector.json", "./BP/blocks/block_basic_box_selection_vector.json")) << "SetBoxSelection (vector) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_creative_category.json", "./BP/blocks/block_basic_creative_category.json")) << "SetCreativeCategory (category) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_creative_group.json", "./BP/blocks/block_basic_creative_group.json")) << "SetCreativeCategory (group) is not working as expected";
}

TEST(BlockTest, BlockAxis) {
	std::filesystem::create_directory("BP");
	std::filesystem::create_directory("RP");

	SetupLoggerStage1();

	auto console_log_level = Level::Info;
	auto file_log_level = Level::Trace;
	std::filesystem::path log_directory = "logs/debug.log";

	SetupLoggerStage2(log_directory, console_log_level, file_log_level);

	log::info("Starting Block Axis Test");

	const std::string MOD_ID = "custom_namespace";
	Registry<Block>* mod = new Registry<Block>(MOD_ID);
	registry_global.push_back(mod);
	std::vector<std::string> crafting_tags = { "custom_crafting_table" };

	mod->Subscribe("block_axis", new BlockAxis(BlockProperty()));
	mod->Subscribe("block_axis_light_dampening", new BlockAxis(BlockProperty().SetLightDampening(5)));
	mod->Subscribe("block_axis_crafting", new BlockAxis(BlockProperty().SetCrafting(crafting_tags, "Custom Crafting Table")));
	mod->Subscribe("block_axis_destructible_by_explosion_bool", new BlockAxis(BlockProperty().SetDestructibleByExplosion(false)));
	mod->Subscribe("block_axis_destructible_by_explosion_double", new BlockAxis(BlockProperty().SetDestructibleByExplosion(5.5)));
	mod->Subscribe("block_axis_destructible_by_mining_bool", new BlockAxis(BlockProperty().SetDestructibleByMining(false)));
	mod->Subscribe("block_axis_destructible_by_mining_double", new BlockAxis(BlockProperty().SetDestructibleByMining(5.5)));
	mod->Subscribe("block_axis_display_name", new BlockAxis(BlockProperty().SetDisplayName("Custom Name")));
	mod->Subscribe("block_axis_flammable_bool", new BlockAxis(BlockProperty().SetFlammable(false)));
	mod->Subscribe("block_axis_flammable_object", new BlockAxis(BlockProperty().SetFlammable(5, 5)));
	mod->Subscribe("block_axis_friction", new BlockAxis(BlockProperty().SetFriction(0.5)));
	mod->Subscribe("block_axis_light_emission", new BlockAxis(BlockProperty().SetLightEmission(5)));
	mod->Subscribe("block_axis_loot", new BlockAxis(BlockProperty().SetLoot("path/to/loot.json")));
	mod->Subscribe("block_axis_map_color_hex", new BlockAxis(BlockProperty().SetMapColor("#FF9900")));
	mod->Subscribe("block_axis_map_color_rgb", new BlockAxis(BlockProperty().SetMapColor(std::vector<int>{33, 33, 33})));
	mod->Subscribe("block_axis_translation", new BlockAxis(BlockProperty().SetTranslation(std::vector<double>{5, 5, 5})));
	mod->Subscribe("block_axis_scale", new BlockAxis(BlockProperty().SetScale(std::vector<double>{5, 5, 5})));
	mod->Subscribe("block_axis_box_collision_bool", new BlockAxis(BlockProperty().SetBoxCollision(false)));
	mod->Subscribe("block_axis_box_collision_vector", new BlockAxis(BlockProperty().SetBoxCollision(std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8})));
	mod->Subscribe("block_axis_box_selection_bool", new BlockAxis(BlockProperty().SetBoxSelection(false)));
	mod->Subscribe("block_axis_box_selection_vector", new BlockAxis(BlockProperty().SetBoxSelection(std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8})));
	mod->Subscribe("block_axis_creative_category", new BlockAxis(BlockProperty().SetCreativeCategory(adk::CreativeCategory::CONSTRUCTION)));
	mod->Subscribe("block_axis_creative_group", new BlockAxis(BlockProperty().SetCreativeCategory(adk::CreativeCategory::CONSTRUCTION, adk::CreativeGroup::SMITHINGTEMPLATES)));

	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis.json", "./BP/blocks/block_axis.json")) << "Block is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_light_dampening.json", "./BP/blocks/block_axis_light_dampening.json")) << "SetLightDampening is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_crafting.json", "./BP/blocks/block_axis_crafting.json")) << "SetCrafting is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_destructible_by_explosion_bool.json", "./BP/blocks/block_axis_destructible_by_explosion_bool.json")) << "SetDestructibleByExplosion (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_destructible_by_explosion_double.json", "./BP/blocks/block_axis_destructible_by_explosion_double.json")) << "SetDestructibleByExplosion (double) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_destructible_by_mining_bool.json", "./BP/blocks/block_axis_destructible_by_mining_bool.json")) << "SetDestructibleByMining (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_destructible_by_mining_double.json", "./BP/blocks/block_axis_destructible_by_mining_double.json")) << "SetDestructibleByMining (double) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_display_name.json", "./BP/blocks/block_axis_display_name.json")) << "SetDisplayName is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_flammable_bool.json", "./BP/blocks/block_axis_flammable_bool.json")) << "SetFlammable (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_flammable_object.json", "./BP/blocks/block_axis_flammable_object.json")) << "SetFlammable (object) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_friction.json", "./BP/blocks/block_axis_friction.json")) << "SetFriction is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_light_emission.json", "./BP/blocks/block_axis_light_emission.json")) << "SetLightEmission is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_loot.json", "./BP/blocks/block_axis_loot.json")) << "SetLoot is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_map_color_hex.json", "./BP/blocks/block_axis_map_color_hex.json")) << "SetMapColor (hex) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_map_color_rgb.json", "./BP/blocks/block_axis_map_color_rgb.json")) << "SetMapColor (rgb) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_translation.json", "./BP/blocks/block_axis_translation.json")) << "SetTranslation is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_scale.json", "./BP/blocks/block_axis_scale.json")) << "SetScale is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_box_collision_bool.json", "./BP/blocks/block_axis_box_collision_bool.json")) << "SetBoxCollision (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_box_collision_vector.json", "./BP/blocks/block_axis_box_collision_vector.json")) << "SetBoxCollision (vector) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_box_selection_bool.json", "./BP/blocks/block_axis_box_selection_bool.json")) << "SetBoxSelection (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_box_selection_vector.json", "./BP/blocks/block_axis_box_selection_vector.json")) << "SetBoxSelection (vector) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_creative_category.json", "./BP/blocks/block_axis_creative_category.json")) << "SetCreativeCategory (category) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_creative_group.json", "./BP/blocks/block_axis_creative_group.json")) << "SetCreativeCategory (group) is not working as expected";
}