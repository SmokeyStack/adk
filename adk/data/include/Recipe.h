#ifndef RECIPE_H
#define RECIPE_H

#include <string>

class Recipe {
   private:
    std::string mod_id;

   public:
    Recipe();

    void init();
};

#endif