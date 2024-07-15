#include "block/component/tag.h"

namespace adk {
	nlohmann::json::object_t ComponentBlockTag::Generate() {
		nlohmann::json::object_t output;

		for (const auto& tag : tags_)
			output["tag:" + tag] = nlohmann::json::object();

		return output;
	}
	std::string ComponentBlockTag::GetType() { return "minecraft:tags"; }
	ComponentBlockTag& ComponentBlockTag::Add(std::string tag) {
		tags_.insert(tag);

		return *this;
	}
	ComponentBlockTag& ComponentBlockTag::Add(std::set<std::string> tags) {
		for (const auto& tag : tags)
			tags_.insert(tag);

		return *this;
	}
	ComponentBlockTag& ComponentBlockTag::Remove(std::string tag) {
		tags_.erase(tag);

		return *this;
	}
} // namespace adk