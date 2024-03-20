#pragma once

#include <string>

#include "block_component.h"
#include "block_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Block
	 */
	class Block {
	public:
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
		 * @param id Identifier for the block
		 *
		 * @return nlohmann::json
		 */
		virtual nlohmann::json Generate(std::string mod_id, std::string id) {
			output_["format_version"] = "1.20.60";
			output_["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;

			// Registering "light_dampening" component
			if (internal_.GetLightDampening() != 15)
				output_["minecraft:block"]["components"].update(
					helper_.LightDampening(
						internal_.GetLightDampening(), id
					)
				);

			// Registering "crafting_table" component
			if (internal_.GetCrafting().has_value())
				output_["minecraft:block"]["components"].update(
					helper_.Crafting(
						internal_.GetCrafting().value().first,
						internal_.GetCrafting().value().second
					)
				);

			// Registering "destructible_by_explosion" component
			if (std::get_if<bool>(&internal_.GetDestructibleByExplosion())) {
				if (!std::get<bool>(internal_.GetDestructibleByExplosion()))
					output_["minecraft:block"]["components"].update(
						helper_.DestructibleByExplosion(false)
					);
			}
			else if (std::get_if<double>(&internal_.GetDestructibleByExplosion()))
				output_["minecraft:block"]["components"].update(
					helper_.DestructibleByExplosion(
						std::get<double>(internal_.GetDestructibleByExplosion())
					)
				);

			// Registering "destructible_by_mining" component
			if (std::get_if<bool>(&internal_.GetDestructibleByMining())) {
				if (!std::get<bool>(internal_.GetDestructibleByMining()))
					output_["minecraft:block"]["components"].update(
						helper_.DestructibleByMining(false)
					);
			}
			else if (std::get_if<double>(&internal_.GetDestructibleByMining()))
				output_["minecraft:block"]["components"].update(
					helper_.DestructibleByMining(
						std::get<double>(internal_.GetDestructibleByMining())
					)
				);

			// Registering "display_name" component
			if (!internal_.GetDisplayName().empty())
				output_["minecraft:block"]["components"].update(
					helper_.DisplayName(
						internal_.GetDisplayName()
					)
				);

			// Registering "flammable" component
			if (std::get_if<bool>(&internal_.GetFlamamble())) {
				if (!std::get<bool>(internal_.GetFlamamble()))
					output_["minecraft:block"]["components"].update(
						helper_.Flammable(false)
					);
			}
			else if (std::get_if<std::pair<int, int>>(&internal_.GetFlamamble()))
				output_["minecraft:block"]["components"].update(
					helper_.Flammable(
						std::get<std::pair<int, int>>(internal_.GetFlamamble()).first,
						std::get<std::pair<int, int>>(internal_.GetFlamamble()).second
					)
				);

			// Registering "friction" component
			if (internal_.GetFriction() != 0.4)
				output_["minecraft:block"]["components"].update(
					helper_.Friction(internal_.GetFriction(), id)
				);

			// Registering "light_emission" component
			if (internal_.GetLightEmission() != 0)
				output_["minecraft:block"]["components"].update(
					helper_.LightEmission(internal_.GetLightEmission(), id)
				);

			// Registering "loot" component
			if (!internal_.GetLoot().empty())
				output_["minecraft:block"]["components"].update(
					helper_.Loot(internal_.GetLoot())
				);

			// Registering "map_color" component
			if (std::get_if<std::string>(&internal_.GetMapColor())) {
				if (!std::get<std::string>(internal_.GetMapColor()).empty())
					output_["minecraft:block"]["components"].update(
						helper_.MapColor(
							std::get<std::string>(internal_.GetMapColor())
						)
					);
			}
			else if (std::get_if<std::vector<int>>(&internal_.GetMapColor()))
				output_["minecraft:block"]["components"].update(
					helper_.MapColor(
						std::get<std::vector<int>>(internal_.GetMapColor())
					)
				);

			// Registering "transformation" component
			if (internal_.GetRotation() != std::vector<int>{0, 0, 0})
				output_["minecraft:block"]["components"].update(
					helper_.Rotation(internal_.GetRotation(), id)
				);

			if (internal_.GetTranslation() != std::vector<double>{0, 0, 0})
				output_["minecraft:block"]["components"].update(
					helper_.Translation(internal_.GetTranslation())
				);

			if (internal_.GetScale() != std::vector<double>{0, 0, 0})
				output_["minecraft:block"]["components"].update(
					helper_.Scale(internal_.GetScale())
				);

			// Registering "collision_box" component
			if (std::get_if<bool>(&internal_.GetBoxCollision())) {
				if (!std::get<bool>(internal_.GetBoxCollision()))
					output_["minecraft:block"]["components"].update(
						helper_.BoxCollision(false)
					);
			}
			else if (std::get_if<std::pair<std::vector<int>, std::vector<int>>>(&internal_.GetBoxCollision())) {
				output_["minecraft:block"]["components"].update(
					helper_.BoxCollision(
						std::get<std::pair<std::vector<int>, std::vector<int>>>(internal_.GetBoxCollision()).first,
						std::get<std::pair<std::vector<int>, std::vector<int>>>(internal_.GetBoxCollision()).second,
						id
					)
				);
			}

			// Registering "selection_box" component
			if (std::get_if<bool>(&internal_.GetBoxSelection())) {
				if (!std::get<bool>(internal_.GetBoxSelection()))
					output_["minecraft:block"]["components"].update(
						helper_.BoxSelection(false)
					);
			}
			else if (std::get_if<std::pair<std::vector<int>, std::vector<int>>>(&internal_.GetBoxSelection())) {
				output_["minecraft:block"]["components"].update(
					helper_.BoxSelection(
						std::get<std::pair<std::vector<int>, std::vector<int>>>(internal_.GetBoxSelection()).first,
						std::get<std::pair<std::vector<int>, std::vector<int>>>(internal_.GetBoxSelection()).second,
						id
					)
				);
			}

			// Registering creative menu
			if (!adk::GetCreativeGroup(internal_.GetCreativeGroup()).empty())
				output_["minecraft:block"]["description"].update(
					helper_.CreativeMenu(
						adk::GetCreativeCategory(internal_.GetCreativeCategory()),
						adk::GetCreativeGroup(internal_.GetCreativeGroup())
					)
				);
			else
				output_["minecraft:block"]["description"].update(
					helper_.CreativeMenu(
						adk::GetCreativeCategory(internal_.GetCreativeCategory())
					)
				);

			// Registering Placemt Filter
			if (!internal_.GetPlacementFilter().allowed_faces.empty())
				output_["minecraft:block"]["components"].update(
					helper_.PlacementFilter(internal_.GetPlacementFilter())
				);

			return output_;
		}
	protected:
		BlockProperty internal_;
		BlockComponent helper_;
		nlohmann::json output_;
	};
} // namespace adk