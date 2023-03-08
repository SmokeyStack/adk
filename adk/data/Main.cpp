#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include "Data.h"
#include "Object.h"
#include "Recipe.h"

int main() {
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

    Object MyAddOn("custom_namespace");
    Data DataGenerator;
    Recipe RecipeGenerator;

    MyAddOn.init();
    DataGenerator.init();
    RecipeGenerator.init();

    return 0;
}