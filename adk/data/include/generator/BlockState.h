#ifndef BLOCKSTATE_H
#define BLOCKSTATE_H

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "json.hpp"

namespace fs = std::filesystem;

/**
 * @brief Creates a one texture block
 *
 * @param block Identifier of the block, omit namespace
 * @param texture Name of the texture defined in `terrain_texture.json`
 */
void simpleBlock(std::string block, std::string texture) {
    std::string my_text, temp_text;

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
                "No block found: {}.json - Please check if this block exists",
                block);
        exit(EXIT_FAILURE);
    }

    std::ifstream TempFile("./BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["texture"] = texture;
    j["minecraft:block"]["components"]["minecraft:unit_cube"] =
        nlohmann::json::object();

    TempFile.close();
    std::ofstream MyFile("./BP/blocks/" + block + ".json");
    MyFile << j.dump();
    MyFile.close();
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

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./RP/models/entity/head.geo.json")) {
        if (!fs::exists("./RP/models/entity")) {
            fs::create_directory("./RP/models/");
            fs::create_directory("./RP/models/entity/");
        }

        fs::copy("./data/adk/assets/head.geo.json", "./RP/models/entity");
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

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./RP/models/entity/head.geo.json")) {
        if (!fs::exists("./RP/models/entity")) {
            fs::create_directory("./RP/models/");
            fs::create_directory("./RP/models/entity/");
        }

        fs::copy("./data/adk/assets/head.geo.json", "./RP/models/entity");
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

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./RP/models/entity/head.geo.json")) {
        if (!fs::exists("./RP/models/entity")) {
            fs::create_directory("./RP/models/");
            fs::create_directory("./RP/models/entity/");
        }

        fs::copy("./data/adk/assets/head.geo.json", "./RP/models/entity");
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

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./RP/models/entity/candle.geo.json")) {
        if (!fs::exists("./RP/models/entity")) {
            fs::create_directory("./RP/models/");
            fs::create_directory("./RP/models/entity/");
        }

        fs::copy("./data/adk/assets/candle.geo.json", "./RP/models/entity");
    }
}

/**
 * @brief Creates a slab block
 *
 * @param block Identifier of the block, omit namespace
 * @param texture Name of the texture defined in `terrain_texture.json`
 */
void slabBlock(std::string block, std::string texture) {
    std::string my_text, temp_text;

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
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

    if (!fs::exists("./RP/models/entity/slab.geo.json")) {
        if (!fs::exists("./RP/models/entity")) {
            fs::create_directory("./RP/models/");
            fs::create_directory("./RP/models/entity/");
        }

        fs::copy("./data/adk/assets/slab.geo.json", "./RP/models/entity");
    }
}

/**
 * @brief Creates a cross block
 *
 * @param block Identifier of the block, omit namespace
 * @param texture Name of the texture defined in `terrain_texture.json`
 */
void crossBlock(std::string block, std::string texture) {
    std::string my_text, temp_text;

    if (!fs::exists("./BP/blocks/" + block + ".json")) {
        spdlog::get("Data Generator")
            ->error(
                "No block found: {}.json - Please check if this block exists",
                block);
        exit(EXIT_FAILURE);
    }

    std::ifstream TempFile("./BP/blocks/" + block + ".json");
    nlohmann::json j = nlohmann::json::parse(TempFile);

    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["texture"] = texture;
    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["render_method"] = "alpha_test";
    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["ambient_occlusion"] = false;
    j["minecraft:block"]["components"]["minecraft:material_instances"]["*"]
     ["face_dimming"] = false;
    j["minecraft:block"]["components"]["minecraft:geometry"] = "geometry.cross";

    TempFile.close();
    std::ofstream MyFile("./BP/blocks/" + block + ".json");
    MyFile << j.dump();
    MyFile.close();

    if (!fs::exists("./RP/models/entity/cross.geo.json")) {
        if (!fs::exists("./RP/models/entity")) {
            fs::create_directory("./RP/models/");
            fs::create_directory("./RP/models/entity/");
        }

        fs::copy("./data/adk/assets/cross.geo.json", "./RP/models/entity");
    }
}

#endif