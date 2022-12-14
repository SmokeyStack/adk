#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "json.hpp"

void simpleBlock(std::string block) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./packs/BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["material_instances"]["*"]["texture"] =
        block;

    TempFile.close();
    std::ofstream MyFile("./packs/BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();
}

void axisBlock(std::string block, std::string sides, std::string ends) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./packs/BP/blocks/" + block + ".json");
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
    std::ofstream MyFile("./packs/BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();
}

void customBlock(std::string block, std::string model, std::string texture) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./packs/BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["minecraft:geometry"] = model;
    j["minecraft:block"]["components"]["material_instances"]["*"]["texture"] =
        texture;

    TempFile.close();
    std::ofstream MyFile("./packs/BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();
}

void tintedGlass(std::string block, std::string texture) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./packs/BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["texture"] = texture;
    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["render_method"] = "blend";

    TempFile.close();
    std::ofstream MyFile("./packs/BP/blocks/" + block + ".json");
    MyFile << j.dump(4);
    MyFile.close();
}

#endif