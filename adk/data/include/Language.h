#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <string>

#include "builder_language.h"

class Language : public LanguageBuilder {
   public:
    Language(std::string id, std::string locale);

    void init();
};

#endif