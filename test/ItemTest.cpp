#include <gtest/gtest.h>

#include <filesystem>
#include <string>
#include <vector>

#include "../adk/data/include/Item.h"
#include "../adk/data/include/ItemProperty.h"
#include "../adk/data/include/Registry.h"
#include "CheckFile.h"

namespace fs = std::filesystem;

TEST(ItemTest, BasicItem) {
    const std::string MODID = "custom_namespace";
    Registry<Item> mod(MODID);

    mod.subscribe("basic_item", new Item(ItemProperty()));

    bool basic = compareFiles("../../test/files/basic_item.json",
                              "./BP/items/basic_item.json");

    EXPECT_EQ(true, basic) << "Item is not working as expected";
}