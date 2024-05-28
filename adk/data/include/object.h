#pragma once

#include <string>

namespace adk {
	class Object {
	public:
		Object(std::string id);

		void init();
	private:
		std::string mod_id;
	};
} // namespace adk