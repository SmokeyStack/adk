#include "language.h"

#include "registry_global.h"

namespace adk {
	Language::Language(std::string id, std::string locale) {
		mod_id = id;
		this->locale = locale;
	}

	void Language::init() { createLangFile(); }
} // namespace adk