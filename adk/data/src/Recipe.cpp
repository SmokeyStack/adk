#include "recipe.h"

#include "builder_recipe_shaped.h"
#include "registry_global.h"

namespace adk {
	Recipe::Recipe() {}

	void Recipe::init() {
		ShapedRecipeBuilder()
			.shaped("custom_namespace:custom_item")
			.pattern("ppp")
			.define('p', "custom_namespace:custom_block")
			.save("custom_recipe");
	}
} // namespace adk