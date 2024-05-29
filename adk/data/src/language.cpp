#include "language.h"

#include "builder_language.h"

namespace adk {
	Language::Language() {}

	void Language::init() {
		BuilderLanguage("en_US").Add("adk:adk", "ADK").Build();
	}
} // namespace adk