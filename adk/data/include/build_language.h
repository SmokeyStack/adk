#ifndef LANGUAGE_BUILDER_H
#define LANGUAGE_BUILDER_H

#include <filesystem>
#include <fstream>
#include <string>
#include <variant>

#include "GlobalRegistry.h"
#include "Registry.h"
#include "json.hpp"

namespace fs = std::filesystem;

class LanguageBuilder {
   protected:
    std::string mod_id;
    std::string locale;
    std::vector<std::string> entries;

    void add(std::string id, std::string value) {
        for (auto const entry : globalregistry) {
            std::map<std::string, std::variant<Block*, Item*>> registry_check;
            registry_check = entry->getRegistrar();

            for (std::map<std::string, std::variant<Block*, Item*>>::iterator
                     it = registry_check.begin();
                 it != registry_check.end(); ++it) {
                if (it->first == (mod_id + ":" + id)) {
                    if (std::get_if<Block*>(&it->second))
                        entries.push_back("tile." + mod_id + ":" + id +
                                          ".name=" + value);
                    else if (std::get_if<Item*>(&it->second))
                        entries.push_back("tile." + mod_id + ":" + id +
                                          ".name=" + value);

                    break;
                }
            }
        }
    }

    void createLangFile() {
        if (!fs::exists("./RP/texts/")) fs::create_directory("./RP/texts/");

        if (!fs::exists("./RP/texts/" + locale + ".lang")) {
            std::ofstream MyLang("./RP/texts/" + locale + ".lang");

            for (auto const entry : entries) {
                MyLang << entry << '\n';
            }

            MyLang.close();

        } else {
            std::ofstream MyLang("./RP/texts/" + locale + ".lang",
                                 std::ios::app);

            for (auto const entry : entries) {
                MyLang << '\n' << entry;
            }

            MyLang.close();
        }
    }

   public:
    LanguageBuilder(){};
};

#endif