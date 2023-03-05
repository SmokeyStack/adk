#include "Object.h"
#include "Recipe.h"

int main() {
    Object SmokeyBedrock("custom_namespace");
    Recipe recipe;

    SmokeyBedrock.init();
    recipe.init();

    return 0;
}