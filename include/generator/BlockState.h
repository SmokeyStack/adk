#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

#include <fstream>
#include <string>

#include "json.hpp"

void simpleBlock(std::string block) {
    std::string my_text, temp_text;
    std::ifstream TempFile("./packs/BP/blocks/" + block + ".json");
    std::ofstream MyFile("./packs/BP/blocks/" + block + ".json");

    while (getline(TempFile, my_text)) temp_text = temp_text + my_text;

    TempFile.close();

    nlohmann::json j = nlohmann::json::parse(temp_text);
    j["minecraft:block"]["components"]["material_instances"]["*"]["texture"] =
        block;
    j["minecraft:block"]["components"]["minecraft:unit_cube"] =
        nlohmann::json::object();

    MyFile << j.dump(4);
    MyFile.close();
}

#endif