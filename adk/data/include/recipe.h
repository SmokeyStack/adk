#pragma once

#include <string>

namespace adk {
	class Recipe {
	public:
		Recipe(std::string id);

		void init();
	private:
		std::string mod_id;
	};
}  // namespace adk