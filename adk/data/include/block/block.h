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
		/**
		 * @brief Returns the type of the object
		 *
		 * @return std::string
		 */
		std::string GetType() { return "block"; };

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
			output_["format_version"] = "1.20.80";
			output_["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;
			nlohmann::json temp;

			if (internal_.GetLightDampening() != 15)
				output_["minecraft:block"]["components"].update(
					helper_.LightDampening(
						internal_.GetLightDampening(), id
					)
				);

			temp = internal_.GetCrafting();
			if (temp["crafting_tags"].size() > 64) {
				log::error("Crafting tags for block {} cannot exceed the limit of 64 tags.", id);
				exit(EXIT_FAILURE);
			}

			if (!temp["crafting_tags"].empty())
				output_["minecraft:block"]["components"].update(
					helper_.Crafting(internal_.GetCrafting())
				);

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

			if (!internal_.GetDisplayName().empty())
				output_["minecraft:block"]["components"].update(
					helper_.DisplayName(
						internal_.GetDisplayName()
					)
				);

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

			if (internal_.GetFriction() != 0.4)
				output_["minecraft:block"]["components"].update(
					helper_.Friction(internal_.GetFriction(), id)
				);

			if (internal_.GetLightEmission() != 0)
				output_["minecraft:block"]["components"].update(
					helper_.LightEmission(internal_.GetLightEmission(), id)
				);

			if (!internal_.GetLoot().empty())
				output_["minecraft:block"]["components"].update(
					helper_.Loot(internal_.GetLoot())
				);

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

			if (!internal_.GetPlacementFilter().allowed_faces.empty())
				output_["minecraft:block"]["components"].update(
					helper_.PlacementFilter(internal_.GetPlacementFilter())
				);

			if (!internal_.GetTags().empty()) {
				for (auto& tag : internal_.GetTags()) {
					output_["minecraft:block"]["components"]["tag:" + tag] = nlohmann::json::object();
				}
			}

			if (!internal_.GetCustomComponents().empty())
				output_["minecraft:block"]["components"].update(helper_.CustomComponents(internal_.GetCustomComponents()));

			if (internal_.GetTick().has_value()) {
				const auto& [first, second, third] = internal_.GetTick().value();
				output_["minecraft:block"]["components"].update(
					helper_.Tick(first, second, third)
				);
			}

			return output_;
		}
	protected:
		BlockProperty internal_;
		BlockComponent helper_;
		nlohmann::json output_;
	};
} // namespace adk