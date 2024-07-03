#include "block/block.h"

#include "utility/logger.h"

namespace adk {
	std::string Block::GetType() { return "block"; }
	nlohmann::json Block::Generate(std::string mod_id, std::string id) {
		nlohmann::json output;
		output["format_version"] = "1.21.10";
		auto& block = output["minecraft:block"];
		block["description"]["identifier"] = mod_id + ":" + id;
		block["components"] = nlohmann::json::object();
		auto& description = block["description"];

		for (const auto& component : components_) {
			try {
				block["components"].update(component->Generate());
			}
			catch (const std::exception& error) {
				log::error("    {}", error.what());
				exit(EXIT_FAILURE);
			}
		}
		for(const auto& permutation : permutations_) {
			try {
				block["permutations"].push_back(permutation->Generate());
			}
			catch (const std::exception& error) {
				log::error("    {}", error.what());
				exit(EXIT_FAILURE);
			}
		}
		for (const auto& property : properties_) {
			try {
				description.update(property->Generate());
			}
			catch (const std::exception& error) {
				log::error("    {}", error.what());
				exit(EXIT_FAILURE);
			}
		}

		return output;
	}
	Block& Block::AddComponent(std::unique_ptr<Component> component) {
		components_.insert(std::move(component));

		return *this;
	}
	Block& Block::AddPermutation(std::unique_ptr<Permutation> permutation) {
		permutations_.push_back(std::move(permutation));

		return *this;
	}
	Block& Block::AddProperty(std::unique_ptr<Property> property) {
		properties_.insert(std::move(property));

		return *this;
	}
} // namespace adk