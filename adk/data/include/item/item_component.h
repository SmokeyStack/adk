#pragma once

#include <string>
#include <variant>
#include <vector>

#include "json.hpp"
#include "utility/logger.h"

namespace adk {
	/**
	 * @brief Creates the json components
	 */
	class ItemComponent {
	public:
		/**
		 * @brief Creates the "allow_off_hand" component
		 *
		 * @param value Whether the item can be placed in the off hand slot.
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t AllowOffHand(bool value) {
			nlohmann::json::object_t temp = { {"minecraft:allow_off_hand", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "block_placer" component
		 *
		 * @param value Defines the block that will be placed.
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t PlacerBlock(std::string value) {
			nlohmann::json::object_t temp = {
				{"minecraft:block_placer", {{"block", value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "block_placer" component
		 *
		 * @param block Defines the block that will be placed.
		 *
		 * @param used_on List of block descriptors that contain blocks that this item can be used on.
		 * If left empty, all blocks will be allowed.
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t PlacerBlock(std::string block, std::vector<std::string> use_on) {
			nlohmann::json::object_t temp = {
				{"minecraft:block_placer",
				 {{"block", block}, {"use_on", use_on}}} };

			return temp;
		}

		/**
		 * @brief Creates the "can_destroy_in_creative" component
		 *
		 * @param value Defines whether the item can destroy blocks while in creative.
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t CanDestroyInCreative(bool value) {
			nlohmann::json::object_t temp = { {"minecraft:can_destroy_in_creative", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "cooldown" component
		 *
		 * @param category The type of cool down for this item.
		 *
		 * @param duration_seconds The duration of time (in seconds) items with a matching category will spend cooling down before becoming usable again.
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t Cooldown(std::string category, double duration_seconds) {
			nlohmann::json::object_t temp = {
				{"minecraft:cooldown",
				 {{"category", category}, {"duration", duration_seconds}}} };

			return temp;
		}

		/**
		 * @brief Sets the "custom_components" component
		 *
		 * @param value Array of custom components
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t CustomComponents(std::vector<std::string> value) {
			nlohmann::json::object_t temp = { {"minecraft:custom_components",value} };

			return temp;
		}

		/**
		 * @brief Creates the "damage" component
		 *
		 * @param value How much extra damage the item does on attack.
		 * Note that this must be a positive value.
		 *
		 * @param id Identifier of the item
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t Damage(int value, std::string id) {
			if (value < 0) {
				log::error("{} - Damage can only be a positive value", id);

				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t temp = { {"minecraft:damage", {{"value",value}}} };

			return temp;
		}

		nlohmann::json::object_t Digger(nlohmann::json j) {
			nlohmann::json::object_t temp = { {"minecraft:digger", j} };

			return temp;
		}

		/**
		 * @brief Creates the "display_name" component
		 *
		 * @param value Set the display name for an item.
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t DisplayName(std::string value) {
			nlohmann::json::object_t temp = { {"minecraft:display_name", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "durability" component
		 *
		 * @param j ItemDurability struct
		 *
		 * @param id Identifier of the item
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Durability(nlohmann::json j, std::string id) {
			if (j.contains("max_durability")) {
				if (j["max_durability"] < 0) {
					log::error("{} - Max durability can only be a positive value", id);

					exit(EXIT_FAILURE);
				}
			}
			if (j.contains("damage_chance")) {
				if (j["damage_chance"]["min"] < 0) {
					log::error("{} - Min damage chance can only be a positive value", id);

					exit(EXIT_FAILURE);
				}

				if (j["damage_chance"]["max"] > 100) {
					log::error("{} - Max damage chance cannot exceed 100", id);

					exit(EXIT_FAILURE);
				}

				if (j["damage_chance"]["min"] > j["damage_chance"]["max"]) {
					log::error("{} - Min damage chance cannot exceed max damage chance", id);

					exit(EXIT_FAILURE);
				}
			}

			nlohmann::json::object_t temp = { {"minecraft:durability", {j}} };

			return temp;
		}

		/**
		 * @brief Creates the "enchantable" component
		 *
		 * @param slot What enchantments can be applied (ex. Using bow would allow this item to be enchanted as if it were a bow).
		 *
		 * @param value The value of the enchantment (minimum of 0).
		 *
		 * @param id Identifier of the item
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Enchantable(std::string slot, int value, std::string id) {
			if (value < 0) {
				log::error("{} - The value of the enchantment can only be a positive value", id);

				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t temp = { {"minecraft:enchantable", {{"slot", slot}, {"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "entity_placer" component
		 *
		 * @param j ItemPlacerEntity struct
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t PlacerEntity(nlohmann::json j) {
			nlohmann::json::object_t temp = { {"minecraft:entity_placer", {j}} };

			return temp;
		}

		/**
		 * @brief Creates the "food" component
		 *
		 * @param j ItemFood struct
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Food(nlohmann::json j) {
			nlohmann::json::object_t temp = { {"minecraft:food",{j}} };

			return temp;
		}

		/**
		 * @brief Creates the "fuel" component
		 *
		 * @param value How long in seconds will this fuel cook items for.
		 * Minimum value: 0.05.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Fuel(double value, std::string id) {
			if (value < 0.05) {
				log::error("{} - The fuel duration must be a minimum of 0.05", id);

				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t temp = { {"minecraft:fuel", {{"duration",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "glint" component
		 *
		 * @param value Whether the item has the enchanted glint render effect.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Glint(bool value) {
			nlohmann::json::object_t temp = { {"minecraft:glint", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "hand_equipped" component
		 *
		 * @param value Determines if the item is rendered like a tool in-hand.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t HandEquipped(bool value) {
			nlohmann::json::object_t temp = { {"minecraft:hand_equipped", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "hover_text_color" component
		 *
		 * @param value The color of the item hover text.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t HoverTextColor(std::string value) {
			nlohmann::json::object_t temp = { {"minecraft:hover_text_color", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "interact_button" component
		 *
		 * @param value What text is displayed on the button
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t InteractButton(std::variant<bool, std::string> value) {
			nlohmann::json::object_t temp;

			if (std::holds_alternative<std::string>(value)) {
				temp = { {"minecraft:interact_button", {{"value",std::get<std::string>(value)}}} };
			}
			else if (std::holds_alternative<bool>(value)) {
				temp = { {"minecraft:interact_button", {{"value",std::get<bool>(value)}}} };
			}

			return temp;
		}

		/**
		 * @brief Creates the "liquid_clipped" component
		 *
		 * @param value Whether an item interacts with liquid blocks on use.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t LiquidClipped(bool value) {
			nlohmann::json::object_t temp = { {"minecraft:liquid_clipped", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "max_stack_size" component
		 *
		 * @param value How many of an item that can be stacked together.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t MaxStackSize(int value) {
			nlohmann::json::object_t temp = { {"minecraft:max_stack_size", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "projectile" component
		 *
		 * @param projectile_entity The entity to be fired as a projectile.
		 *
		 * @param minimum_critical_power Defines the time a projectile needs to charge in order to critically hit.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Projectile(std::string projectile_entity, double minimum_critical_power = 0.0) {
			nlohmann::json::object_t temp = { {"minecraft:projectile",
				{{"projectile_entity", projectile_entity},
				{"minimum_critical_power",minimum_critical_power}}} };

			return temp;
		}

		/**
		 * @brief Creates the "record" component
		 *
		 * @param j ItemRecord struct
		 *
		 * @param id Identifier of the item
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Record(nlohmann::json j, std::string id) {
			if (j.contains("comparator_signal")) {
				int comparator_signal = j["comparator_signal"];

				if (comparator_signal > 15 || comparator_signal < 1) {
					log::error("{} - comparator_signal can only be in range (0-15)", id);

					exit(EXIT_FAILURE);
				}
			}

			nlohmann::json::object_t temp = { {"minecraft:record",{j}} };

			return temp;
		}

		/**
		 * @brief Creates the "record" component
		 *
		 * @param j ItemRepairable struct
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Repairable(nlohmann::json j) {
			nlohmann::json::object_t temp = { {"minecraft:repairable",{j}} };

			return temp;
		}

		/**
		 * @brief Creates the "shooter" component
		 *
		 * @param j ItemShooter struct
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Shooter(nlohmann::json j) {
			nlohmann::json::object_t temp = { {"minecraft:shooter", j} };

			return temp;
		}

		/**
		 * @brief Creates the "should_despawn" component
		 *
		 * @param value Sets whether the item should eventually despawn while floating in the world.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t ShouldDespawn(bool value) {
			nlohmann::json::object_t temp = { {"minecraft:should_despawn", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "stacked_by_data" component
		 *
		 * @param value Sets whether the same item with different aux values can stack and merge while floating in the world.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t StackedByData(bool value) {
			nlohmann::json::object_t temp = { {"minecraft:stacked_by_data", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "tags" component
		 *
		 * @param value An array which can contain multiple item tags.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Tags(std::vector<std::string> value) {
			nlohmann::json::object_t temp = { {"minecraft:tags", {{"tags",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "throwable" component
		 *
		 * @param j ItemThrowable struct
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Throwable(nlohmann::json j) {
			nlohmann::json::object_t temp = { {"minecraft:throwable",{j} } };

			return temp;
		}

		/**
		 * @brief Creates the "use_animation" component
		 *
		 * @param value Which animation to play when using an item.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t UseAnimation(std::string value) {
			nlohmann::json::object_t temp = { {"minecraft:use_animation", {{"value",value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "use_modifiers" component
		 *
		 * @param use_duration_seconds How long the item takes to use in seconds.
		 *
		 * @param movement_modifier Modifier value to scale the players movement speed when item is in use.
		 *
		 * @param id Identifier of the item
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t UseModifiers(double use_duration_seconds, double movement_modifier, std::string id) {
			if (movement_modifier < 0 || movement_modifier >1) {
				log::error("{} - movement_modifier can only be from 0-1", id);

				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t temp = { {"minecraft:use_modifiers",
				{{"use_duration", use_duration_seconds},
				{"movement_modifier", movement_modifier}}} };

			return temp;
		}

		/**
		 * @brief Creates the "wearable" component
		 *
		 * @param slot Determines where the item can be worn.
		 * If any non-hand slot is chosen, the max stack size is set to 1.
		 *
		 * @param protection How much protection the wearable has.
		 *
		 * @param id Identifier of the item
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Wearable(std::string slot, int protection, std::string id) {
			if (protection < 0) {
				log::error("{} - Protection can only be a positive value", id);

				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t temp = { {"minecraft:wearable",{{"slot",slot}}} };

			if (protection != 0)
				temp["minecraft:wearable"]["protection"] = protection;

			return temp;
		}
	};
} // namespace adk