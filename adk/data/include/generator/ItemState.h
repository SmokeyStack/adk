#ifndef ITEMSTATE_H
#define ITEMSTATE_H

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "json.hpp"

namespace fs = std::filesystem;

enum ArmorGeometry { HEAD, CHEST, LEGS, FEET };

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

void simpleItem(std::string item, std::string icon) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./BP/items/" + item + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:item"]["components"]["minecraft:icon"]["texture"] = icon;

    TempFile.close();
    std::ofstream MyFile("./BP/items/" + item + ".json");
    MyFile << j.dump();
    MyFile.close();
}

void armorModel(std::string id, std::string item, std::string texture,
                ArmorGeometry geometry) {
    if (!fs::exists("./RP/attachables/"))
        fs::create_directory("./RP/attachables/");

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
    j["minecraft:attachable"]["description"]["scripts"]["animate"] = {"offset"};
    j["minecraft:attachable"]["description"]["animations"]["offset"] =
        getArmorSetup(geometry);
    j["minecraft:attachable"]["description"]["render_controllers"] = {
        "controller.render.armor"};

    MyJson << j.dump();
    MyJson.close();
}

#endif