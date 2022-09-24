#ifndef REGSITRY_H
#define REGISTRY_H

#include <iostream>
#include <string>
#include <fstream>

template <typename T>
class Registry
{
private:
	std::string mod_id;
public:
	Registry(std::string id) {
		mod_id = id;
	};
	void reg(std::string id, T* object) {
		std::ofstream MyJson("./packs/BP/" + object->getType() + id + ".json");
		MyJson << object->output(mod_id, id).dump(4);
		MyJson.close();
	};
};

#endif // REGSITRY_H