#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents Armor model
	 *
	 */
	enum ArmorGeometry { HEAD, CHEST, LEGS, FEET };

	/**
	 * @brief Get the Armor Geometry object
	 *
	 * @param geometry enum ArmorGeometry
	 * @return std::string
	 */
	std::string getArmorGeometry(ArmorGeometry geometry) {
		switch (geometry) {
		case HEAD:
			return "geometry.player.armor.helmet";
		case CHEST:
			return "geometry.player.armor.chestplate";
		case LEGS:
			return "geometry.player.armor.leggings";
		case FEET:
			return "geometry.player.armor.boots";
		default:
			return "Error";
		}
	}

	/**
	 * @brief Get the Armor Setup object
	 *
	 * @param geometry enum ArmorGeometry
	 * @return std::string
	 */
	std::string getArmorSetup(ArmorGeometry geometry) {
		switch (geometry) {
		case HEAD:
			return "v.helmet_layer_visible = 0.0;";
		case CHEST:
			return "v.leg_layer_visible = 0.0;";
		case LEGS:
			return "v.chest_layer_visible = 0.0;";
		case FEET:
			return "v.boot_layer_visible = 0.0;";
		default:
			return "Error";
		}
	}

	/**
	 * @brief Get the Armor Offset object
	 *
	 * @param geometry enum ArmorGeometry
	 * @return std::string
	 */
	std::string getArmorOffset(ArmorGeometry geometry) {
		switch (geometry) {
		case HEAD:
			return "animation.armor.helmet.offset";
		case CHEST:
			return "animation.armor.chestplate.offset";
		case LEGS:
			return "animation.armor.leggings.offset";
		case FEET:
			return "animation.armor.boots.offset";
		default:
			return "Error";
		}
	}

	/**
	 * @brief Creates a simple item
	 *
	 * @param item Identifier of the item, omit namespace
	 *
	 * @param icon Name of the texture defined in `item_texture.json`
	 */
	void SimpleItem(const std::string item, const std::string icon) {
		const std::string filePath = "./BP/items/" + item + ".json";
		nlohmann::json output;
		{
			std::ifstream TempFile(filePath);
			TempFile >> output;
		}
		output["minecraft:item"]["components"]["minecraft:icon"]["textures"]["default"] = icon;
		{
			std::ofstream OutputFile(filePath);
			OutputFile << output.dump();
		}
	}

	/**
	 * @brief Creates armor
	 *
	 * @param id Namespace
	 * @param item Identifier of the item
	 * @param texture Path of the texture
	 * @param geometry enum ArmorGeometry
	 */
	void armorModel(std::string id, std::string item, std::string texture,
		ArmorGeometry geometry) {
		if (!std::filesystem::exists("./RP/attachables/"))
			std::filesystem::create_directory("./RP/attachables/");

		std::ofstream MyJson("./RP/attachables/" + item + ".json");
		nlohmann::json j;

		j["format_version"] = "1.10.0";
		j["minecraft:attachable"]["description"]["identifier"] = id + ":" + item;
		j["minecraft:attachable"]["description"]["item"][id + ":" + item] =
			"q.owner_identifier == 'minecraft:player'";
		j["minecraft:attachable"]["description"]["materials"]["default"] = "armor";
		j["minecraft:attachable"]["description"]["materials"]["enchanted"] =
			"armor_enchanted";
		j["minecraft:attachable"]["description"]["textures"]["default"] = texture;
		j["minecraft:attachable"]["description"]["textures"]["enchanted"] =
			"textures/misc/enchanted_item_glint";
		j["minecraft:attachable"]["description"]["geometry"]["default"] =
			getArmorGeometry(geometry);
		j["minecraft:attachable"]["description"]["scripts"]["parent_setup"] =
			getArmorSetup(geometry);
		j["minecraft:attachable"]["description"]["scripts"]["animate"] = { "offset" };
		j["minecraft:attachable"]["description"]["animations"]["offset"] =
			getArmorSetup(geometry);
		j["minecraft:attachable"]["description"]["render_controllers"] = {
			"controller.render.armor" };

		MyJson << j.dump();
		MyJson.close();
	}
} // namespace adk