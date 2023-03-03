#include <gtest/gtest.h>
#include <spdlog/async.h>

#include "BlockTest.cpp"

int main(int argc, char **argv) {
    auto logger = spdlog::basic_logger_mt<spdlog::async_factory>(
        "adk", "logs/async_log.txt");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}