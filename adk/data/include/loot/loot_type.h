#include <string>

namespace adk {
	class LootType {
	public:
		static std::string ITEM;
		static std::string LOOT_TABLE;
		static std::string EMPTY;
	};
	std::string LootType::ITEM = "item";
	std::string LootType::LOOT_TABLE = "loot_table";
	std::string LootType::EMPTY = "empty";
} // namespace adk