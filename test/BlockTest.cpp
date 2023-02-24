#include <gtest/gtest.h>

#include <filesystem>

#include "CheckFile.h"

namespace fs = std::filesystem;

TEST(BlockTest, BasicBlock) {
    if (!fs::exists("../../test/files/basic_block.json")) std::cout << "Whaaa";

    bool check = compareFiles("../../test/files/basic_block.json",
                              "../../test/files/basic_block.json");
    EXPECT_EQ(true, check);
}