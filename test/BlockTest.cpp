#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "CheckFile.h"
#include "registry.h"
#include "registry_global.h"
#include "utility/logger.h"

#include "block/block.h"
#include "block/block_experience_dropping.h"
#include "block/block_flower.h"
#include "block/block_ladder.h"
#include "block/block_mushroom.h"
#include "block/block_pillar.h"
#include "block/block_plant.h"
#include "block/block_slab.h"
#include "block/block_stairs.h"
#include "block/block_sugar_cane.h"
#include "block/block_tnt.h"
#include "block/block_torch.h"

namespace fs = std::filesystem;
using namespace adk;

namespace {
	auto console_log_level = Level::Info;
	auto file_log_level = Level::Trace;
	std::filesystem::path log_directory = "logs/debug.log";
	const std::string MOD_ID = "custom_namespace";
	Registry<Block>* mod = new Registry<Block>(MOD_ID);

	static void SetupCommon() {
		SetupLoggerStage1();
		SetupLoggerStage2(log_directory, console_log_level, file_log_level);
	}
}

TEST(BlockTest, BlockBasic) {
	std::filesystem::create_directory("BP");
	std::filesystem::create_directory("RP");

	SetupCommon();

	log::info("Starting Block Basic Test");

	mod->Subscribe("block_basic", &Block());
	mod->Subscribe("block_experience_dropping", &BlockExperienceDropping(5));
	mod->Subscribe("block_plant", &BlockPlant());
	mod->Subscribe("block_flower", &BlockFlower());
	mod->Subscribe("block_ladder", &BlockLadder());
	mod->Subscribe("block_mushroom", &BlockMushroom());
	mod->Subscribe("block_pillar", &BlockPillar());
	mod->Subscribe("block_slab", &BlockSlab("path/to/loot"));
	mod->Subscribe("block_stairs", &BlockStairs());
	mod->Subscribe("block_sugar_cane", &BlockSugarCane());
	mod->Subscribe("block_tnt", &BlockTnt());
	mod->Subscribe("block_torch", &BlockTorch());

	/*mod->Subscribe("block_basic_light_dampening", new Block(BlockProperty().SetLightDampening(5)));
	mod->Subscribe("block_basic_crafting", new Block(BlockProperty().SetCrafting(crafting_table)));
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
	mod->Subscribe("block_basic_filter_tags", new Block(BlockProperty().SetBlockPlacementFilter(filter_tags)));
	mod->Subscribe("block_basic_filter_states", new Block(BlockProperty().SetBlockPlacementFilter(filter_states)));

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
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_filter_tags.json", "./BP/blocks/block_basic_filter_tags.json")) << "SetBlockPlacementFilter (tags) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/blocks/block_basic_filter_states.json", "./BP/blocks/block_basic_filter_states.json")) << "SetBlockPlacementFilter (states) is not working as expected";*/
}

//TEST(BlockTest, BlockAxis) {
//	std::filesystem::create_directory("BP");
//	std::filesystem::create_directory("RP");
//
//	SetupCommon();
//
//	log::info("Starting Block Axis Test");
//
//	mod->Subscribe("block_axis", new BlockAxis(BlockProperty()));
//	mod->Subscribe("block_axis_light_dampening", new BlockAxis(BlockProperty().SetLightDampening(5)));
//	mod->Subscribe("block_axis_crafting", new BlockAxis(BlockProperty().SetCrafting(crafting_tags, "Custom Crafting Table")));
//	mod->Subscribe("block_axis_destructible_by_explosion_bool", new BlockAxis(BlockProperty().SetDestructibleByExplosion(false)));
//	mod->Subscribe("block_axis_destructible_by_explosion_double", new BlockAxis(BlockProperty().SetDestructibleByExplosion(5.5)));
//	mod->Subscribe("block_axis_destructible_by_mining_bool", new BlockAxis(BlockProperty().SetDestructibleByMining(false)));
//	mod->Subscribe("block_axis_destructible_by_mining_double", new BlockAxis(BlockProperty().SetDestructibleByMining(5.5)));
//	mod->Subscribe("block_axis_display_name", new BlockAxis(BlockProperty().SetDisplayName("Custom Name")));
//	mod->Subscribe("block_axis_flammable_bool", new BlockAxis(BlockProperty().SetFlammable(false)));
//	mod->Subscribe("block_axis_flammable_object", new BlockAxis(BlockProperty().SetFlammable(5, 5)));
//	mod->Subscribe("block_axis_friction", new BlockAxis(BlockProperty().SetFriction(0.5)));
//	mod->Subscribe("block_axis_light_emission", new BlockAxis(BlockProperty().SetLightEmission(5)));
//	mod->Subscribe("block_axis_loot", new BlockAxis(BlockProperty().SetLoot("path/to/loot.json")));
//	mod->Subscribe("block_axis_map_color_hex", new BlockAxis(BlockProperty().SetMapColor("#FF9900")));
//	mod->Subscribe("block_axis_map_color_rgb", new BlockAxis(BlockProperty().SetMapColor(std::vector<int>{33, 33, 33})));
//	mod->Subscribe("block_axis_translation", new BlockAxis(BlockProperty().SetTranslation(std::vector<double>{5, 5, 5})));
//	mod->Subscribe("block_axis_scale", new BlockAxis(BlockProperty().SetScale(std::vector<double>{5, 5, 5})));
//	mod->Subscribe("block_axis_box_collision_bool", new BlockAxis(BlockProperty().SetBoxCollision(false)));
//	mod->Subscribe("block_axis_box_collision_vector", new BlockAxis(BlockProperty().SetBoxCollision(std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8})));
//	mod->Subscribe("block_axis_box_selection_bool", new BlockAxis(BlockProperty().SetBoxSelection(false)));
//	mod->Subscribe("block_axis_box_selection_vector", new BlockAxis(BlockProperty().SetBoxSelection(std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8})));
//	mod->Subscribe("block_axis_creative_category", new BlockAxis(BlockProperty().SetCreativeCategory(adk::CreativeCategory::CONSTRUCTION)));
//	mod->Subscribe("block_axis_creative_group", new BlockAxis(BlockProperty().SetCreativeCategory(adk::CreativeCategory::CONSTRUCTION, adk::CreativeGroup::SMITHINGTEMPLATES)));
//	mod->Subscribe("block_axis_filter_tags", new BlockAxis(BlockProperty().SetBlockPlacementFilter(filter_tags)));
//	mod->Subscribe("block_axis_filter_states", new BlockAxis(BlockProperty().SetBlockPlacementFilter(filter_states)));
//
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis.json", "./BP/blocks/block_axis.json")) << "Block is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_light_dampening.json", "./BP/blocks/block_axis_light_dampening.json")) << "SetLightDampening is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_crafting.json", "./BP/blocks/block_axis_crafting.json")) << "SetCrafting is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_destructible_by_explosion_bool.json", "./BP/blocks/block_axis_destructible_by_explosion_bool.json")) << "SetDestructibleByExplosion (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_destructible_by_explosion_double.json", "./BP/blocks/block_axis_destructible_by_explosion_double.json")) << "SetDestructibleByExplosion (double) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_destructible_by_mining_bool.json", "./BP/blocks/block_axis_destructible_by_mining_bool.json")) << "SetDestructibleByMining (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_destructible_by_mining_double.json", "./BP/blocks/block_axis_destructible_by_mining_double.json")) << "SetDestructibleByMining (double) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_display_name.json", "./BP/blocks/block_axis_display_name.json")) << "SetDisplayName is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_flammable_bool.json", "./BP/blocks/block_axis_flammable_bool.json")) << "SetFlammable (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_flammable_object.json", "./BP/blocks/block_axis_flammable_object.json")) << "SetFlammable (object) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_friction.json", "./BP/blocks/block_axis_friction.json")) << "SetFriction is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_light_emission.json", "./BP/blocks/block_axis_light_emission.json")) << "SetLightEmission is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_loot.json", "./BP/blocks/block_axis_loot.json")) << "SetLoot is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_map_color_hex.json", "./BP/blocks/block_axis_map_color_hex.json")) << "SetMapColor (hex) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_map_color_rgb.json", "./BP/blocks/block_axis_map_color_rgb.json")) << "SetMapColor (rgb) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_translation.json", "./BP/blocks/block_axis_translation.json")) << "SetTranslation is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_scale.json", "./BP/blocks/block_axis_scale.json")) << "SetScale is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_box_collision_bool.json", "./BP/blocks/block_axis_box_collision_bool.json")) << "SetBoxCollision (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_box_collision_vector.json", "./BP/blocks/block_axis_box_collision_vector.json")) << "SetBoxCollision (vector) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_box_selection_bool.json", "./BP/blocks/block_axis_box_selection_bool.json")) << "SetBoxSelection (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_box_selection_vector.json", "./BP/blocks/block_axis_box_selection_vector.json")) << "SetBoxSelection (vector) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_creative_category.json", "./BP/blocks/block_axis_creative_category.json")) << "SetCreativeCategory (category) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_creative_group.json", "./BP/blocks/block_axis_creative_group.json")) << "SetCreativeCategory (group) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_filter_tags.json", "./BP/blocks/block_axis_filter_tags.json")) << "SetBlockPlacementFilter (tags) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_axis_filter_states.json", "./BP/blocks/block_axis_filter_states.json")) << "SetBlockPlacementFilter (states) is not working as expected";
//}
//
//TEST(BlockTest, BlockPlant) {
//	std::filesystem::create_directory("BP");
//	std::filesystem::create_directory("RP");
//
//	SetupCommon();
//
//	log::info("Starting Block Plant Test");
//
//	mod->Subscribe("block_plant", new BlockPlant(BlockProperty()));
//	mod->Subscribe("block_plant_light_dampening", new BlockPlant(BlockProperty().SetLightDampening(5)));
//	mod->Subscribe("block_plant_crafting", new BlockPlant(BlockProperty().SetCrafting(crafting_tags, "Custom Crafting Table")));
//	mod->Subscribe("block_plant_destructible_by_explosion_bool", new BlockPlant(BlockProperty().SetDestructibleByExplosion(false)));
//	mod->Subscribe("block_plant_destructible_by_explosion_double", new BlockPlant(BlockProperty().SetDestructibleByExplosion(5.5)));
//	mod->Subscribe("block_plant_destructible_by_mining_bool", new BlockPlant(BlockProperty().SetDestructibleByMining(false)));
//	mod->Subscribe("block_plant_destructible_by_mining_double", new BlockPlant(BlockProperty().SetDestructibleByMining(5.5)));
//	mod->Subscribe("block_plant_display_name", new BlockPlant(BlockProperty().SetDisplayName("Custom Name")));
//	mod->Subscribe("block_plant_flammable_bool", new BlockPlant(BlockProperty().SetFlammable(false)));
//	mod->Subscribe("block_plant_flammable_object", new BlockPlant(BlockProperty().SetFlammable(5, 5)));
//	mod->Subscribe("block_plant_friction", new BlockPlant(BlockProperty().SetFriction(0.5)));
//	mod->Subscribe("block_plant_light_emission", new BlockPlant(BlockProperty().SetLightEmission(5)));
//	mod->Subscribe("block_plant_loot", new BlockPlant(BlockProperty().SetLoot("path/to/loot.json")));
//	mod->Subscribe("block_plant_map_color_hex", new BlockPlant(BlockProperty().SetMapColor("#FF9900")));
//	mod->Subscribe("block_plant_map_color_rgb", new BlockPlant(BlockProperty().SetMapColor(std::vector<int>{33, 33, 33})));
//	mod->Subscribe("block_plant_translation", new BlockPlant(BlockProperty().SetTranslation(std::vector<double>{5, 5, 5})));
//	mod->Subscribe("block_plant_scale", new BlockPlant(BlockProperty().SetScale(std::vector<double>{5, 5, 5})));
//	mod->Subscribe("block_plant_rotation", new BlockPlant(BlockProperty().SetRotation(std::vector<int>{90, 90, 90})));
//	mod->Subscribe("block_plant_box_collision_bool", new BlockPlant(BlockProperty().SetBoxCollision(false)));
//	mod->Subscribe("block_plant_box_collision_vector", new BlockPlant(BlockProperty().SetBoxCollision(std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8})));
//	mod->Subscribe("block_plant_box_selection_bool", new BlockPlant(BlockProperty().SetBoxSelection(false)));
//	mod->Subscribe("block_plant_box_selection_vector", new BlockPlant(BlockProperty().SetBoxSelection(std::vector<int>{-4, 0, -4}, std::vector<int>{8, 8, 8})));
//	mod->Subscribe("block_plant_creative_category", new BlockPlant(BlockProperty().SetCreativeCategory(adk::CreativeCategory::CONSTRUCTION)));
//	mod->Subscribe("block_plant_creative_group", new BlockPlant(BlockProperty().SetCreativeCategory(adk::CreativeCategory::CONSTRUCTION, adk::CreativeGroup::SMITHINGTEMPLATES)));
//	mod->Subscribe("block_plant_filter_tags", new BlockPlant(BlockProperty().SetBlockPlacementFilter(filter_tags)));
//	mod->Subscribe("block_plant_filter_states", new BlockPlant(BlockProperty().SetBlockPlacementFilter(filter_states)));
//
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant.json", "./BP/blocks/block_plant.json")) << "Block is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_light_dampening.json", "./BP/blocks/block_plant_light_dampening.json")) << "SetLightDampening is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_crafting.json", "./BP/blocks/block_plant_crafting.json")) << "SetCrafting is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_destructible_by_explosion_bool.json", "./BP/blocks/block_plant_destructible_by_explosion_bool.json")) << "SetDestructibleByExplosion (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_destructible_by_explosion_double.json", "./BP/blocks/block_plant_destructible_by_explosion_double.json")) << "SetDestructibleByExplosion (double) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_destructible_by_mining_bool.json", "./BP/blocks/block_plant_destructible_by_mining_bool.json")) << "SetDestructibleByMining (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_destructible_by_mining_double.json", "./BP/blocks/block_plant_destructible_by_mining_double.json")) << "SetDestructibleByMining (double) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_display_name.json", "./BP/blocks/block_plant_display_name.json")) << "SetDisplayName is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_flammable_bool.json", "./BP/blocks/block_plant_flammable_bool.json")) << "SetFlammable (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_flammable_object.json", "./BP/blocks/block_plant_flammable_object.json")) << "SetFlammable (object) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_friction.json", "./BP/blocks/block_plant_friction.json")) << "SetFriction is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_light_emission.json", "./BP/blocks/block_plant_light_emission.json")) << "SetLightEmission is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_loot.json", "./BP/blocks/block_plant_loot.json")) << "SetLoot is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_map_color_hex.json", "./BP/blocks/block_plant_map_color_hex.json")) << "SetMapColor (hex) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_map_color_rgb.json", "./BP/blocks/block_plant_map_color_rgb.json")) << "SetMapColor (rgb) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_translation.json", "./BP/blocks/block_plant_translation.json")) << "SetTranslation is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_scale.json", "./BP/blocks/block_plant_scale.json")) << "SetScale is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_rotation.json", "./BP/blocks/block_plant_rotation.json")) << "SetRotation is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_box_collision_bool.json", "./BP/blocks/block_plant_box_collision_bool.json")) << "SetBoxCollision (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_box_collision_vector.json", "./BP/blocks/block_plant_box_collision_vector.json")) << "SetBoxCollision (vector) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_box_selection_bool.json", "./BP/blocks/block_plant_box_selection_bool.json")) << "SetBoxSelection (bool) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_box_selection_vector.json", "./BP/blocks/block_plant_box_selection_vector.json")) << "SetBoxSelection (vector) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_creative_category.json", "./BP/blocks/block_plant_creative_category.json")) << "SetCreativeCategory (category) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_creative_group.json", "./BP/blocks/block_plant_creative_group.json")) << "SetCreativeCategory (group) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_filter_tags.json", "./BP/blocks/block_plant_filter_tags.json")) << "SetBlockPlacementFilter (tags) is not working as expected";
//	EXPECT_EQ(true, CompareFiles("./files/blocks/block_plant_filter_states.json", "./BP/blocks/block_plant_filter_states.json")) << "SetBlockPlacementFilter (states) is not working as expected";
//}
