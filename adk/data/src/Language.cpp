#include "Language.h"

#include "registry_global.h"

Language::Language(std::string id, std::string locale) {
    mod_id = id;
    this->locale = locale;
}

void Language::init() { createLangFile(); }