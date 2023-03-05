#include "Data.h"
#include "Object.h"
#include "Recipe.h"

int main() {
    Object MyAddOn("custom_namespace");
    Data DataGenerator;
    Recipe RecipeGenerator;

    MyAddOn.init();
    DataGenerator.init();
    RecipeGenerator.init();

    return 0;
}