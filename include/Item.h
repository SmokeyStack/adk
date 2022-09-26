#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "json.hpp"

class Item {
    using json = nlohmann::json;
    json j;

   private:
    int block_light_filter;
    std::string breathability;
    std::string category;
    std::string group;

   public:
    Item(std::string breath, int light = 15) {
        block_light_filter = light;
        breathability = breath;
    }
    std::string getType() { return "blocks/"; };
    json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.19.30";
        j["minecraft:block"]["components"]["block_light_filter"] =
            block_light_filter;
        j["minecraft:block"]["components"]["minecraft:unit_cube"] =
            json::object();
        j["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;
        return j;
    }
    // void simpleBlock(std::string id, bool creative, std::string category,
    // std::string group, int destroy, int explode, std::string colour,
    // std::string texture);
};
#endif
