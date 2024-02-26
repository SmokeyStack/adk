#pragma once

#include <string>
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
		 * @param value Whether the item can be placed in the off-hand slot.
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t AllowOffHand(bool value) {
			nlohmann::json::object_t temp = { {"minecraft:allow_off_hand", value} };

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
				 {{"block", block}, {"used_on", use_on}}} };

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
			nlohmann::json::object_t temp = { {"minecraft:can_destroy_in_creative", value} };

			return temp;
		}

		/**
		 * @brief Creates the "cooldown" component
		 *
		 * @param category The type of cool down for this item.
		 *
		 * @param duration The duration of time (in seconds) items with a matching category will spend cooling down before becoming usable again.
		 *
		 * @return nlohmann::json::object_t
		 */
		nlohmann::json::object_t Cooldown(std::string category, float duration) {
			nlohmann::json::object_t temp = {
				{"minecraft:cooldown",
				 {{"category", category}, {"duration", duration}}} };

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

			nlohmann::json::object_t temp = { {"minecraft:damage", value} };

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
			nlohmann::json::object_t temp = { {"minecraft:display_name", {"value",value}} };

			return temp;
		}

		/**
		 * @brief Creates the "durability" component
		 *
		 * @param durability_max Max durability is the amount of damage that this item can take before breaking.
		 * This is a required parameter with a minimum value of 0.
		 *
		 * @param chance_min Minimum damage chance that the item will take damage.
		 *
		 * @param chance_max Maximum damage chance that the item will take damage.
		 *
		 * @param id Identifier of the item
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Durability(int durability_max, int chance_min, int chance_max, std::string id) {
			if (durability_max < 0) {
				log::error("{} - Max durability can only be a positive value", id);

				exit(EXIT_FAILURE);
			}

			if (chance_min < 0) {
				log::error("{} - Min damage chance can only be a positive value", id);

				exit(EXIT_FAILURE);
			}

			if (chance_max > 100) {
				log::error("{} - Max damage chance cannot exceed 100", id);

				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t temp = { {"minecraft:durability",
				{{"max_durability", durability_max}, {"damage_chance", {{"min", chance_min},{"max", chance_max}}}}} };

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
		 * @param entity The entity to be placed in the world.
		 *
		 * @param dispense_on List of block descriptors that contain blocks that this item can be dispensed on.
		 * If left empty, all blocks will be allowed.
		 *
		 * @param use_on List of block descriptors that contain blocks that this item can be used on.
		 * If left empty, all blocks will be allowed.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t PlacerEntity(std::string entity, std::vector<std::string> dispense_on = {}, std::vector<std::string> use_on = {}) {
			nlohmann::json::object_t temp = { {"minecraft:entity_placer", {{"entity", entity}, {"dispense_on", dispense_on}, {"use_on", use_on}}} };

			return temp;
		}

		/**
		 * @brief Creates the "food" component
		 *
		 * @param can_always_eat If "true" you can always eat this item (even when not hungry).
		 *
		 * @param nutrition The value that is added to the actor's nutrition when the item is used.
		 *
		 * @param saturation_modifier Saturation Modifier is used in this formula: (nutrition * saturation_modifier * 2) when applying the saturation buff.
		 *
		 * @param using_converts_to When used, converts to the item specified by the string in this field.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Food(bool can_always_eat, int nutrition, float saturation_modifier, std::string using_converts_to = "") {
			nlohmann::json::object_t temp = { {"minecraft:food",
				{{"can_always_eat", can_always_eat},
				{"nutrition", nutrition},
				{"saturation_modifier", saturation_modifier},
				{"using_converts_to", using_converts_to}}} };

			return temp;
		}

		/**
		 * @brief Creates the "food" component
		 *
		 * @param can_always_eat If "true" you can always eat this item (even when not hungry).
		 *
		 * @param nutrition The value that is added to the actor's nutrition when the item is used.
		 *
		 * @param saturation_modifier Saturation Modifier is used in this formula: (nutrition * saturation_modifier * 2) when applying the saturation buff.
		 *
		 * @param effects List of effects that are applied when the item is used.
		 *
		 * @param using_converts_to When used, converts to the item specified by the string in this field.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Food(bool can_always_eat, int nutrition, float saturation_modifier, nlohmann::json effects, std::string using_converts_to = "") {
			nlohmann::json::object_t temp = { {"minecraft:food",
					{{"can_always_eat", can_always_eat},
					{"nutrition", nutrition},
					{"saturation_modifier", saturation_modifier},
					{"using_converts_to", using_converts_to},
					{"effects", {effects}}}} };

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
		nlohmann::json::object_t Fuel(float value) {
			nlohmann::json::object_t temp = { {"minecraft:fuel", value} };

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
			nlohmann::json::object_t temp = { {"minecraft:glint", value} };

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
			nlohmann::json::object_t temp = { {"minecraft:hand_equipped", value} };

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
			nlohmann::json::object_t temp = { {"minecraft:hover_text_color", value} };

			return temp;
		}

		/**
		 * @brief Creates the "icon" component
		 *
		 * @param value This map contains the different textures that can be used for the item's icon.
		 * Default will contain the actual icon texture.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Icon(std::string value) {
			nlohmann::json::object_t temp = { {"minecraft:icon", value} };

			return temp;
		}

		/**
		 * @brief Creates the "interact_button" component
		 *
		 * @param value What text is displayed on the button
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t InteractButton(std::string value) {
			nlohmann::json::object_t temp = { {"minecraft:interact_button", value} };

			return temp;
		}

		/**
		 * @brief Creates the "liquid_clipped" component
		 *
		 * @param value Whether an item interacts with liquid blocks on use.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t LiquidClipped(std::string value) {
			nlohmann::json::object_t temp = { {"minecraft:liquid_clipped", value} };

			return temp;
		}

		/**
		 * @brief Creates the "max_stack_size" component
		 *
		 * @param value How many of an item that can be stacked together.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t MaxStackSize(std::string value) {
			nlohmann::json::object_t temp = { {"minecraft:max_stack_size", value} };

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
		nlohmann::json::object_t Projectile(std::string projectile_entity, float minimum_critical_power) {
			nlohmann::json::object_t temp = { {"minecraft:projectile",
				{{"projectile_entity", projectile_entity},
				{"minimum_critical_power",minimum_critical_power}}} };

			return temp;
		}

		/**
		 * @brief Creates the "record" component
		 *
		 * @param comparator_signal Signal strength for comparator blocks to use from 1 - 13.
		 *
		 * @param duration Duration of sound event in seconds float value.
		 *
		 * @param sound_event Sound event types
		 *
		 * @param id Identifier of the item
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Record(int comparator_signal, float duration, std::string sound_event, std::string id) {
			if (comparator_signal > 13 || comparator_signal < 1) {
				adk::log::error("{} - comparator_signal can only be in range (0-15)", id);

				exit(EXIT_FAILURE);
			}

			nlohmann::json::object_t temp = { {"minecraft:record",
					{{"comparator_signal", comparator_signal},
					{"duration",duration},
					{"sound_event",sound_event}}} };

			return temp;
		}

		/**
		 * @brief Creates the "shooter" component
		 *
		 * @param j Sets the entity that is used as ammunition
		 *
		 * @param charge_on_draw Sets if the item is charged when drawn
		 *
		 * @param max_draw_duration Determines how long can the weapon can be drawn before releasing automatically
		 *
		 * @param scale_power_by_draw_duration When set to 'true', the longer the weapon is drawn, the more power it will have when released
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Shooter(nlohmann::json j, bool charge_on_draw, float max_draw_duration, bool scale_power_by_draw_duration) {
			nlohmann::json::object_t temp = { {"minecraft:shooter",
				{{"max_draw_duration", max_draw_duration},
				{"scale_power_by_draw_duration",scale_power_by_draw_duration},
				{"charge_on_draw",charge_on_draw},
				{"ammunition", {j}}}} };

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
			nlohmann::json::object_t temp = { {"minecraft:should_despawn", {{"value", value}}} };

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
			nlohmann::json::object_t temp = { {"minecraft:stacked_by_data", {{"value", value}}} };

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
			nlohmann::json::object_t temp = { {"minecraft:tags", {{"tags", value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "throwable" component
		 *
		 * @param do_swing_animation Whether the item should use the swing animation when thrown.
		 *
		 * @param launch_power_scale The scale at which the power of the throw increases
		 *
		 * @param max_draw_duration The maximum duration to draw a throwable item.
		 *
		 * @param max_launch_power The maximum power to launch the throwable item.
		 *
		 * @param min_draw_duration The minimum duration to draw a throwable item.
		 *
		 * @param scale_power_by_draw_duration Whether or not the power of the throw increases with duration charged.
		 * When true, The longer you hold, the more power it will have when released.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Throwable(bool do_swing_animation, float launch_power_scale, float max_draw_duration, float max_launch_power, float min_draw_duration, bool scale_power_by_draw_duration) {
			nlohmann::json::object_t temp = { {"minecraft:throwable",
				{{"do_swing_animation", do_swing_animation},
				{"launch_power_scale",launch_power_scale},
				{"max_draw_duration",max_draw_duration},
				{"max_launch_power",max_launch_power},
				{"min_draw_duration",min_draw_duration},
				{"scale_power_by_draw_duration",scale_power_by_draw_duration}}} };

			return temp;
		}

		/**
		 * @brief Creates the "use_animation" component
		 *
		 * @param value Which animation to play when using an item.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t UseAnimations(std::string value) {
			nlohmann::json::object_t temp = { {"minecraft:use_animation ", {{"value", value}}} };

			return temp;
		}

		/**
		 * @brief Creates the "use_modifiers" component
		 *
		 * @param use_duration How long the item takes to use in seconds.
		 *
		 * @param movement_modifier Modifier value to scale the players movement speed when item is in use.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t UseModifiers(float use_duration, float movement_modifier) {
			nlohmann::json::object_t temp = { {"minecraft:use_modifiers",
				{{"use_duration", use_duration},
				{"movement_modifier", movement_modifier}}} };

			return temp;
		}

		/**
		 * @brief Creates the "wearable" component
		 *
		 * @param protection How much protection the wearable has.
		 *
		 * @param slot Determines where the item can be worn.
		 * If any non-hand slot is chosen, the max stack size is set to 1.
		 *
		 * @return nlohmann::json::object_t
		*/
		nlohmann::json::object_t Wearable(int protection, std::string slot) {
			nlohmann::json::object_t temp = { {"minecraft:wearable",
				{{"protection", protection},
				{"slot",slot}}} };

			return temp;
		}
	};
} // namespace adk