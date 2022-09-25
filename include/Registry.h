#ifndef REGISTRY_H
#define REGISTRY_H

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

template <typename T>
class Registry {
   private:
    std::string mod_id;

   public:
    Registry(std::string id) { mod_id = id; };
    void reg(std::string id, T* object) {
        if (!fs::exists("./packs/BP/" + object->getType())) {
            fs::create_directory("./packs/BP/" + object->getType());
        }
        std::ofstream MyJson("./packs/BP/" + object->getType() + id + ".json");
        MyJson << object->output(mod_id, id).dump(4);
        MyJson.close();
    };
};

#endif  // REGISTRY_H