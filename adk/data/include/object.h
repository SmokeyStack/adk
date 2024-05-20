#pragma once

#include <string>

namespace adk {
	class Object {
	private:
		std::string mod_id;

	public:
		Object(std::string id);

		void init();
	};
} // namespace adk