#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "json.hpp"
#include "registry_global.h"
#include "utility/logger.h"

namespace adk {
	/**
	 * @brief Creates a one texture block
	 *
	 * @param block Identifier of the block, include namespace
	 *
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	void SimpleBlock(std::string block, std::string texture) {
		auto registry = GetIDs();

		if (!(std::find(registry.begin(), registry.end(), block) != registry.end())) {
			log::error("No block found: {} - Please check if this block exists", block);
			exit(EXIT_FAILURE);
		}

		block = block.substr(block.find(":") + 1);
		const std::string filePath = "./BP/blocks/" + block + ".json";
		nlohmann::json output;
		{
			std::ifstream TempFile(filePath);
			TempFile >> output;
		}
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["texture"] = texture;
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "minecraft:geometry.full_block";
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}
	}

	/**
	 * @brief Creates a slab block
	 *
	 * @param block Identifier of the block, omit namespace
	 *
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	void SlabBlock(std::string block, std::string texture, std::string up = "") {
		auto registry = GetIDs();

		if (!(std::find(registry.begin(), registry.end(), block) != registry.end())) {
			log::error("No block found: {} - Please check if this block exists", block);
			exit(EXIT_FAILURE);
		}

		std::string id = block;
		block = block.substr(block.find(":") + 1);
		id = id.substr(0, id.find(":"));
		const std::string filePath = "./BP/blocks/" + block + ".json";
		nlohmann::json output;
		{
			std::ifstream TempFile(filePath);
			TempFile >> output;
		}
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["texture"] = texture;
		output["minecraft:block"]["components"]["minecraft:material_instances"]["ends"]["texture"] = up;
		if (!up.empty()) {
			output["minecraft:block"]["components"]["minecraft:material_instances"]["up"] = "ends";
			output["minecraft:block"]["components"]["minecraft:material_instances"]["down"] = "ends";
		}
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "geometry.slab";
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["top"] = "q.block_state('minecraft:vertical_half') == 'top' || q.block_state('" + id + ":is_double')";
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["bottom"] = "q.block_state('minecraft:vertical_half') == 'bottom' || q.block_state('" + id + ":is_double')";
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}

		const std::string sourcePath = "./data/adk/assets/slab.geo.json";
		const std::string targetPath = "./RP/models/blocks/slab.geo.json";

		if (!std::filesystem::exists(targetPath)) {
			std::filesystem::create_directories("./RP/models/blocks");
			std::filesystem::copy(sourcePath, targetPath);
		}
	}

	/**
	 * @brief Creates a ladder block
	 *
	 * @param block Identifier of the block, omit namespace
	 *
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	void LadderBlock(std::string block, std::string texture) {
		auto registry = GetIDs();

		if (!(std::find(registry.begin(), registry.end(), block) != registry.end())) {
			log::error("No block found: {} - Please check if this block exists", block);
			exit(EXIT_FAILURE);
		}

		std::string id = block;
		block = block.substr(block.find(":") + 1);
		id = id.substr(0, id.find(":"));
		const std::string filePath = "./BP/blocks/" + block + ".json";
		nlohmann::json output;
		{
			std::ifstream TempFile(filePath);
			TempFile >> output;
		}
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["texture"] = texture;
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["render_method"] = "alpha_test";
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["face_dimming"] = false;
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["ambient_occlusion"] = false;
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "geometry.ladder";
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}

		const std::string sourcePath = "./data/adk/assets/ladder.geo.json";
		const std::string targetPath = "./RP/models/blocks/ladder.geo.json";

		if (!std::filesystem::exists(targetPath)) {
			std::filesystem::create_directories("./RP/models/blocks");
			std::filesystem::copy(sourcePath, targetPath);
		}
	}

	/**
	 * @brief Creates a cross block
	 *
	 * @param block Identifier of the block, omit namespace
	 *
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	void CrossBlock(std::string block, std::string texture) {
		auto registry = GetIDs();

		if (!(std::find(registry.begin(), registry.end(), block) != registry.end())) {
			log::error("No block found: {} - Please check if this block exists", block);
			exit(EXIT_FAILURE);
		}

		std::string id = block;
		block = block.substr(block.find(":") + 1);
		id = id.substr(0, id.find(":"));
		const std::string filePath = "./BP/blocks/" + block + ".json";
		nlohmann::json output;
		{
			std::ifstream TempFile(filePath);
			TempFile >> output;
		}
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["texture"] = texture;
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["render_method"] = "alpha_test";
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["face_dimming"] = false;
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["ambient_occlusion"] = false;
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "minecraft:geometry.cross";
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}

		const std::string sourcePath = "./data/adk/assets/ladder.geo.json";
		const std::string targetPath = "./RP/models/blocks/ladder.geo.json";
	}

	/**
	 * @brief Creates a stair block
	 *
	 * @param block Identifier of the block, omit namespace
	 *
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	void StairsBlock(std::string block, std::string texture) {
		auto registry = GetIDs();

		if (!(std::find(registry.begin(), registry.end(), block) != registry.end())) {
			log::error("No block found: {} - Please check if this block exists", block);
			exit(EXIT_FAILURE);
		}

		std::string id = block;
		block = block.substr(block.find(":") + 1);
		id = id.substr(0, id.find(":"));
		const std::string filePath = "./BP/blocks/" + block + ".json";
		nlohmann::json output;
		{
			std::ifstream TempFile(filePath);
			TempFile >> output;
		}
		output["minecraft:block"]["components"]["minecraft:material_instances"]["*"]["texture"] = texture;
		std::string upper_north_east = fmt::format(
			"q.block_state('{namespace}:shape') == 'straight' || q.block_state('{namespace}:shape') == 'outer_right' || q.block_state('{namespace}:shape') == 'inner_left' || q.block_state('{namespace}:shape') == 'inner_right' || q.block_state('minecraft:vertical_half') == 'top'",
			fmt::arg("namespace", id)
		);
		std::string upper_north_west = fmt::format(
			"q.block_state('{namespace}:shape') == 'straight' || q.block_state('{namespace}:shape') == 'outer_left' || q.block_state('{namespace}:shape') == 'inner_left' || q.block_state('{namespace}:shape') == 'inner_right' || q.block_state('minecraft:vertical_half') == 'top'",
			fmt::arg("namespace", id)
		);
		std::string upper_south_east = fmt::format(
			"q.block_state('{namespace}:shape') == 'inner_left' || q.block_state('minecraft:vertical_half') == 'top'",
			fmt::arg("namespace", id)
		);
		std::string upper_south_west = fmt::format(
			"q.block_state('{namespace}:shape') == 'inner_right' || q.block_state('minecraft:vertical_half') == 'top'",
			fmt::arg("namespace", id)
		);
		std::string lower_north_east = fmt::format(
			"q.block_state('{namespace}:shape') == 'straight' || q.block_state('{namespace}:shape') == 'outer_right' || q.block_state('{namespace}:shape') == 'inner_left' || q.block_state('{namespace}:shape') == 'inner_right' || q.block_state('minecraft:vertical_half') == 'bottom'",
			fmt::arg("namespace", id)
		);
		std::string lower_north_west = fmt::format(
			"q.block_state('{namespace}:shape') == 'straight' || q.block_state('{namespace}:shape') == 'outer_left' || q.block_state('{namespace}:shape') == 'inner_left' || q.block_state('{namespace}:shape') == 'inner_right' || q.block_state('minecraft:vertical_half') == 'bottom'",
			fmt::arg("namespace", id)
		);
		std::string lower_south_east = fmt::format(
			"q.block_state('{namespace}:shape') == 'inner_left' || q.block_state('minecraft:vertical_half') == 'bottom'",
			fmt::arg("namespace", id)
		);
		std::string lower_south_west = fmt::format(
			"q.block_state('{namespace}:shape') == 'inner_right' || q.block_state('minecraft:vertical_half') == 'bottom'",
			fmt::arg("namespace", id)
		);
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_north";
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["upper_north_east"] = upper_north_east;
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["upper_north_west"] = upper_north_west;
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["upper_south_east"] = upper_south_east;
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["upper_south_west"] = upper_south_west;
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["lower_north_east"] = lower_north_east;
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["lower_north_west"] = lower_north_west;
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["lower_south_east"] = lower_south_east;
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["lower_south_west"] = lower_south_west;
		nlohmann::json::object_t temp = {
			{"condition",
			 "q.block_state('minecraft:cardinal_direction') == 'east'"} };
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_east";
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_north_east"] = upper_north_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_north_west"] = upper_north_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_south_east"] = upper_south_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_south_west"] = upper_south_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_north_east"] = lower_north_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_north_west"] = lower_north_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_south_east"] = lower_south_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_south_west"] = lower_south_west;
		output["minecraft:block"]["permutations"].push_back(temp);
		temp = {
			{"condition",
			 "q.block_state('minecraft:cardinal_direction') == 'west'"} };
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_west";
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_north_east"] = upper_north_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_north_west"] = upper_north_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_south_east"] = upper_south_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_south_west"] = upper_south_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_north_east"] = lower_north_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_north_west"] = lower_north_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_south_east"] = lower_south_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_south_west"] = lower_south_west;
		output["minecraft:block"]["permutations"].push_back(temp);
		temp = {
			{"condition",
			 "q.block_state('" + id + ":south')"} };
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_south";
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_north_east"] = upper_north_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_north_west"] = upper_north_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_south_east"] = upper_south_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["upper_south_west"] = upper_south_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_north_east"] = lower_north_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_north_west"] = lower_north_west;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_south_east"] = lower_south_east;
		temp["components"]["minecraft:geometry"]["bone_visibility"]["lower_south_west"] = lower_south_west;
		output["minecraft:block"]["permutations"].push_back(temp);
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}

		const std::string sourcePath = "./data/adk/assets/stairs.geo.json";
		const std::string targetPath = "./RP/models/blocks/stairs.geo.json";

		if (!std::filesystem::exists(targetPath)) {
			std::filesystem::create_directories("./RP/models/blocks");
			std::filesystem::copy(sourcePath, targetPath);
		}
	}

	/**
	 * @brief Sides can have different textures
	 *
	 * @param block Identifier of the block, omit namespace
	 * @param north Texture for the north face
	 * @param east Texture for the east face
	 * @param south Texture for the south face
	 * @param west Texture for the west face
	 * @param up Texture for the up face
	 * @param down Texture for the down face
	 */
	void simpleBlock(std::string block, std::string north, std::string east,
		std::string south, std::string west, std::string up,
		std::string down) {
		std::string my_text, temp_text;

		if (!std::filesystem::exists("./BP/blocks/" + block + ".json")) {
			log
				::error(
					"No block found: {}.json - Please check if this block exists",
					block);
			exit(EXIT_FAILURE);
		}

		std::ifstream TempFile("./BP/blocks/" + block + ".json");
		nlohmann::json j = nlohmann::json::parse(TempFile);

		j["minecraft:block"]["components"]["minecraft:material_instances"]["north"]
			["texture"] = north;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["east"]
			["texture"] = east;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["south"]
			["texture"] = south;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["west"]
			["texture"] = west;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["up"]
			["texture"] = up;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["down"]
			["texture"] = down;
		j["minecraft:block"]["components"]["minecraft:unit_cube"] =
			nlohmann::json::object();

		TempFile.close();
		std::ofstream MyFile("./BP/blocks/" + block + ".json");
		MyFile << j.dump();
		MyFile.close();
	}

	/**
	 * @brief Creates a log like block, sides are one texture, ends are one texture
	 *
	 * @param block Identifier of the block, omit namespace
	 * @param sides Texture name for the sides of the block
	 * @param ends Texture name for the ends of the block
	 */
	void axisBlock(std::string block, std::string sides, std::string ends) {
		std::string my_text, temp_text;

		if (!std::filesystem::exists("./BP/blocks/" + block + ".json")) {
			log
				::error(
					"No block found: {}.json - Please check if this block exists",
					block);
			exit(EXIT_FAILURE);
		}

		std::ifstream TempFile("./BP/blocks/" + block + ".json");
		nlohmann::json j = nlohmann::json::parse(TempFile);

		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["texture"] = sides;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["ends"]
			["texture"] = ends;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["up"]
			["texture"] = "ends";
		j["minecraft:block"]["components"]["minecraft:material_instances"]["down"]
			["texture"] = "ends";
		j["minecraft:block"]["components"]["minecraft:unit_cube"] =
			nlohmann::json::object();

		TempFile.close();
		std::ofstream MyFile("./BP/blocks/" + block + ".json");
		MyFile << j.dump();
		MyFile.close();
	}

	/**
	 * @brief Creates a custom geometry block
	 *
	 * @param block Identifier of the block, omit namespace
	 * @param model Identifier of the geometry
	 * @param texture Texture name for the block
	 */
	void customBlock(std::string block, std::string model, std::string texture) {
		std::string my_text, temp_text;

		if (!std::filesystem::exists("./BP/blocks/" + block + ".json")) {
			log
				::error(
					"No block found: {}.json - Please check if this block exists",
					block);
			exit(EXIT_FAILURE);
		}

		std::ifstream TempFile("./BP/blocks/" + block + ".json");
		nlohmann::json j = nlohmann::json::parse(TempFile);

		j["minecraft:block"]["components"]["minecraft:geometry"] = model;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["texture"] = texture;

		TempFile.close();
		std::ofstream MyFile("./BP/blocks/" + block + ".json");
		MyFile << j.dump();
		MyFile.close();
	}

	void tintedGlass(std::string block, std::string texture) {
		std::string my_text, temp_text;

		if (!std::filesystem::exists("./BP/blocks/" + block + ".json")) {
			log
				::error(
					"No block found: {}.json - Please check if this block exists",
					block);
			exit(EXIT_FAILURE);
		}

		std::ifstream TempFile("./BP/blocks/" + block + ".json");
		nlohmann::json j = nlohmann::json::parse(TempFile);

		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["texture"] = texture;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["render_method"] = "blend";
		j["minecraft:block"]["components"]["minecraft:unit_cube"] =
			nlohmann::json::object();

		TempFile.close();
		std::ofstream MyFile("./BP/blocks/" + block + ".json");
		MyFile << j.dump();
		MyFile.close();
	}

	/**
	 * @brief Creates a skull block
	 *
	 * @param block Identifier of the block, omit namespace
	 * @param texture Texture for the block
	 */
	void headBlock(std::string block, std::string texture) {
		std::string my_text, temp_text;

		if (!std::filesystem::exists("./BP/blocks/" + block + ".json")) {
			log
				::error(
					"No block found: {}.json - Please check if this block exists",
					block);
			exit(EXIT_FAILURE);
		}

		std::ifstream TempFile("./BP/blocks/" + block + ".json");
		nlohmann::json j = nlohmann::json::parse(TempFile);

		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["texture"] = texture;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["render_method"] = "blend";

		TempFile.close();
		std::ofstream MyFile("./BP/blocks/" + block + ".json");
		MyFile << j.dump();
		MyFile.close();

		if (!std::filesystem::exists("./RP/models/entity/head.geo.json")) {
			if (!std::filesystem::exists("./RP/models/entity")) {
				std::filesystem::create_directory("./RP/models/");
				std::filesystem::create_directory("./RP/models/entity/");
			}

			std::filesystem::copy("./data/adk/assets/head.geo.json", "./RP/models/entity");
		}
	}

	/**
	 * @brief Creates a skull block, sides are one texture, ends are one texture
	 *
	 * @param block Identifier of the block, omit namespace
	 * @param sides Texture name for the sides of the block
	 * @param ends Texture name for the ends of the block
	 */
	void headBlock(std::string block, std::string sides, std::string ends) {
		std::string my_text, temp_text;

		if (!std::filesystem::exists("./BP/blocks/" + block + ".json")) {
			log
				::error(
					"No block found: {}.json - Please check if this block exists",
					block);
			exit(EXIT_FAILURE);
		}

		std::ifstream TempFile("./BP/blocks/" + block + ".json");
		nlohmann::json j = nlohmann::json::parse(TempFile);

		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["texture"] = sides;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["up"]
			["texture"] = ends;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["up"]
			["texture"] = ends;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["render_method"] = "blend";
		j["minecraft:block"]["components"]["minecraft:material_instances"]["up"]
			["render_method"] = "blend";
		j["minecraft:block"]["components"]["minecraft:material_instances"]["up"]
			["render_method"] = "blend";

		TempFile.close();
		std::ofstream MyFile("./BP/blocks/" + block + ".json");
		MyFile << j.dump();
		MyFile.close();

		if (!std::filesystem::exists("./RP/models/entity/head.geo.json")) {
			if (!std::filesystem::exists("./RP/models/entity")) {
				std::filesystem::create_directory("./RP/models/");
				std::filesystem::create_directory("./RP/models/entity/");
			}

			std::filesystem::copy("./data/adk/assets/head.geo.json", "./RP/models/entity");
		}
	}

	/**
	 * @brief Creates a skull block. Sides can have different textures
	 *
	 * @param block Identifier of the block, omit namespace
	 * @param north Texture for the north face
	 * @param east Texture for the east face
	 * @param south Texture for the south face
	 * @param west Texture for the west face
	 * @param up Texture for the up face
	 * @param down Texture for the down face
	 */
	void headBlock(std::string block, std::string north, std::string east,
		std::string south, std::string west, std::string up,
		std::string down) {
		std::string my_text, temp_text;

		if (!std::filesystem::exists("./BP/blocks/" + block + ".json")) {
			log
				::error(
					"No block found: {}.json - Please check if this block exists",
					block);
			exit(EXIT_FAILURE);
		}

		std::ifstream TempFile("./BP/blocks/" + block + ".json");
		nlohmann::json j = nlohmann::json::parse(TempFile);

		j["minecraft:block"]["components"]["minecraft:material_instances"]["north"]
			["texture"] = north;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["east"]
			["texture"] = east;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["south"]
			["texture"] = south;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["west"]
			["texture"] = west;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["up"]
			["texture"] = up;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["down"]
			["texture"] = down;
		j["minecraft:block"]["components"]["minecraft:material_instances"]["north"]
			["render_method"] = "blend";
		j["minecraft:block"]["components"]["minecraft:material_instances"]["east"]
			["render_method"] = "blend";
		j["minecraft:block"]["components"]["minecraft:material_instances"]["south"]
			["render_method"] = "blend";
		j["minecraft:block"]["components"]["minecraft:material_instances"]["west"]
			["render_method"] = "blend";
		j["minecraft:block"]["components"]["minecraft:material_instances"]["up"]
			["render_method"] = "blend";
		j["minecraft:block"]["components"]["minecraft:material_instances"]["down"]
			["render_method"] = "blend";

		TempFile.close();
		std::ofstream MyFile("./BP/blocks/" + block + ".json");
		MyFile << j.dump();
		MyFile.close();

		if (!std::filesystem::exists("./RP/models/entity/head.geo.json")) {
			if (!std::filesystem::exists("./RP/models/entity")) {
				std::filesystem::create_directory("./RP/models/");
				std::filesystem::create_directory("./RP/models/entity/");
			}

			std::filesystem::copy("./data/adk/assets/head.geo.json", "./RP/models/entity");
		}
	}

	/**
	 * @brief Creates a candle block
	 *
	 * @param block Identifier of the block, omit namespace
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	void candleBlock(std::string block, std::string texture) {
		std::string my_text, temp_text;

		if (!std::filesystem::exists("./BP/blocks/" + block + ".json")) {
			log
				::error(
					"No block found: {}.json - Please check if this block exists",
					block);
			exit(EXIT_FAILURE);
		}

		std::ifstream TempFile("./BP/blocks/" + block + ".json");
		nlohmann::json j = nlohmann::json::parse(TempFile);

		j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
			["texture"] = texture;

		TempFile.close();
		std::ofstream MyFile("./BP/blocks/" + block + ".json");
		MyFile << j.dump();
		MyFile.close();

		if (!std::filesystem::exists("./RP/models/entity/candle.geo.json")) {
			if (!std::filesystem::exists("./RP/models/entity")) {
				std::filesystem::create_directory("./RP/models/");
				std::filesystem::create_directory("./RP/models/entity/");
			}

			std::filesystem::copy("./data/adk/assets/candle.geo.json", "./RP/models/entity");
		}
	}
} // namespace adk