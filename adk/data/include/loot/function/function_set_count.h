#pragma once

#include <variant>

#include "json.hpp"
#include "loot/function/loot_function.h"

namespace adk {
	/**
	 * @brief Builds the "set_count" loot function.
	 */
	class FunctionSetCount : public LootFunction {
	public:
		nlohmann::json Generate() {
			nlohmann::json output;
			output["function"] = "set_count";

			if (std::holds_alternative<int>(count_))
				output["count"] = std::get<int>(count_);
			else
				output["count"] = { {"min", std::get<std::pair<int, int>>(count_).first},{"max", std::get<std::pair<int, int>>(count_).second} };

			return output;
		}

		FunctionSetCount set(int count) {
			count_ = count;

			return *this;
		}

		FunctionSetCount set(int min, int max) {
			count_ = std::make_pair(min, max);

			return *this;
		}
	private:
		std::variant<int, std::pair<int, int>> count_;
	};
}