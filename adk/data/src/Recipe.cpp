#include "recipe.h"

#include "registry_global.h"
#include "builder_recipe_shaped.h"

Recipe::Recipe() {}

void Recipe::init() {
    ShapedRecipeBuilder()
        .shaped("custom_namespace:custom_item")
        .pattern("ppp")
        .define('p', "custom_namespace:custom_block")
        .save("custom_recipe");
}