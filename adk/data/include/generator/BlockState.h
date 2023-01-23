#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "json.hpp"

namespace fs = std::filesystem;

void simpleBlock(std::string block) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["material_instances"]["*"]["texture"] =
        block;

    TempFile.close();
    std::ofstream MyFile("./BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();
}

void axisBlock(std::string block, std::string sides, std::string ends) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["material_instances"]["*"]["texture"] =
        sides;
    j["minecraft:block"]["components"]["material_instances"]["ends"]
     ["texture"] = ends;
    j["minecraft:block"]["components"]["material_instances"]["up"]["texture"] =
        "ends";
    j["minecraft:block"]["components"]["material_instances"]["down"]
     ["texture"] = "ends";

    TempFile.close();
    std::ofstream MyFile("./BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();
}

void customBlock(std::string block, std::string model, std::string texture) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["minecraft:geometry"] = model;
    j["minecraft:block"]["components"]["material_instances"]["*"]["texture"] =
        texture;

    TempFile.close();
    std::ofstream MyFile("./BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();
}

void tintedGlass(std::string block, std::string texture) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["texture"] = texture;
    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["render_method"] = "blend";

    TempFile.close();
    std::ofstream MyFile("./BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();
}

void head(std::string block, std::string north, std::string east,
          std::string south, std::string west, std::string up,
          std::string down) {
    std::string my_text, temp_text;
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

    TempFile.close();
    std::ofstream MyFile("./BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();

    if (!fs::exists("./RP/models/entity/head.geo.json")) {
        if (!fs::exists("./RP/models/entity")) {
            fs::create_directory("./RP/models/");
            fs::create_directory("./RP/models/entity/");
        }

        fs::copy("./data/adk/assets/head.geo.json", "./RP/models/entity");
    }
}

#endif