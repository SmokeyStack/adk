#include "Data.h"
#include "Object.h"
#include "Recipe.h"

int main() {
    Object SmokeyBedrock("custom_namespace");
    Data DataGenerator;
    Recipe RecipeGenerator;

    SmokeyBedrock.init();
    DataGenerator.init();
    RecipeGenerator.init();

    return 0;
}