#include "Language.h"

#include "GlobalRegistry.h"

Language::Language(std::string id, std::string locale) {
    mod_id = id;
    this->locale = locale;
}

void Language::init() { createLangFile(); }