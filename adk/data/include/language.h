#pragma once

#include <string>

#include "builder_language.h"
namespace adk {
	class Language : public LanguageBuilder {
	public:
		Language(std::string id, std::string locale);

		void init();
	};
} // namespace adk
