#include <gtest/gtest.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <string>
#include <vector>

#include "../adk/data/include/GlobalRegistry.h"
#include "../adk/data/include/Item.h"
#include "../adk/data/include/ItemProperty.h"
#include "../adk/data/include/Registry.h"
#include "CheckFile.h"

namespace fs = std::filesystem;

TEST(ItemTest, BasicItem) {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    console_sink->set_level(spdlog::level::err);

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "logs/log.txt", true);
    file_sink->set_level(spdlog::level::info);

    spdlog::sinks_init_list sink_list = {file_sink, console_sink};

    auto object_logger = std::make_shared<spdlog::logger>(
        "Blocks/Items", sink_list.begin(), sink_list.end());
    auto data_logger = std::make_shared<spdlog::logger>(
        "Data Generator", sink_list.begin(), sink_list.end());
    auto recipe_logger = std::make_shared<spdlog::logger>(
        "Recipe", sink_list.begin(), sink_list.end());

    spdlog::register_logger(object_logger);
    spdlog::register_logger(data_logger);
    spdlog::register_logger(recipe_logger);

    const std::string MODID = "custom_namespace";
    Registry<Item>* mod = new Registry<Item>(MODID);

    globalregistry.push_back(mod);

    mod->subscribe("basic_item", new Item(ItemProperty()));

    bool basic = compareFiles("../../test/files/basic_item.json",
                              "./BP/items/basic_item.json");

    EXPECT_EQ(true, basic) << "Item is not working as expected";
}