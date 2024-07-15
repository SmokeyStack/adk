#pragma once

#include <set>
#include <string>

#include "block/permutation.h"
#include "block/property.h"
#include "component.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Block
	 */
	class Block {
	public:
		Block() {};

		/**
		 * @brief Returns the type of the object
		 *
		 * @return std::string
		 */
		std::string GetType();

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the block
		 *
		 * @return nlohmann::json
		 */
		virtual nlohmann::json Generate(std::string mod_id, std::string id);
		Block& AddComponent(std::unique_ptr<Component> component);
		Block& AddPermutation(std::unique_ptr<Permutation> permutation);
		Block& AddProperty(std::unique_ptr<Property> property);
	protected:
		std::set<std::unique_ptr<Component>> components_;
		std::vector<std::unique_ptr<Permutation>> permutations_;
		std::set<std::unique_ptr<Property>> properties_;
	};
} // namespace adk