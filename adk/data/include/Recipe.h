#pragma once

#include <string>

namespace adk {
	class Recipe {
	private:
		std::string mod_id;

	public:
		Recipe();

		void init();
	};
}  // namespace adk