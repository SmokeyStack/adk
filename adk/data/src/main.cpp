#include <filesystem>

#include "data.h"
#include "loot.h"
#include "object.h"
#include "recipe.h"
#include "utility/logger.h"

int main() {
	adk::SetupLoggerStage1();

	auto console_log_level = adk::Level::Info;
	auto file_log_level = adk::Level::Trace;
	std::filesystem::path log_directory = "logs/debug.log";

	adk::SetupLoggerStage2(log_directory, console_log_level, file_log_level);

	// Edit this to change the namespace of the add-on
	adk::Object MyAddOn("custom_namespace");
	adk::Data DataGenerator;
	adk::Recipe RecipeGenerator("custom_namespace");
	adk::Loot LootGenerator;

	MyAddOn.init();
	DataGenerator.init();
	DataGenerator.RegisterToCreativeMenu();
	RecipeGenerator.init();
	LootGenerator.init();

	return 0;
}