#pragma once

#include <string>

namespace adk {
	enum class RecipeUnlockContext {
		ALWAYS_UNLOCKED,
		PLAYER_IN_WATER,
		PLAYER_HAS_MANY_ITEMS
	};

	inline std::string GetRecipeUnlockContext(RecipeUnlockContext context) {
		switch (context) {
			case RecipeUnlockContext::ALWAYS_UNLOCKED: return "AlwaysUnlocked";
			case RecipeUnlockContext::PLAYER_IN_WATER: return "PlayerInwater";
			case RecipeUnlockContext::PLAYER_HAS_MANY_ITEMS: return "PlayerHasManyItems";
		}
	}
} // namespace adk