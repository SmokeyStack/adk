#include "recipe.h"

#include "recipe/builder_recipe_shaped.h"
#include "recipe/builder_recipe_shapeless.h"
#include "recipe/unlock_context.h"
#include "registry_global.h"

namespace adk {
	Recipe::Recipe(std::string id) { mod_id = id; }

	void Recipe::init() {
        ShapedRecipeBuilder(mod_id)
            .Shaped("minecraft:bedrock")
            .Pattern("ppp")
            .Define('p', "minecraft:dirt")
            .Unlock(RecipeUnlockContext::ALWAYS_UNLOCKED)
            .Tags({ "crafting_table" })
            .Build("custom_shaped_recipe");
        ShapelessRecipeBuilder(mod_id)
            .Shapeless("minecraft:bedrock")
            .Ingredients("minecraft:dirt", 3)
            .Unlock(RecipeUnlockContext::ALWAYS_UNLOCKED)
            .Tags({ "crafting_table" })
            .Build("custom_shapeless_recipe");
	}
} // namespace adk