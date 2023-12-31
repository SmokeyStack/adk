#pragma once

#include <spdlog/spdlog.h>

#include <string>

#include "block_component.h"
#include "block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Block
	 */
	class Block {
	protected:
		BlockProperty internal_;
		BlockComponent helper_;

	public:
		nlohmann::json output;
		std::string getType() { return "block"; };

		Block() {};
		/**
		 * @brief Construct a new Block object
		 *
		 * @param property BlockProperty
		 */
		Block(BlockProperty property) { internal_ = property; }

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 * 
		 * @param id Identifier for the item
		 * 
		 * @return json
		 */
		virtual nlohmann::json Generate(std::string mod_id, std::string id) {
			output["format_version"] = "1.20.50";
			output["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;

			if (internal_.getBlockLightFilter() != 15)
				output["minecraft:block"]["components"].update(
					helper_.LightDampening(internal_.getBlockLightFilter(), id));

			if (internal_.getCrafting().has_value())
				output["minecraft:block"]["components"].update(
					helper_.Crafting(internal_.getCrafting().value()));

			if (std::get_if<bool>(&internal_.getExplosion())) {
				if (!std::get<bool>(internal_.getExplosion()))
					output["minecraft:block"]["components"].update(
						helper_.destructibleByExplosion(false));
			}
			else if (std::get_if<double>(&internal_.getExplosion()))
				output["minecraft:block"]["components"].update(
					helper_.destructibleByExplosion(
						std::get<double>(internal_.getExplosion())));

			if (std::get_if<bool>(&internal_.getMining())) {
				if (!std::get<bool>(internal_.getMining()))
					output["minecraft:block"]["components"].update(
						helper_.DestructibleByMining(false));
			}
			else if (std::get_if<double>(&internal_.getMining()))
				output["minecraft:block"]["components"].update(
					helper_.DestructibleByMining(
						std::get<double>(internal_.getMining())));

			if (!internal_.getName().empty())
				output["minecraft:block"]["components"].update(
					helper_.DisplayName(internal_.getName()));

			if (internal_.getFlamamble().has_value())
				output["minecraft:block"]["components"].update(
					helper_.Flammable(internal_.getFlamamble().value()));

			if (internal_.getFriction() != 0.4)
				output["minecraft:block"]["components"].update(
					helper_.Friction(internal_.getFriction(), id));

			if (internal_.getLightEmission() != 0)
				output["minecraft:block"]["components"].update(
					helper_.LightEmission(internal_.getLightEmission(), id));

			if (!internal_.getLoot().empty())
				output["minecraft:block"]["components"].update(
					helper_.Loot(internal_.getLoot()));

			if (!internal_.getColor().empty())
				output["minecraft:block"]["components"].update(
					helper_.MapColor(internal_.getColor()));

			if (internal_.getRotation() != std::vector<int>{0, 0, 0})
				output["minecraft:block"]["components"].update(
					helper_.Rotation(internal_.getRotation(), id));

			if (internal_.getTranslation() != std::vector<double>{0, 0, 0})
				output["minecraft:block"]["components"].update(
					helper_.Translation(internal_.getTranslation()));

			if (internal_.getScale() != std::vector<double>{0, 0, 0})
				output["minecraft:block"]["components"].update(
					helper_.Scale(internal_.getScale()));

			if (std::get_if<bool>(&internal_.getCollision())) {
				if (!std::get<bool>(internal_.getCollision()))
					output["minecraft:block"]["components"].update(
						helper_.CollisionBox(false, id));

			}
			else if (std::get_if<std::pair<std::vector<int>, std::vector<int>>>(
				&internal_.getCollision())) {
				output["minecraft:block"]["components"].update(
					helper_.CollisionBox(internal_.getCollision(), id));
			}

			if (std::get_if<bool>(&internal_.getSelection())) {
				if (!std::get<bool>(internal_.getSelection()))
					output["minecraft:block"]["components"].update(
						helper_.selection(false, id));

			}
			else if (std::get_if<std::pair<std::vector<int>, std::vector<int>>>(
				&internal_.getSelection())) {
				output["minecraft:block"]["components"].update(
					helper_.selection(internal_.getSelection(), id));
			}

			if (internal_.getCreative().has_value())
				output["minecraft:block"]["description"].update(
					helper_.CreativeMenu(internal_.getCreative().value()));

			return output;
		}
	};
} // namespace adk