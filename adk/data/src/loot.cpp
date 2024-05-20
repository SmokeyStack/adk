#include "loot.h"

#include "loot/builder_loot.h"

namespace adk {
	Loot::Loot() {}

	void Loot::init() {
		BuilderLoot()
			.pool(LootPool().with(
				LootEntry()
				.type(LootType::ITEM)
				.entry("minecraft:diamond")
				.apply(&FunctionSetCount().set(5, 10))));
	}
} // namespace adk