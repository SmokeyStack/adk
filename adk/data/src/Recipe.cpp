#include "Recipe.h"

#include "GlobalRegistry.h"
#include "ShapedRecipeBuilder.h"

Recipe::Recipe() {}

void Recipe::init() {
    ShapedRecipeBuilder()
        .shaped("custom_namespace:custom_item")
        .pattern("ppp")
        .define('p', "custom_namespace:custom_block")
        .save("custom_recipe");
}