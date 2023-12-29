#include "Data.h"
#include "Object.h"
#include "Recipe.h"
#include "utility/logger.h"

int main() {
    adk::SetupLoggerStage1();

    auto console_log_level = adk::Level::Info;
    auto file_log_level = adk::Level::Trace;
    std::filesystem::path log_directory = "logs/debug.log";

    adk::SetupLoggerStage2(log_directory, console_log_level, file_log_level);

    // Edit this to change the namespace of the add-on
    Object MyAddOn("custom_namespace");
    Data DataGenerator;
    Recipe RecipeGenerator;

    MyAddOn.init();
    DataGenerator.init();
    RecipeGenerator.init();

    return 0;
}