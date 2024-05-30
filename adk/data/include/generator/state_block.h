#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "json.hpp"
#include "registry_global.h"
#include "utility/logger.h"

namespace adk {
	struct MaterialInstances {
		std::string textures;
		std::string render_method = "opaque";
		bool ambient_occlusion = true;
		bool face_dimming = true;
	};

	struct BlockTextures {
		MaterialInstances all;
		MaterialInstances sides;
		MaterialInstances ends;
		MaterialInstances up;
		MaterialInstances down;
		MaterialInstances north;
		MaterialInstances east;
		MaterialInstances south;
		MaterialInstances west;
	};

	void to_json(nlohmann::json& j, const MaterialInstances& p) {
		if (!p.textures.empty())
			j.update({ {"texture", p.textures} });
		if (p.render_method != "opaque") {
			j.update({ {"render_method", p.render_method} });
		}
		if (!p.ambient_occlusion) {
			j.update({ {"ambient_occlusion", p.ambient_occlusion} });
		}
		if (!p.face_dimming) {
			j.update({ {"face_dimming", p.face_dimming} });
		}
	}
}

nlohmann::json::object_t TranslateMaterialInstances(adk::BlockTextures textures) {
	nlohmann::json temp, output;
	temp = textures.all;
	if (!temp.is_null())
		output["minecraft:material_instances"]["*"] = temp;
	temp = textures.ends;
	if (!temp.is_null()) {
		output["minecraft:material_instances"]["ends"] = temp;
		output["minecraft:material_instances"]["up"] = "ends";
		output["minecraft:material_instances"]["down"] = "ends";
	}
	temp = textures.sides;
	if (!temp.is_null()) {
		output["minecraft:material_instances"]["sides"] = temp;
		output["minecraft:material_instances"]["north"] = "sides";
		output["minecraft:material_instances"]["east"] = "sides";
		output["minecraft:material_instances"]["south"] = "sides";
		output["minecraft:material_instances"]["west"] = "sides";
	}
	temp = textures.up;
	if (!temp.is_null())
		output["minecraft:material_instances"]["up"] = temp;
	temp = textures.down;
	if (!temp.is_null())
		output["minecraft:material_instances"]["down"] = temp;
	temp = textures.north;
	if (!temp.is_null())
		output["minecraft:material_instances"]["north"] = temp;
	temp = textures.east;
	if (!temp.is_null())
		output["minecraft:material_instances"]["east"] = temp;
	temp = textures.south;
	if (!temp.is_null())
		output["minecraft:material_instances"]["up"] = temp;
	temp = textures.west;
	if (!temp.is_null())
		output["minecraft:material_instances"]["west"] = temp;

	return output;
}

namespace adk {
	/**
	 * @brief Creates a one texture block
	 *
	 * @param block Identifier of the block, include namespace
	 *
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	void SimpleBlock(std::string block, BlockTextures textures) {
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

		output["minecraft:block"]["components"] = TranslateMaterialInstances(textures);
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
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "geometry.slab_adk";
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["top"] = "q.block_state('minecraft:vertical_half') == 'top' || q.block_state('" + id + ":is_double')";
		output["minecraft:block"]["components"]["minecraft:geometry"]["bone_visibility"]["bottom"] = "q.block_state('minecraft:vertical_half') == 'bottom' || q.block_state('" + id + ":is_double')";
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}

		const std::string sourcePath = "./data/adk/assets/slab.geo.json";
		const std::string targetPath = "./RP/models/blocks/adk/slab.geo.json";

		if (!std::filesystem::exists(targetPath)) {
			std::filesystem::create_directories("./RP/models/blocks/adk");
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
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "geometry.ladder_adk";
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}

		const std::string sourcePath = "./data/adk/assets/ladder.geo.json";
		const std::string targetPath = "./RP/models/blocks/adk/ladder.geo.json";

		if (!std::filesystem::exists(targetPath)) {
			std::filesystem::create_directories("./RP/models/blocks/adk");
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
		const std::string targetPath = "./RP/models/blocks/adk/ladder.geo.json";
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
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_north_adk";
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
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_east_adk";
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
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_west_adk";
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
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_south_adk";
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
		const std::string targetPath = "./RP/models/blocks/adk/stairs.geo.json";

		if (!std::filesystem::exists(targetPath)) {
			std::filesystem::create_directories("./RP/models/blocks/adk");
			std::filesystem::copy(sourcePath, targetPath);
		}
	}

	/**
	 * @brief Creates a stair block
	 *
	 * @param block Identifier of the block, omit namespace
	 *
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	void TorchBlock(std::string block, BlockTextures textures) {
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

		nlohmann::json textures_json;
		textures_json = textures.all;
		if (!textures_json.is_null())
			output["minecraft:block"]["components"]["minecraft:material_instances"]["*"] = textures_json;
		textures_json = textures.ends;
		if (!textures_json.is_null()) {
			output["minecraft:block"]["components"]["minecraft:material_instances"]["ends"] = textures_json;
			output["minecraft:block"]["components"]["minecraft:material_instances"]["up"] = "ends";
			output["minecraft:block"]["components"]["minecraft:material_instances"]["down"] = "ends";
		}
		textures_json = textures.sides;
		if (!textures_json.is_null()) {
			output["minecraft:block"]["components"]["minecraft:material_instances"]["sides"] = textures_json;
			output["minecraft:block"]["components"]["minecraft:material_instances"]["north"] = "sides";
			output["minecraft:block"]["components"]["minecraft:material_instances"]["east"] = "sides";
			output["minecraft:block"]["components"]["minecraft:material_instances"]["south"] = "sides";
			output["minecraft:block"]["components"]["minecraft:material_instances"]["west"] = "sides";
		}
		textures_json = textures.up;
		if (!textures_json.is_null())
			output["minecraft:block"]["components"]["minecraft:material_instances"]["up"] = textures_json;
		textures_json = textures.down;
		if (!textures_json.is_null())
			output["minecraft:block"]["components"]["minecraft:material_instances"]["down"] = textures_json;
		textures_json = textures.north;
		if (!textures_json.is_null())
			output["minecraft:block"]["components"]["minecraft:material_instances"]["north"] = textures_json;
		textures_json = textures.east;
		if (!textures_json.is_null())
			output["minecraft:block"]["components"]["minecraft:material_instances"]["east"] = textures_json;
		textures_json = textures.south;
		if (!textures_json.is_null())
			output["minecraft:block"]["components"]["minecraft:material_instances"]["up"] = textures_json;
		textures_json = textures.west;
		if (!textures_json.is_null())
			output["minecraft:block"]["components"]["minecraft:material_instances"]["west"] = textures_json;
		output["minecraft:block"]["components"]["minecraft:geometry"]["identifier"] = "geometry.torch_adk";
		std::string condition = fmt::format(
			"q.block_state('{state}') == 'north' || q.block_state('{state}') == 'east' || q.block_state('{state}') == 'south' || q.block_state('{state}') == 'west'",
			fmt::arg("state", "minecraft:block_face")
		);
		nlohmann::json::object_t geo_json = { {"condition",condition} };
		geo_json["components"]["minecraft:geometry"]["identifier"] = "geometry.torch_wall_adk";
		output["minecraft:block"]["permutations"].push_back(geo_json);
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}

		const std::string sourcePath = "./data/adk/assets/torch.geo.json";
		const std::string targetPath = "./RP/models/blocks/adk/torch.geo.json";

		if (!std::filesystem::exists(targetPath)) {
			std::filesystem::create_directories("./RP/models/blocks/adk");
			std::filesystem::copy(sourcePath, targetPath);
		}
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