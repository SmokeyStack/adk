#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "CheckFile.h"
#include "item/armor_materials.h"
#include "item/item.h"
#include "item/item_armor.h"
#include "item/item_armor_stand.h"
#include "item/item_pickaxe.h"
#include "item/item_property.h"
#include "item/tool_materials.h"
#include "registry.h"
#include "registry_global.h"
#include "utility/shared_construct.h"
#include "utility/logger.h"

namespace fs = std::filesystem;
using namespace adk;

namespace {
	auto console_log_level = Level::Info;
	auto file_log_level = Level::Trace;
	std::filesystem::path log_directory = "logs/debug.log";
	const std::string MOD_ID = "custom_namespace";
	Registry<Item>* mod = new Registry<Item>(MOD_ID);

	BlockDescriptor block_descriptor_states = BlockDescriptor();
	BlockDescriptor block_descriptor_tags = BlockDescriptor();
	ItemDigger digger_block_descriptor_states;
	ItemDigger digger_block_descriptor_tags;
	ItemDigger digger_name;
	ItemDiggerDestroySpeeds digger_destroy_speeds_states;
	ItemDiggerDestroySpeeds digger_destroy_speeds_tags;
	ItemDiggerDestroySpeeds digger_destroy_speeds;
	ItemDurability durability = { 10 };
	ItemDurability durability_chance = { 10, std::pair<int, int>{50,100} };
	ItemEntityPlacer entity_placer = { "minecraft:armor_stand" };
	ItemEntityPlacer entity_placer_use_on = { "minecraft:armor_stand" };
	ItemEntityPlacer entity_placer_dispense_on = { "minecraft:armor_stand" };
	ItemEntityPlacer entity_placer_both = { "minecraft:armor_stand" };
	ItemFood food_nutrition;
	ItemFood food_can_always_eat;
	ItemFood food_using_converts_to;
	ItemFood food_saturation_modifier;
	ItemRecord record = { "record.pigstep",10,10 };
	ItemRecord record_comparator_signal = { "record.pigstep" };
	ItemRecord record_duration = { "record.pigstep" };
	ItemRepairable repairable;
	ItemShooter shooter_ammunition_item;
	ItemShooter shooter_ammunition_use_offhand;
	ItemShooter shooter_ammunition_search_inventory;
	ItemShooter shooter_ammunition_use_in_creative;
	ItemShooter shooter_ammunition_two;
	ItemShooter shooter_charge_on_draw;
	ItemShooter shooter_max_draw_duration;
	ItemShooter shooter_scale_power_by_draw_duration;
	ItemShooterAmmunition ammunition_item;
	ItemShooterAmmunition ammunition_item_two;
	ItemShooterAmmunition ammunition_use_offhand;
	ItemShooterAmmunition ammunition_search_inventory;
	ItemShooterAmmunition ammunition_use_in_creative;
	ItemThrowable throwable_do_swing_animation;
	ItemThrowable throwable_launch_power_scale;
	ItemThrowable throwable_max_draw_duration;
	ItemThrowable throwable_max_launch_power;
	ItemThrowable throwable_min_draw_duration;
	ItemThrowable throwable_scale_power_by_draw_duration;

	static void SetupCommon() {
		SetupLoggerStage1();
		SetupLoggerStage2(log_directory, console_log_level, file_log_level);

		registry_global.push_back(mod);
		block_descriptor_states.name = "minecraft:sand";
		block_descriptor_states.states = std::map<std::string, std::variant<std::string, int, bool>>{ {"sand_type", std::string("red")} };
		digger_destroy_speeds_states.block = block_descriptor_states;
		digger_destroy_speeds_states.speed = -1;
		digger_block_descriptor_states.destroy_speeds = { digger_destroy_speeds_states };
		block_descriptor_tags.tags = std::vector<std::string>{ "dirt" };
		digger_destroy_speeds_tags.block = block_descriptor_tags;
		digger_destroy_speeds_tags.speed = -1;
		digger_block_descriptor_tags.destroy_speeds = { digger_destroy_speeds_tags };
		digger_destroy_speeds.block = "minecraft:dirt";
		digger_destroy_speeds.speed = -1;
		digger_name.destroy_speeds = { digger_destroy_speeds };
		entity_placer_use_on.use_on = std::vector<std::string>{ "minecraft:grass", "minecraft:glass" };
		entity_placer_dispense_on.dispense_on = std::vector<std::string>{ "minecraft:grass", "minecraft:glass" };
		entity_placer_both.use_on = std::vector<std::string>{ "minecraft:grass", "minecraft:glass" };
		entity_placer_both.dispense_on = std::vector<std::string>{ "minecraft:grass", "minecraft:glass" };
		food_nutrition.nutrition = 10;
		food_can_always_eat.can_always_eat = true;
		food_using_converts_to.using_converts_to = "minecraft:apple";
		food_saturation_modifier.saturation_modifier = 1.0;
		record_comparator_signal.comparator_signal = 15;
		record_duration.duration_seconds = 10.0;
		repairable.repair_items = std::vector<ItemRepairableItems>{
			{ 1, std::vector<std::string>{"minecraft:stick"}},
			{ "c.other->q.remaining_durability + 0.05 * c.other->q.max_durability", std::vector<std::string>{"minecraft:diamond"}}
		};
		ammunition_item.item = "minecraft:arrow";
		ammunition_item_two.item = "minecraft:trident";
		ammunition_search_inventory.search_inventory = true;
		ammunition_use_in_creative.use_in_creative = true;
		ammunition_use_offhand.use_offhand = true;
		shooter_ammunition_item.ammunition.push_back(ammunition_item);
		shooter_ammunition_two.ammunition.push_back(ammunition_item);
		shooter_ammunition_two.ammunition.push_back(ammunition_item_two);
		shooter_ammunition_search_inventory.ammunition.push_back(ammunition_search_inventory);
		shooter_ammunition_use_in_creative.ammunition.push_back(ammunition_use_in_creative);
		shooter_ammunition_use_offhand.ammunition.push_back(ammunition_use_offhand);
		shooter_charge_on_draw.ammunition.push_back(ammunition_item);
		shooter_charge_on_draw.charge_on_draw = true;
		shooter_max_draw_duration.ammunition.push_back(ammunition_item);
		shooter_max_draw_duration.max_draw_duration = 1.0;
		shooter_scale_power_by_draw_duration.ammunition.push_back(ammunition_item);
		shooter_scale_power_by_draw_duration.scale_power_by_draw_duration = true;
		throwable_do_swing_animation.do_swing_animation = true;
		throwable_launch_power_scale.launch_power_scale = 10.0;
		throwable_max_draw_duration.max_draw_duration = 10.0;
		throwable_max_launch_power.max_launch_power = 10.0;
		throwable_min_draw_duration.min_draw_duration = 10.0;
		throwable_scale_power_by_draw_duration.scale_power_by_draw_duration = true;
	}
}

TEST(ItemTest, ItemBasic) {
	std::filesystem::create_directory("BP");
	std::filesystem::create_directory("RP");

	SetupCommon();

	log::info("Starting Item Basic Test");

	mod->Subscribe("item_basic", new Item(ItemProperty()));
	mod->Subscribe("item_basic_allow_off_hand", new Item(ItemProperty().SetAllowOffHand(true)));
	mod->Subscribe("item_basic_block_placer", new Item(ItemProperty().SetPlacerBlock("minecraft:bedrock")));
	mod->Subscribe("item_basic_block_placer_use_on", new Item(ItemProperty().SetPlacerBlock("minecraft:bedrock", std::vector<std::string>{"minecraft:grass", "minecraft:glass"})));
	mod->Subscribe("item_basic_can_destroy_in_creative", new Item(ItemProperty().SetCanDestroyInCreative(false)));
	mod->Subscribe("item_basic_cooldown", new Item(ItemProperty().SetCooldown("test", 10)));
	mod->Subscribe("item_basic_custom_components", new Item(ItemProperty().SetCustomComponents(std::vector<std::string>{ "adk-lib:custom_component", "adk-lib:custom_component_two" })));
	mod->Subscribe("item_basic_damage", new Item(ItemProperty().SetDamage(10)));
	mod->Subscribe("item_basic_display_name", new Item(ItemProperty().SetDisplayName("Custom Name")));
	mod->Subscribe("item_basic_digger_name", new Item(ItemProperty().SetDigger(digger_name)));
	mod->Subscribe("item_basic_digger_states", new Item(ItemProperty().SetDigger(digger_block_descriptor_states)));
	mod->Subscribe("item_basic_digger_tags", new Item(ItemProperty().SetDigger(digger_block_descriptor_tags)));
	mod->Subscribe("item_basic_durability", new Item(ItemProperty().SetDurability(durability)));
	mod->Subscribe("item_basic_durability_chance", new Item(ItemProperty().SetDurability(durability_chance)));
	mod->Subscribe("item_basic_enchantable", new Item(ItemProperty().SetEnchantable(EnchantableSlot::Sword, 255)));
	mod->Subscribe("item_basic_entity_placer", new Item(ItemProperty().SetPlacerEntity(entity_placer)));
	mod->Subscribe("item_basic_entity_placer_use_on", new Item(ItemProperty().SetPlacerEntity(entity_placer_use_on)));
	mod->Subscribe("item_basic_entity_placer_dispense_on", new Item(ItemProperty().SetPlacerEntity(entity_placer_dispense_on)));
	mod->Subscribe("item_basic_entity_placer_both", new Item(ItemProperty().SetPlacerEntity(entity_placer_both)));
	mod->Subscribe("item_basic_food_nutrition", new Item(ItemProperty().SetFood(food_nutrition)));
	mod->Subscribe("item_basic_food_can_always_eat", new Item(ItemProperty().SetFood(food_can_always_eat)));
	mod->Subscribe("item_basic_food_using_converts_to", new Item(ItemProperty().SetFood(food_using_converts_to)));
	mod->Subscribe("item_basic_food_saturation_modifier", new Item(ItemProperty().SetFood(food_saturation_modifier)));
	mod->Subscribe("item_basic_fuel", new Item(ItemProperty().SetFuel(0.05)));
	mod->Subscribe("item_basic_glint", new Item(ItemProperty().SetGlint(true)));
	mod->Subscribe("item_basic_hand_equipped", new Item(ItemProperty().SetHandEquipped(true)));
	mod->Subscribe("item_basic_hover_text_color", new Item(ItemProperty().SetHoverTextColor("green")));
	mod->Subscribe("item_basic_interact_button_bool", new Item(ItemProperty().SetInteractButton(false)));
	mod->Subscribe("item_basic_interact_button_string", new Item(ItemProperty().SetInteractButton(std::string("Interact with me!"))));
	mod->Subscribe("item_basic_liquid_clipped", new Item(ItemProperty().SetLiquidClipped(true)));
	mod->Subscribe("item_basic_max_stack_size", new Item(ItemProperty().SetMaxStackSize(32)));
	mod->Subscribe("item_basic_projectile", new Item(ItemProperty().SetProjectile("minecraft:arrow", 0.0)));
	mod->Subscribe("item_basic_record", new Item(ItemProperty().SetRecord(record)));
	mod->Subscribe("item_basic_record_comparator_signal", new Item(ItemProperty().SetRecord(record_comparator_signal)));
	mod->Subscribe("item_basic_record_duration", new Item(ItemProperty().SetRecord(record_duration)));
	mod->Subscribe("item_basic_repairable", new Item(ItemProperty().SetRepairable(repairable)));
	mod->Subscribe("item_basic_shooter_ammunition_item", new Item(ItemProperty().SetShooter(shooter_ammunition_item)));
	mod->Subscribe("item_basic_shooter_ammunition_search_inventory", new Item(ItemProperty().SetShooter(shooter_ammunition_search_inventory)));
	mod->Subscribe("item_basic_shooter_ammunition_use_in_creative", new Item(ItemProperty().SetShooter(shooter_ammunition_use_in_creative)));
	mod->Subscribe("item_basic_shooter_ammunition_use_offhand", new Item(ItemProperty().SetShooter(shooter_ammunition_use_offhand)));
	mod->Subscribe("item_basic_shooter_charge_on_draw", new Item(ItemProperty().SetShooter(shooter_charge_on_draw)));
	mod->Subscribe("item_basic_shooter_max_draw_duration", new Item(ItemProperty().SetShooter(shooter_max_draw_duration)));
	mod->Subscribe("item_basic_shooter_scale_power_by_draw_duration", new Item(ItemProperty().SetShooter(shooter_scale_power_by_draw_duration)));
	mod->Subscribe("item_basic_should_despawn", new Item(ItemProperty().SetShouldDespawn(false)));
	mod->Subscribe("item_basic_stacked_by_data", new Item(ItemProperty().SetStackedByData(true)));
	mod->Subscribe("item_basic_tags", new Item(ItemProperty().SetTags(std::vector<std::string>{"tag1", "tag2"})));
	mod->Subscribe("item_basic_throwable_do_swing_animation", new Item(ItemProperty().SetThrowable(throwable_do_swing_animation)));
	mod->Subscribe("item_basic_throwable_launch_power_scale", new Item(ItemProperty().SetThrowable(throwable_launch_power_scale)));
	mod->Subscribe("item_basic_throwable_max_draw_duration", new Item(ItemProperty().SetThrowable(throwable_max_draw_duration)));
	mod->Subscribe("item_basic_throwable_max_launch_power", new Item(ItemProperty().SetThrowable(throwable_max_launch_power)));
	mod->Subscribe("item_basic_throwable_min_draw_duration", new Item(ItemProperty().SetThrowable(throwable_min_draw_duration)));
	mod->Subscribe("item_basic_throwable_scale_power_by_draw_duration", new Item(ItemProperty().SetThrowable(throwable_scale_power_by_draw_duration)));
	mod->Subscribe("item_basic_use_animation", new Item(ItemProperty().SetUseAnimation("eat")));
	mod->Subscribe("item_basic_use_modifiers", new Item(ItemProperty().SetUseModifiers(1, 0.5)));
	mod->Subscribe("item_basic_wearable", new Item(ItemProperty().SetWearable(WearableSlot::ArmorChest, 10)));

	EXPECT_EQ(true, CompareFiles("./files/items/item_basic.json", "./BP/items/item_basic.json")) << "Item is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_allow_off_hand.json", "./BP/items/item_basic_allow_off_hand.json")) << "SetAllowOffhand is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_block_placer.json", "./BP/items/item_basic_block_placer.json")) << "SetBlockPlacer is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_block_placer_use_on.json", "./BP/items/item_basic_block_placer_use_on.json")) << "SetBlockPlacer (UseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_can_destroy_in_creative.json", "./BP/items/item_basic_can_destroy_in_creative.json")) << "SetCanDestoryInCreative is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_cooldown.json", "./BP/items/item_basic_cooldown.json")) << "SetCrafting is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_custom_components.json", "./BP/items/item_basic_custom_components.json")) << "SetCustomComponents is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_damage.json", "./BP/items/item_basic_damage.json")) << "SetDamage is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_digger_name.json", "./BP/items/item_basic_digger_name.json")) << "SetDigger (Name) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_digger_states.json", "./BP/items/item_basic_digger_states.json")) << "SetDigger (States) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_digger_tags.json", "./BP/items/item_basic_digger_tags.json")) << "SetDigger (Tags) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_display_name.json", "./BP/items/item_basic_display_name.json")) << "SetDisplayName is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_durability.json", "./BP/items/item_basic_durability.json")) << "SetDurability is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_durability_chance.json", "./BP/items/item_basic_durability_chance.json")) << "SetDurability (DamageChance) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_enchantable.json", "./BP/items/item_basic_enchantable.json")) << "SetEnchantable is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_entity_placer.json", "./BP/items/item_basic_entity_placer.json")) << "SetEntityPlacer is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_entity_placer_both.json", "./BP/items/item_basic_entity_placer_both.json")) << "SetEntityPlacer (Both) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_entity_placer_dispense_on.json", "./BP/items/item_basic_entity_placer_dispense_on.json")) << "SetEntityPlacer (DispenseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_entity_placer_use_on.json", "./BP/items/item_basic_entity_placer_use_on.json")) << "SetEntityPlacer (UseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_food_can_always_eat.json", "./BP/items/item_basic_food_can_always_eat.json")) << "SetFood (CanAlwaysEat) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_food_nutrition.json", "./BP/items/item_basic_food_nutrition.json")) << "SetFood (Nurtition) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_food_saturation_modifier.json", "./BP/items/item_basic_food_saturation_modifier.json")) << "SetFood (SaturationModifier) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_food_using_converts_to.json", "./BP/items/item_basic_food_using_converts_to.json")) << "SetFood (UsingConvertsTo) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_fuel.json", "./BP/items/item_basic_fuel.json")) << "SetFuel is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_glint.json", "./BP/items/item_basic_glint.json")) << "SetGlint is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_hand_equipped.json", "./BP/items/item_basic_hand_equipped.json")) << "SetHandEquipped is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_hover_text_color.json", "./BP/items/item_basic_hover_text_color.json")) << "SetHoverTextColor is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_interact_button_bool.json", "./BP/items/item_basic_interact_button_bool.json")) << "SetInteractButton (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_interact_button_string.json", "./BP/items/item_basic_interact_button_string.json")) << "SetInteractButton (string) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_liquid_clipped.json", "./BP/items/item_basic_liquid_clipped.json")) << "SetLiquidClipped is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_max_stack_size.json", "./BP/items/item_basic_max_stack_size.json")) << "SetMaxStackSize is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_projectile.json", "./BP/items/item_basic_projectile.json")) << "SetProjectile is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_record.json", "./BP/items/item_basic_record.json")) << "SetRecord is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_record_comparator_signal.json", "./BP/items/item_basic_record_comparator_signal.json")) << "SetRecord (ComparatorSignal) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_record_duration.json", "./BP/items/item_basic_record_duration.json")) << "SetRecord (Duration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_repairable.json", "./BP/items/item_basic_repairable.json")) << "SetRepairable is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_shooter_ammunition_item.json", "./BP/items/item_basic_shooter_ammunition_item.json")) << "SetShooter (Ammunition) (Item) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_shooter_ammunition_search_inventory.json", "./BP/items/item_basic_shooter_ammunition_search_inventory.json")) << "SetShooter (Ammunition) (SearchInventory)is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_shooter_ammunition_use_in_creative.json", "./BP/items/item_basic_shooter_ammunition_use_in_creative.json")) << "SetShooter (Ammunition) (UseInCreative)is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_shooter_ammunition_use_offhand.json", "./BP/items/item_basic_shooter_ammunition_use_offhand.json")) << "SetShooter (Ammunition) (UseOffhand) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_shooter_charge_on_draw.json", "./BP/items/item_basic_shooter_charge_on_draw.json")) << "SetShooter (ChargeOnDraw) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_shooter_max_draw_duration.json", "./BP/items/item_basic_shooter_max_draw_duration.json")) << "SetShooter (MaxDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_shooter_scale_power_by_draw_duration.json", "./BP/items/item_basic_shooter_scale_power_by_draw_duration.json")) << "SetShooter (ScalePowerByDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_should_despawn.json", "./BP/items/item_basic_should_despawn.json")) << "SetShouldDespawn is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_stacked_by_data.json", "./BP/items/item_basic_stacked_by_data.json")) << "SetStackedByData is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_tags.json", "./BP/items/item_basic_tags.json")) << "SetTags is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_throwable_do_swing_animation.json", "./BP/items/item_basic_throwable_do_swing_animation.json")) << "SetThrowable (DoSwingAnimation) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_throwable_launch_power_scale.json", "./BP/items/item_basic_throwable_launch_power_scale.json")) << "SetThrowable (LaunchPowerScale) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_throwable_max_draw_duration.json", "./BP/items/item_basic_throwable_max_draw_duration.json")) << "SetThrowable (MaxDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_throwable_max_launch_power.json", "./BP/items/item_basic_throwable_max_launch_power.json")) << "SetThrowable (MaxLaunchPower) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_throwable_min_draw_duration.json", "./BP/items/item_basic_throwable_min_draw_duration.json")) << "SetThrowable (MinDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_throwable_scale_power_by_draw_duration.json", "./BP/items/item_basic_throwable_scale_power_by_draw_duration.json")) << "SetThrowable (ScalePowerByDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_use_animation.json", "./BP/items/item_basic_use_animation.json")) << "SetUseAnimation is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_use_modifiers.json", "./BP/items/item_basic_use_modifiers.json")) << "SetUseModifiers is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_basic_wearable.json", "./BP/items/item_basic_wearable.json")) << "SetWearable is not working as expected";
}

TEST(ItemTest, ItemArmor) {
	std::filesystem::create_directory("BP");
	std::filesystem::create_directory("RP");

	SetupCommon();

	log::info("Starting Item Armor Test");

	mod->Subscribe("item_armor", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty()));
	mod->Subscribe("item_armor_allow_off_hand", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetAllowOffHand(true)));
	mod->Subscribe("item_armor_block_placer", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetPlacerBlock("minecraft:bedrock")));
	mod->Subscribe("item_armor_block_placer_use_on", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetPlacerBlock("minecraft:bedrock", std::vector<std::string>{"minecraft:grass", "minecraft:glass"})));
	mod->Subscribe("item_armor_can_destroy_in_creative", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetCanDestroyInCreative(false)));
	mod->Subscribe("item_armor_cooldown", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetCooldown("test", 10)));
	mod->Subscribe("item_armor_custom_components", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetCustomComponents(std::vector<std::string>{ "adk-lib:custom_component", "adk-lib:custom_component_two" })));
	mod->Subscribe("item_armor_damage", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetDamage(10)));
	mod->Subscribe("item_armor_display_name", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetDisplayName("Custom Name")));
	mod->Subscribe("item_armor_digger_name", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetDigger(digger_name)));
	mod->Subscribe("item_armor_digger_states", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetDigger(digger_block_descriptor_states)));
	mod->Subscribe("item_armor_digger_tags", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetDigger(digger_block_descriptor_tags)));
	mod->Subscribe("item_armor_durability", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetDurability(durability)));
	mod->Subscribe("item_armor_durability_chance", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetDurability(durability_chance)));
	mod->Subscribe("item_armor_enchantable", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetEnchantable(EnchantableSlot::Sword, 255)));
	mod->Subscribe("item_armor_entity_placer", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetPlacerEntity(entity_placer)));
	mod->Subscribe("item_armor_entity_placer_use_on", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetPlacerEntity(entity_placer_use_on)));
	mod->Subscribe("item_armor_entity_placer_dispense_on", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetPlacerEntity(entity_placer_dispense_on)));
	mod->Subscribe("item_armor_entity_placer_both", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetPlacerEntity(entity_placer_both)));
	mod->Subscribe("item_armor_food_nutrition", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetFood(food_nutrition)));
	mod->Subscribe("item_armor_food_can_always_eat", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetFood(food_can_always_eat)));
	mod->Subscribe("item_armor_food_using_converts_to", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetFood(food_using_converts_to)));
	mod->Subscribe("item_armor_food_saturation_modifier", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetFood(food_saturation_modifier)));
	mod->Subscribe("item_armor_fuel", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetFuel(0.05)));
	mod->Subscribe("item_armor_glint", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetGlint(true)));
	mod->Subscribe("item_armor_hand_equipped", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetHandEquipped(true)));
	mod->Subscribe("item_armor_hover_text_color", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetHoverTextColor("green")));
	mod->Subscribe("item_armor_interact_button_bool", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetInteractButton(false)));
	mod->Subscribe("item_armor_interact_button_string", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetInteractButton(std::string("Interact with me!"))));
	mod->Subscribe("item_armor_liquid_clipped", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetLiquidClipped(true)));
	mod->Subscribe("item_armor_max_stack_size", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetMaxStackSize(32)));
	mod->Subscribe("item_armor_projectile", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetProjectile("minecraft:arrow", 0.0)));
	mod->Subscribe("item_armor_record", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetRecord(record)));
	mod->Subscribe("item_armor_record_comparator_signal", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetRecord(record_comparator_signal)));
	mod->Subscribe("item_armor_record_duration", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetRecord(record_duration)));
	mod->Subscribe("item_armor_repairable", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetRepairable(repairable)));
	mod->Subscribe("item_armor_shooter_ammunition_item", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetShooter(shooter_ammunition_item)));
	mod->Subscribe("item_armor_shooter_ammunition_search_inventory", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetShooter(shooter_ammunition_search_inventory)));
	mod->Subscribe("item_armor_shooter_ammunition_use_in_creative", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetShooter(shooter_ammunition_use_in_creative)));
	mod->Subscribe("item_armor_shooter_ammunition_use_offhand", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetShooter(shooter_ammunition_use_offhand)));
	mod->Subscribe("item_armor_shooter_charge_on_draw", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetShooter(shooter_charge_on_draw)));
	mod->Subscribe("item_armor_shooter_max_draw_duration", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetShooter(shooter_max_draw_duration)));
	mod->Subscribe("item_armor_shooter_scale_power_by_draw_duration", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetShooter(shooter_scale_power_by_draw_duration)));
	mod->Subscribe("item_armor_should_despawn", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetShouldDespawn(false)));
	mod->Subscribe("item_armor_stacked_by_data", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetStackedByData(true)));
	mod->Subscribe("item_armor_tags", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetTags(std::vector<std::string>{"tag1", "tag2"})));
	mod->Subscribe("item_armor_throwable_do_swing_animation", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetThrowable(throwable_do_swing_animation)));
	mod->Subscribe("item_armor_throwable_launch_power_scale", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetThrowable(throwable_launch_power_scale)));
	mod->Subscribe("item_armor_throwable_max_draw_duration", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetThrowable(throwable_max_draw_duration)));
	mod->Subscribe("item_armor_throwable_max_launch_power", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetThrowable(throwable_max_launch_power)));
	mod->Subscribe("item_armor_throwable_min_draw_duration", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetThrowable(throwable_min_draw_duration)));
	mod->Subscribe("item_armor_throwable_scale_power_by_draw_duration", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetThrowable(throwable_scale_power_by_draw_duration)));
	mod->Subscribe("item_armor_use_animation", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetUseAnimation("eat")));
	mod->Subscribe("item_armor_use_modifiers", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetUseModifiers(1, 0.5)));
	mod->Subscribe("item_armor_wearable", new ItemArmor(&ArmorMaterials::Leather, WearableSlot::ArmorHead, ItemProperty().SetWearable(WearableSlot::ArmorChest, 10)));

	EXPECT_EQ(true, CompareFiles("./files/items/item_armor.json", "./BP/items/item_armor.json")) << "Item Armor is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_allow_off_hand.json", "./BP/items/item_armor_allow_off_hand.json")) << "SetAllowOffhand is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_block_placer.json", "./BP/items/item_armor_block_placer.json")) << "SetBlockPlacer is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_block_placer_use_on.json", "./BP/items/item_armor_block_placer_use_on.json")) << "SetBlockPlacer (UseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_can_destroy_in_creative.json", "./BP/items/item_armor_can_destroy_in_creative.json")) << "SetCanDestoryInCreative is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_cooldown.json", "./BP/items/item_armor_cooldown.json")) << "SetCrafting is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_custom_components.json", "./BP/items/item_armor_custom_components.json")) << "SetCustomComponents is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_damage.json", "./BP/items/item_armor_damage.json")) << "SetDamage is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_digger_name.json", "./BP/items/item_armor_digger_name.json")) << "SetDigger (Name) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_digger_states.json", "./BP/items/item_armor_digger_states.json")) << "SetDigger (States) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_digger_tags.json", "./BP/items/item_armor_digger_tags.json")) << "SetDigger (Tags) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_display_name.json", "./BP/items/item_armor_display_name.json")) << "SetDisplayName is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_durability.json", "./BP/items/item_armor_durability.json")) << "SetDurability is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_durability_chance.json", "./BP/items/item_armor_durability_chance.json")) << "SetDurability (DamageChance) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_enchantable.json", "./BP/items/item_armor_enchantable.json")) << "SetEnchantable is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_entity_placer.json", "./BP/items/item_armor_entity_placer.json")) << "SetEntityPlacer is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_entity_placer_both.json", "./BP/items/item_armor_entity_placer_both.json")) << "SetEntityPlacer (Both) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_entity_placer_dispense_on.json", "./BP/items/item_armor_entity_placer_dispense_on.json")) << "SetEntityPlacer (DispenseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_entity_placer_use_on.json", "./BP/items/item_armor_entity_placer_use_on.json")) << "SetEntityPlacer (UseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_food_can_always_eat.json", "./BP/items/item_armor_food_can_always_eat.json")) << "SetFood (CanAlwaysEat) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_food_nutrition.json", "./BP/items/item_armor_food_nutrition.json")) << "SetFood (Nurtition) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_food_saturation_modifier.json", "./BP/items/item_armor_food_saturation_modifier.json")) << "SetFood (SaturationModifier) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_food_using_converts_to.json", "./BP/items/item_armor_food_using_converts_to.json")) << "SetFood (UsingConvertsTo) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_fuel.json", "./BP/items/item_armor_fuel.json")) << "SetFuel is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_glint.json", "./BP/items/item_armor_glint.json")) << "SetGlint is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_hand_equipped.json", "./BP/items/item_armor_hand_equipped.json")) << "SetHandEquipped is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_hover_text_color.json", "./BP/items/item_armor_hover_text_color.json")) << "SetHoverTextColor is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_interact_button_bool.json", "./BP/items/item_armor_interact_button_bool.json")) << "SetInteractButton (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_interact_button_string.json", "./BP/items/item_armor_interact_button_string.json")) << "SetInteractButton (string) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_liquid_clipped.json", "./BP/items/item_armor_liquid_clipped.json")) << "SetLiquidClipped is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_max_stack_size.json", "./BP/items/item_armor_max_stack_size.json")) << "SetMaxStackSize is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_projectile.json", "./BP/items/item_armor_projectile.json")) << "SetProjectile is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_record.json", "./BP/items/item_armor_record.json")) << "SetRecord is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_record_comparator_signal.json", "./BP/items/item_armor_record_comparator_signal.json")) << "SetRecord (ComparatorSignal) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_record_duration.json", "./BP/items/item_armor_record_duration.json")) << "SetRecord (Duration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_repairable.json", "./BP/items/item_armor_repairable.json")) << "SetRepairable is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_shooter_ammunition_item.json", "./BP/items/item_armor_shooter_ammunition_item.json")) << "SetShooter (Ammunition) (Item) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_shooter_ammunition_search_inventory.json", "./BP/items/item_armor_shooter_ammunition_search_inventory.json")) << "SetShooter (Ammunition) (SearchInventory)is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_shooter_ammunition_use_in_creative.json", "./BP/items/item_armor_shooter_ammunition_use_in_creative.json")) << "SetShooter (Ammunition) (UseInCreative)is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_shooter_ammunition_use_offhand.json", "./BP/items/item_armor_shooter_ammunition_use_offhand.json")) << "SetShooter (Ammunition) (UseOffhand) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_shooter_charge_on_draw.json", "./BP/items/item_armor_shooter_charge_on_draw.json")) << "SetShooter (ChargeOnDraw) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_shooter_max_draw_duration.json", "./BP/items/item_armor_shooter_max_draw_duration.json")) << "SetShooter (MaxDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_shooter_scale_power_by_draw_duration.json", "./BP/items/item_armor_shooter_scale_power_by_draw_duration.json")) << "SetShooter (ScalePowerByDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_should_despawn.json", "./BP/items/item_armor_should_despawn.json")) << "SetShouldDespawn is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stacked_by_data.json", "./BP/items/item_armor_stacked_by_data.json")) << "SetStackedByData is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_tags.json", "./BP/items/item_armor_tags.json")) << "SetTags is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_throwable_do_swing_animation.json", "./BP/items/item_armor_throwable_do_swing_animation.json")) << "SetThrowable (DoSwingAnimation) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_throwable_launch_power_scale.json", "./BP/items/item_armor_throwable_launch_power_scale.json")) << "SetThrowable (LaunchPowerScale) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_throwable_max_draw_duration.json", "./BP/items/item_armor_throwable_max_draw_duration.json")) << "SetThrowable (MaxDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_throwable_max_launch_power.json", "./BP/items/item_armor_throwable_max_launch_power.json")) << "SetThrowable (MaxLaunchPower) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_throwable_min_draw_duration.json", "./BP/items/item_armor_throwable_min_draw_duration.json")) << "SetThrowable (MinDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_throwable_scale_power_by_draw_duration.json", "./BP/items/item_armor_throwable_scale_power_by_draw_duration.json")) << "SetThrowable (ScalePowerByDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_use_animation.json", "./BP/items/item_armor_use_animation.json")) << "SetUseAnimation is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_use_modifiers.json", "./BP/items/item_armor_use_modifiers.json")) << "SetUseModifiers is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_wearable.json", "./BP/items/item_armor_wearable.json")) << "SetWearable is not working as expected";
}

TEST(ItemTest, ItemArmorStand) {
	std::filesystem::create_directory("BP");
	std::filesystem::create_directory("RP");

	SetupCommon();

	log::info("Starting Item Armor Stand Test");

	mod->Subscribe("item_armor_stand", new ItemArmorStand(ItemProperty()));
	mod->Subscribe("item_armor_stand_allow_off_hand", new ItemArmorStand(ItemProperty().SetAllowOffHand(true)));
	mod->Subscribe("item_armor_stand_block_placer", new ItemArmorStand(ItemProperty().SetPlacerBlock("minecraft:bedrock")));
	mod->Subscribe("item_armor_stand_block_placer_use_on", new ItemArmorStand(ItemProperty().SetPlacerBlock("minecraft:bedrock", std::vector<std::string>{"minecraft:grass", "minecraft:glass"})));
	mod->Subscribe("item_armor_stand_can_destroy_in_creative", new ItemArmorStand(ItemProperty().SetCanDestroyInCreative(false)));
	mod->Subscribe("item_armor_stand_cooldown", new ItemArmorStand(ItemProperty().SetCooldown("test", 10)));
	mod->Subscribe("item_armor_stand_custom_components", new ItemArmorStand(ItemProperty().SetCustomComponents(std::vector<std::string>{ "adk-lib:custom_component", "adk-lib:custom_component_two" })));
	mod->Subscribe("item_armor_stand_damage", new ItemArmorStand(ItemProperty().SetDamage(10)));
	mod->Subscribe("item_armor_stand_display_name", new ItemArmorStand(ItemProperty().SetDisplayName("Custom Name")));
	mod->Subscribe("item_armor_stand_digger_name", new ItemArmorStand(ItemProperty().SetDigger(digger_name)));
	mod->Subscribe("item_armor_stand_digger_states", new ItemArmorStand(ItemProperty().SetDigger(digger_block_descriptor_states)));
	mod->Subscribe("item_armor_stand_digger_tags", new ItemArmorStand(ItemProperty().SetDigger(digger_block_descriptor_tags)));
	mod->Subscribe("item_armor_stand_durability", new ItemArmorStand(ItemProperty().SetDurability(durability)));
	mod->Subscribe("item_armor_stand_durability_chance", new ItemArmorStand(ItemProperty().SetDurability(durability_chance)));
	mod->Subscribe("item_armor_stand_enchantable", new ItemArmorStand(ItemProperty().SetEnchantable(EnchantableSlot::Sword, 255)));
	mod->Subscribe("item_armor_stand_entity_placer", new ItemArmorStand(ItemProperty().SetPlacerEntity(entity_placer)));
	mod->Subscribe("item_armor_stand_entity_placer_use_on", new ItemArmorStand(ItemProperty().SetPlacerEntity(entity_placer_use_on)));
	mod->Subscribe("item_armor_stand_entity_placer_dispense_on", new ItemArmorStand(ItemProperty().SetPlacerEntity(entity_placer_dispense_on)));
	mod->Subscribe("item_armor_stand_entity_placer_both", new ItemArmorStand(ItemProperty().SetPlacerEntity(entity_placer_both)));
	mod->Subscribe("item_armor_stand_food_nutrition", new ItemArmorStand(ItemProperty().SetFood(food_nutrition)));
	mod->Subscribe("item_armor_stand_food_can_always_eat", new ItemArmorStand(ItemProperty().SetFood(food_can_always_eat)));
	mod->Subscribe("item_armor_stand_food_using_converts_to", new ItemArmorStand(ItemProperty().SetFood(food_using_converts_to)));
	mod->Subscribe("item_armor_stand_food_saturation_modifier", new ItemArmorStand(ItemProperty().SetFood(food_saturation_modifier)));
	mod->Subscribe("item_armor_stand_fuel", new ItemArmorStand(ItemProperty().SetFuel(0.05)));
	mod->Subscribe("item_armor_stand_glint", new ItemArmorStand(ItemProperty().SetGlint(true)));
	mod->Subscribe("item_armor_stand_hand_equipped", new ItemArmorStand(ItemProperty().SetHandEquipped(true)));
	mod->Subscribe("item_armor_stand_hover_text_color", new ItemArmorStand(ItemProperty().SetHoverTextColor("green")));
	mod->Subscribe("item_armor_stand_interact_button_bool", new ItemArmorStand(ItemProperty().SetInteractButton(false)));
	mod->Subscribe("item_armor_stand_interact_button_string", new ItemArmorStand(ItemProperty().SetInteractButton(std::string("Interact with me!"))));
	mod->Subscribe("item_armor_stand_liquid_clipped", new ItemArmorStand(ItemProperty().SetLiquidClipped(true)));
	mod->Subscribe("item_armor_stand_max_stack_size", new ItemArmorStand(ItemProperty().SetMaxStackSize(32)));
	mod->Subscribe("item_armor_stand_projectile", new ItemArmorStand(ItemProperty().SetProjectile("minecraft:arrow", 0.0)));
	mod->Subscribe("item_armor_stand_record", new ItemArmorStand(ItemProperty().SetRecord(record)));
	mod->Subscribe("item_armor_stand_record_comparator_signal", new ItemArmorStand(ItemProperty().SetRecord(record_comparator_signal)));
	mod->Subscribe("item_armor_stand_record_duration", new ItemArmorStand(ItemProperty().SetRecord(record_duration)));
	mod->Subscribe("item_armor_stand_repairable", new ItemArmorStand(ItemProperty().SetRepairable(repairable)));
	mod->Subscribe("item_armor_stand_shooter_ammunition_item", new ItemArmorStand(ItemProperty().SetShooter(shooter_ammunition_item)));
	mod->Subscribe("item_armor_stand_shooter_ammunition_search_inventory", new ItemArmorStand(ItemProperty().SetShooter(shooter_ammunition_search_inventory)));
	mod->Subscribe("item_armor_stand_shooter_ammunition_use_in_creative", new ItemArmorStand(ItemProperty().SetShooter(shooter_ammunition_use_in_creative)));
	mod->Subscribe("item_armor_stand_shooter_ammunition_use_offhand", new ItemArmorStand(ItemProperty().SetShooter(shooter_ammunition_use_offhand)));
	mod->Subscribe("item_armor_stand_shooter_charge_on_draw", new ItemArmorStand(ItemProperty().SetShooter(shooter_charge_on_draw)));
	mod->Subscribe("item_armor_stand_shooter_max_draw_duration", new ItemArmorStand(ItemProperty().SetShooter(shooter_max_draw_duration)));
	mod->Subscribe("item_armor_stand_shooter_scale_power_by_draw_duration", new ItemArmorStand(ItemProperty().SetShooter(shooter_scale_power_by_draw_duration)));
	mod->Subscribe("item_armor_stand_should_despawn", new ItemArmorStand(ItemProperty().SetShouldDespawn(false)));
	mod->Subscribe("item_armor_stand_stacked_by_data", new ItemArmorStand(ItemProperty().SetStackedByData(true)));
	mod->Subscribe("item_armor_stand_tags", new ItemArmorStand(ItemProperty().SetTags(std::vector<std::string>{"tag1", "tag2"})));
	mod->Subscribe("item_armor_stand_throwable_do_swing_animation", new ItemArmorStand(ItemProperty().SetThrowable(throwable_do_swing_animation)));
	mod->Subscribe("item_armor_stand_throwable_launch_power_scale", new ItemArmorStand(ItemProperty().SetThrowable(throwable_launch_power_scale)));
	mod->Subscribe("item_armor_stand_throwable_max_draw_duration", new ItemArmorStand(ItemProperty().SetThrowable(throwable_max_draw_duration)));
	mod->Subscribe("item_armor_stand_throwable_max_launch_power", new ItemArmorStand(ItemProperty().SetThrowable(throwable_max_launch_power)));
	mod->Subscribe("item_armor_stand_throwable_min_draw_duration", new ItemArmorStand(ItemProperty().SetThrowable(throwable_min_draw_duration)));
	mod->Subscribe("item_armor_stand_throwable_scale_power_by_draw_duration", new ItemArmorStand(ItemProperty().SetThrowable(throwable_scale_power_by_draw_duration)));
	mod->Subscribe("item_armor_stand_use_animation", new ItemArmorStand(ItemProperty().SetUseAnimation("eat")));
	mod->Subscribe("item_armor_stand_use_modifiers", new ItemArmorStand(ItemProperty().SetUseModifiers(1, 0.5)));
	mod->Subscribe("item_armor_stand_wearable", new ItemArmorStand(ItemProperty().SetWearable(WearableSlot::ArmorChest, 10)));

	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand.json", "./BP/items/item_armor_stand.json")) << "Item is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_allow_off_hand.json", "./BP/items/item_armor_stand_allow_off_hand.json")) << "SetAllowOffhand is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_block_placer.json", "./BP/items/item_armor_stand_block_placer.json")) << "SetBlockPlacer is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_block_placer_use_on.json", "./BP/items/item_armor_stand_block_placer_use_on.json")) << "SetBlockPlacer (UseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_can_destroy_in_creative.json", "./BP/items/item_armor_stand_can_destroy_in_creative.json")) << "SetCanDestoryInCreative is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_cooldown.json", "./BP/items/item_armor_stand_cooldown.json")) << "SetCrafting is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_custom_components.json", "./BP/items/item_armor_stand_custom_components.json")) << "SetCustomComponents is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_damage.json", "./BP/items/item_armor_stand_damage.json")) << "SetDamage is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_digger_name.json", "./BP/items/item_armor_stand_digger_name.json")) << "SetDigger (Name) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_digger_states.json", "./BP/items/item_armor_stand_digger_states.json")) << "SetDigger (States) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_digger_tags.json", "./BP/items/item_armor_stand_digger_tags.json")) << "SetDigger (Tags) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_display_name.json", "./BP/items/item_armor_stand_display_name.json")) << "SetDisplayName is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_durability.json", "./BP/items/item_armor_stand_durability.json")) << "SetDurability is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_durability_chance.json", "./BP/items/item_armor_stand_durability_chance.json")) << "SetDurability (DamageChance) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_enchantable.json", "./BP/items/item_armor_stand_enchantable.json")) << "SetEnchantable is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_entity_placer.json", "./BP/items/item_armor_stand_entity_placer.json")) << "SetEntityPlacer is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_entity_placer_both.json", "./BP/items/item_armor_stand_entity_placer_both.json")) << "SetEntityPlacer (Both) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_entity_placer_dispense_on.json", "./BP/items/item_armor_stand_entity_placer_dispense_on.json")) << "SetEntityPlacer (DispenseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_entity_placer_use_on.json", "./BP/items/item_armor_stand_entity_placer_use_on.json")) << "SetEntityPlacer (UseOn) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_food_can_always_eat.json", "./BP/items/item_armor_stand_food_can_always_eat.json")) << "SetFood (CanAlwaysEat) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_food_nutrition.json", "./BP/items/item_armor_stand_food_nutrition.json")) << "SetFood (Nurtition) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_food_saturation_modifier.json", "./BP/items/item_armor_stand_food_saturation_modifier.json")) << "SetFood (SaturationModifier) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_food_using_converts_to.json", "./BP/items/item_armor_stand_food_using_converts_to.json")) << "SetFood (UsingConvertsTo) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_fuel.json", "./BP/items/item_armor_stand_fuel.json")) << "SetFuel is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_glint.json", "./BP/items/item_armor_stand_glint.json")) << "SetGlint is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_hand_equipped.json", "./BP/items/item_armor_stand_hand_equipped.json")) << "SetHandEquipped is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_hover_text_color.json", "./BP/items/item_armor_stand_hover_text_color.json")) << "SetHoverTextColor is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_interact_button_bool.json", "./BP/items/item_armor_stand_interact_button_bool.json")) << "SetInteractButton (bool) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_interact_button_string.json", "./BP/items/item_armor_stand_interact_button_string.json")) << "SetInteractButton (string) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_liquid_clipped.json", "./BP/items/item_armor_stand_liquid_clipped.json")) << "SetLiquidClipped is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_max_stack_size.json", "./BP/items/item_armor_stand_max_stack_size.json")) << "SetMaxStackSize is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_projectile.json", "./BP/items/item_armor_stand_projectile.json")) << "SetProjectile is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_record.json", "./BP/items/item_armor_stand_record.json")) << "SetRecord is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_record_comparator_signal.json", "./BP/items/item_armor_stand_record_comparator_signal.json")) << "SetRecord (ComparatorSignal) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_record_duration.json", "./BP/items/item_armor_stand_record_duration.json")) << "SetRecord (Duration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_repairable.json", "./BP/items/item_armor_stand_repairable.json")) << "SetRepairable is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_shooter_ammunition_item.json", "./BP/items/item_armor_stand_shooter_ammunition_item.json")) << "SetShooter (Ammunition) (Item) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_shooter_ammunition_search_inventory.json", "./BP/items/item_armor_stand_shooter_ammunition_search_inventory.json")) << "SetShooter (Ammunition) (SearchInventory)is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_shooter_ammunition_use_in_creative.json", "./BP/items/item_armor_stand_shooter_ammunition_use_in_creative.json")) << "SetShooter (Ammunition) (UseInCreative)is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_shooter_ammunition_use_offhand.json", "./BP/items/item_armor_stand_shooter_ammunition_use_offhand.json")) << "SetShooter (Ammunition) (UseOffhand) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_shooter_charge_on_draw.json", "./BP/items/item_armor_stand_shooter_charge_on_draw.json")) << "SetShooter (ChargeOnDraw) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_shooter_max_draw_duration.json", "./BP/items/item_armor_stand_shooter_max_draw_duration.json")) << "SetShooter (MaxDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_shooter_scale_power_by_draw_duration.json", "./BP/items/item_armor_stand_shooter_scale_power_by_draw_duration.json")) << "SetShooter (ScalePowerByDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_should_despawn.json", "./BP/items/item_armor_stand_should_despawn.json")) << "SetShouldDespawn is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_stacked_by_data.json", "./BP/items/item_armor_stand_stacked_by_data.json")) << "SetStackedByData is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_tags.json", "./BP/items/item_armor_stand_tags.json")) << "SetTags is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_throwable_do_swing_animation.json", "./BP/items/item_armor_stand_throwable_do_swing_animation.json")) << "SetThrowable (DoSwingAnimation) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_throwable_launch_power_scale.json", "./BP/items/item_armor_stand_throwable_launch_power_scale.json")) << "SetThrowable (LaunchPowerScale) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_throwable_max_draw_duration.json", "./BP/items/item_armor_stand_throwable_max_draw_duration.json")) << "SetThrowable (MaxDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_throwable_max_launch_power.json", "./BP/items/item_armor_stand_throwable_max_launch_power.json")) << "SetThrowable (MaxLaunchPower) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_throwable_min_draw_duration.json", "./BP/items/item_armor_stand_throwable_min_draw_duration.json")) << "SetThrowable (MinDrawDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_throwable_scale_power_by_draw_duration.json", "./BP/items/item_armor_stand_throwable_scale_power_by_draw_duration.json")) << "SetThrowable (ScalePowerByDuration) is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_use_animation.json", "./BP/items/item_armor_stand_use_animation.json")) << "SetUseAnimation is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_use_modifiers.json", "./BP/items/item_armor_stand_use_modifiers.json")) << "SetUseModifiers is not working as expected";
	EXPECT_EQ(true, CompareFiles("./files/items/item_armor_stand_wearable.json", "./BP/items/item_armor_stand_wearable.json")) << "SetWearable is not working as expected";
}
