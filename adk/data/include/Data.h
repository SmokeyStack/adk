#pragma once

#include <string>

namespace adk {
	class Data {
	private:
		std::string mod_id;

	public:
		Data();

		void init();
	};
}  // namespace adk