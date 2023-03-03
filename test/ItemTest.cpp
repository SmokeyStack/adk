#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "../adk/data/include/Item.h"
#include "../adk/data/include/ItemProperty.h"
#include "../adk/data/include/Registry.h"
#include "../adk/data/include/ShapedRecipeBuilder.h"
#include "../adk/data/include/ShapelessRecipeBuilder.h"
#include "../adk/data/include/ToolItem.h"
#include "CheckFile.h"

namespace fs = std::filesystem;

TEST(ItemTest, BasicItem) {
    const std::string MODID = "custom_namespace";
    Registry<Item> mod(MODID);

    mod.subscribe("basic_item", new Item(ItemProperty::Property()));

    bool basic = compareFiles("../../test/files/basic_item.json",
                              "./BP/items/basic_item.json");

    ShapelessRecipeBuilder()
        .shapeless("honeycomb_bricks", 4)
        .requires("solidified_honey")
        .save("honeycomb_bricks_recipe");

    ShapedRecipeBuilder()
        .shaped(mod, "basic_item")
        .pattern("ppp")
        .define('p', "uwu")
        .save("test");

    EXPECT_EQ(true, false) << "Item is not working as expected";
}

TEST(ItemTest, ToolItem) {
    const std::string MODID = "custom_namespace";
    Registry<Item> mod(MODID);

    auto list_of_blocks = std::multimap<int, std::string>{};
    list_of_blocks.insert(std::make_pair(5, "grass"));
    list_of_blocks.insert(std::make_pair(5, "dirt"));
    list_of_blocks.insert(std::make_pair(10, "obsidian"));
    list_of_blocks.insert(std::make_pair(5, "sand"));
    list_of_blocks.insert(std::make_pair(4, "log"));

    mod.subscribe("basic_tool", new ToolItem(ItemProperty::Property(), 100, 100,
                                             100, list_of_blocks));

    bool basic = compareFiles("../../test/files/basic_tool.json",
                              "./BP/items/basic_tool.json");

    EXPECT_EQ(true, basic) << "ToolItem is not working as expected";
}