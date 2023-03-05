#ifndef OBJECT_H
#define OBJECT_H

#include <string>

class Object {
   private:
    std::string mod_id;

   public:
    Object(std::string id);

    void init();
};

#endif