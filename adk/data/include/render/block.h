#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "json.hpp"
#include "registry_global.h"
#include "utility/logger.h"


namespace adk {
	enum RenderMethod {
		opaque,
		double_sided,
		blend,
		alpha_test,
	};

	class MaterialInstances {
	public:
		MaterialInstances() {};
		~MaterialInstances() {};

		MaterialInstances& SetTextures(std::string textures) {
			textures_ = textures;
			return *this;
		}
		MaterialInstances& SetRenderMethod(RenderMethod render_method) {
			render_method_ = render_method;
			return *this;
		}
		MaterialInstances& SetAmbientOcclusion(bool ambient_occlusion) {
			ambient_occlusion_ = ambient_occlusion;
			return *this;
		}
		MaterialInstances& SetFaceDimming(bool face_dimming) {
			face_dimming_ = face_dimming;
			return *this;
		}
		std::string GetTextures() {
			return textures_;
		}
		nlohmann::json::object_t Generate() {
			nlohmann::json::object_t output;

			if (!textures_.empty())
				output["texture"] = textures_;
			if (render_method_ != RenderMethod::opaque)
				output["render_method"] = render_method_;
			if (!ambient_occlusion_)
				output["ambient_occlusion"] = ambient_occlusion_;
			if (!face_dimming_)
				output["face_dimming"] = face_dimming_;

			return output;
		}
	private:
		std::string textures_;
		RenderMethod render_method_ = RenderMethod::opaque;
		bool ambient_occlusion_ = true;
		bool face_dimming_ = true;
	};

	class BlockRenderer {
	public:
		BlockRenderer() {};
		~BlockRenderer() {};

		BlockRenderer& SetAll(MaterialInstances all) {
			this->all_ = all;
			return *this;
		}
		BlockRenderer& SetSides(MaterialInstances sides) {
			this->sides_ = sides;
			return *this;
		}
		BlockRenderer& SetEnds(MaterialInstances ends) {
			this->ends_ = ends;
			return *this;
		}
		BlockRenderer& SetUp(MaterialInstances up) {
			this->up_ = up;
			return *this;
		}
		BlockRenderer& SetDown(MaterialInstances down) {
			this->down_ = down;
			return *this;
		}
		BlockRenderer& SetNorth(MaterialInstances north) {
			this->north_ = north;
			return *this;
		}
		BlockRenderer& SetEast(MaterialInstances east) {
			this->east_ = east;
			return *this;
		}
		BlockRenderer& SetSouth(MaterialInstances south) {
			this->south_ = south;
			return *this;
		}
		BlockRenderer& SetWest(MaterialInstances west) {
			this->west_ = west;
			return *this;
		}
		nlohmann::json::object_t Generate() {
			nlohmann::json output;
			auto& material = output["minecraft:material_instances"];

			if (!all_.GetTextures().empty())
				material["*"] = all_.Generate();
			if (!ends_.GetTextures().empty()) {
				material["ends"] = ends_.Generate();
				material["up"] = "ends";
				material["down"] = "ends";
			}
			if (!sides_.GetTextures().empty()) {
				material["sides"] = sides_.Generate();
				material["north"] = "sides";
				material["east"] = "sides";
				material["south"] = "sides";
				material["west"] = "sides";
			}
			if (!up_.GetTextures().empty())
				material["up"] = up_.Generate();
			if (!down_.GetTextures().empty())
				material["down"] = down_.Generate();
			if (!north_.GetTextures().empty())
				material["north"] = north_.Generate();
			if (!east_.GetTextures().empty())
				material["east"] = east_.Generate();
			if (!south_.GetTextures().empty())
				material["south"] = south_.Generate();
			if (!west_.GetTextures().empty())
				material["west"] = west_.Generate();

			return output;
		}

	private:
		MaterialInstances all_;
		MaterialInstances sides_;
		MaterialInstances ends_;
		MaterialInstances up_;
		MaterialInstances down_;
		MaterialInstances north_;
		MaterialInstances east_;
		MaterialInstances south_;
		MaterialInstances west_;
	};

	/**
	 * @brief Creates a one texture block
	 *
	 * @param block Identifier of the block, include namespace
	 *
	 * @param textures A BlockRenderer configuration for the block
	 */
	void SimpleBlock(std::string block, BlockRenderer textures) {
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

		auto& material = output["minecraft:block"]["components"];
		material.update(textures.Generate());
		material["minecraft:geometry"]["identifier"] = "minecraft:geometry.full_block";

		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}
	}

	/**
	 * @brief Creates a slab block
	 *
	 * @param block Identifier of the block, include namespace
	 *
	 * @param textures A BlockRenderer configuration for the block
	 */
	void SlabBlock(std::string block, BlockRenderer textures) {
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

		auto& material = output["minecraft:block"]["components"];
		material.update(textures.Generate());
		material["minecraft:geometry"]["identifier"] = "geometry.slab_adk";
		std::string condition_top = fmt::format("q.block_state('minecraft:vertical_half') == 'top' || q.block_state('{namespace}:is_double')", fmt::arg("namespace", id));
		std::string condition_bottom = fmt::format("q.block_state('minecraft:vertical_half') == 'bottom' || q.block_state('{namespace}:is_double')", fmt::arg("namespace", id));
		material["minecraft:geometry"]["bone_visibility"]["top"] = condition_top;
		material["minecraft:geometry"]["bone_visibility"]["bottom"] = condition_bottom;

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
	 * @param block Identifier of the block, include namespace
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

		auto& material = output["minecraft:block"]["components"];
		material.update(BlockRenderer()
			.SetAll(MaterialInstances()
				.SetTextures(texture)
				.SetRenderMethod(RenderMethod::alpha_test)
				.SetFaceDimming(false)
				.SetAmbientOcclusion(false))
			.Generate());
		material["minecraft:geometry"]["identifier"] = "geometry.ladder_adk";

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
	 * @param block Identifier of the block, include namespace
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

		auto& material = output["minecraft:block"]["components"];
		material.update(BlockRenderer()
			.SetAll(MaterialInstances()
				.SetTextures(texture)
				.SetRenderMethod(RenderMethod::alpha_test)
				.SetFaceDimming(false)
				.SetAmbientOcclusion(false))
			.Generate());
		material["minecraft:geometry"]["identifier"] = "minecraft:geometry.cross";

		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}
	}

	/**
	 * @brief Creates a stair block
	 *
	 * @param block Identifier of the block, include namespace
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

		auto& material = output["minecraft:block"]["components"];
		material.update(BlockRenderer()
			.SetAll(MaterialInstances()
				.SetTextures(texture))
			.Generate());
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
		nlohmann::json::object_t temp = {
			{"condition",
			 "q.block_state('minecraft:cardinal_direction') == 'north'"} };
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_adk";
		auto& temp_bone_visibility = temp["components"]["minecraft:geometry"]["bone_visibility"];
		temp_bone_visibility["upper_north_east"] = upper_north_east;
		temp_bone_visibility["upper_north_west"] = upper_north_west;
		temp_bone_visibility["upper_south_east"] = upper_south_east;
		temp_bone_visibility["upper_south_west"] = upper_south_west;
		temp_bone_visibility["lower_north_east"] = lower_north_east;
		temp_bone_visibility["lower_north_west"] = lower_north_west;
		temp_bone_visibility["lower_south_east"] = lower_south_east;
		temp_bone_visibility["lower_south_west"] = lower_south_west;
		output["minecraft:block"]["permutations"].push_back(temp);
		temp = {
			{"condition",
			 "q.block_state('minecraft:cardinal_direction') == 'east'"} };
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_adk";
		auto& temp_bone_visibility_east = temp["components"]["minecraft:geometry"]["bone_visibility"];
		temp_bone_visibility_east["upper_south_east"] = upper_north_east;
		temp_bone_visibility_east["upper_north_east"] = upper_north_west;
		temp_bone_visibility_east["upper_south_west"] = upper_south_east;
		temp_bone_visibility_east["upper_north_west"] = upper_south_west;
		temp_bone_visibility_east["lower_south_east"] = lower_north_east;
		temp_bone_visibility_east["lower_north_east"] = lower_north_west;
		temp_bone_visibility_east["lower_south_west"] = lower_south_east;
		temp_bone_visibility_east["lower_north_west"] = lower_south_west;
		output["minecraft:block"]["permutations"].push_back(temp);
		temp = {
			{"condition",
			 "q.block_state('minecraft:cardinal_direction') == 'south'"} };
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_adk";
		auto& temp_bone_visibility_south = temp["components"]["minecraft:geometry"]["bone_visibility"];
		temp_bone_visibility_south["upper_south_west"] = upper_north_east;
		temp_bone_visibility_south["upper_north_east"] = upper_north_west;
		temp_bone_visibility_south["upper_north_west"] = upper_south_east;
		temp_bone_visibility_south["upper_north_east"] = upper_south_west;
		temp_bone_visibility_south["lower_south_west"] = lower_north_east;
		temp_bone_visibility_south["lower_north_east"] = lower_north_west;
		temp_bone_visibility_south["lower_north_west"] = lower_south_east;
		temp_bone_visibility_south["lower_north_east"] = lower_south_west;
		output["minecraft:block"]["permutations"].push_back(temp);
		temp = {
			{"condition",
			 "q.block_state('minecraft:cardinal_direction') == 'west'"} };
		temp["components"]["minecraft:geometry"]["identifier"] = "geometry.stairs_adk";
		auto& temp_bone_visibility_west = temp["components"]["minecraft:geometry"]["bone_visibility"];
		temp_bone_visibility_west["upper_north_west"] = upper_north_east;
		temp_bone_visibility_west["upper_south_west"] = upper_north_west;
		temp_bone_visibility_west["upper_north_east"] = upper_south_east;
		temp_bone_visibility_west["upper_south_east"] = upper_south_west;
		temp_bone_visibility_west["lower_north_west"] = lower_north_east;
		temp_bone_visibility_west["lower_south_west"] = lower_north_west;
		temp_bone_visibility_west["lower_north_east"] = lower_south_east;
		temp_bone_visibility_west["lower_south_east"] = lower_south_west;
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
	 * @param block Identifier of the block, include namespace
	 *
	 * @param texture Name of the texture defined in `terrain_texture.json`
	 */
	 /*void TorchBlock(std::string block, BlockTextures textures) {
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
	 }*/

	 /**
	  * @brief Creates a candle block
	  *
	  * @param block Identifier of the block, include namespace
	  *
	  * @param textures A BlockTextures configuration for the block
	  */
	void CandleBlock(std::string block, std::string texture) {
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

		auto& material = output["minecraft:block"]["components"];
		material.update(BlockRenderer()
			.SetAll(MaterialInstances()
				.SetTextures(texture))
			.Generate());

		for (const auto& [key, value] : output["minecraft:block"]["permutations"].items()) {
			if (value.contains("condition") && value["condition"].dump() == fmt::format("\"q.block_state('{namespace}:candles') == 1\"", fmt::arg("namespace", id)))
				value["components"]["minecraft:geometry"]["identifier"] = "geometry.candle_one_adk";
			if (value.contains("condition") && value["condition"].dump() == fmt::format("\"q.block_state('{namespace}:candles') == 2\"", fmt::arg("namespace", id)))
				value["components"]["minecraft:geometry"]["identifier"] = "geometry.candle_two_adk";
			if (value.contains("condition") && value["condition"].dump() == fmt::format("\"q.block_state('{namespace}:candles') == 3\"", fmt::arg("namespace", id)))
				value["components"]["minecraft:geometry"]["identifier"] = "geometry.candle_three_adk";
			if (value.contains("condition") && value["condition"].dump() == fmt::format("\"q.block_state('{namespace}:candles') == 4\"", fmt::arg("namespace", id)))
				value["components"]["minecraft:geometry"]["identifier"] = "geometry.candle_four_adk";
			if (value.contains("condition") && value["condition"].dump() == fmt::format("\"q.block_state('{namespace}:lit') == 4\"", fmt::arg("namespace", id)))
				value["components"].update(BlockRenderer()
					.SetAll(MaterialInstances()
						.SetTextures(texture)
						.SetFaceDimming(false))
					.Generate());
		}

		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}

		const std::string sourcePath = "./data/adk/assets/candle.geo.json";
		const std::string targetPath = "./RP/models/blocks/adk/candle.geo.json";

		if (!std::filesystem::exists(targetPath)) {
			std::filesystem::create_directories("./RP/models/blocks/adk");
			std::filesystem::copy(sourcePath, targetPath);
		}
	}
} // namespace adk