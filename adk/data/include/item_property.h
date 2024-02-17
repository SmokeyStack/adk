#pragma once

#include <optional>
#include <string>
#include <vector>

#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents the enchantable slots
	 */
	enum class EnchantableSlot {
		ARMOR_FEET,
		ARMOR_TORSO,
		ARMOR_HEAD,
		ARMOR_LEGS,
		AXE,
		BOW,
		COSMETIC_HEAD,
		CROSSBOW,
		ELYTRA,
		FISHING_ROD,
		FLINTSTEEL,
		HOE,
		PICKAXE,
		SHEARS,
		SHIELD,
		SHOVEL,
		SWORD,
		ALL,
	};

	/**
	 * @brief Gets the Enchantable slot object
	 *
	 * @param slot enum EnchantableSlot
	 *
	 * @return std::string
	 */
	inline std::string GetEnchantableSlot(EnchantableSlot slot) {
		switch (slot) {
		case EnchantableSlot::ARMOR_FEET:
			return "armor_feet";
		case EnchantableSlot::ARMOR_TORSO:
			return "armor_torso";
		case EnchantableSlot::ARMOR_HEAD:
			return "armor_head";
		case EnchantableSlot::ARMOR_LEGS:
			return "armor_legs";
		case EnchantableSlot::AXE:
			return "axe";
		case EnchantableSlot::BOW:
			return "bow";
		case EnchantableSlot::COSMETIC_HEAD:
			return "cosmetic_head";
		case EnchantableSlot::CROSSBOW:
			return "crossbow";
		case EnchantableSlot::ELYTRA:
			return "elytra";
		case EnchantableSlot::FISHING_ROD:
			return "fishing_rod";
		case EnchantableSlot::FLINTSTEEL:
			return "flintsteel";
		case EnchantableSlot::HOE:
			return "hoe";
		case EnchantableSlot::PICKAXE:
			return "pickaxe";
		case EnchantableSlot::SHEARS:
			return "shears";
		case EnchantableSlot::SHIELD:
			return "shield";
		case EnchantableSlot::SHOVEL:
			return "shovel";
		case EnchantableSlot::SWORD:
			return "sword";
		case EnchantableSlot::ALL:
			return "all";
		default:
			return "Error";
		}
	}

	namespace {
		/**
		 * @brief Sets how much damage the item can take before breaking, and allows the item to be combined at an anvil, grindstone, or crafting table.
		 *
		 * @param durability Max durability is the amount of damage that this item can take before breaking.
		 * This is a required parameter with a minimum value of 0.
		 *
		 * @param damage_chance Damage chance is the percentage chance of this item losing durability.
		 * Default is set at 100.
		 * Defined as an int range with min and max value.
		*/
		struct ItemDurability {
			int durability;
			std::optional<std::pair<int, int>> damage_chance;
		};

		struct ItemEntityPlacer {
			std::string entity;
			std::optional<std::vector<std::string>> use_on;
			std::optional<std::vector<std::string>> dispense_on;
		};

		struct ItemFood {
			int nutrition;
			float saturation_modifier;
			std::optional<bool> can_always_eat;
			std::optional<std::string> using_converts_to;
		};

		void to_json(nlohmann::json& j, const ItemDurability& p) {
			if (p.damage_chance.has_value()) {
				j = nlohmann::json{
					{"max_durability", p.durability},
					{"damage_chance",{
						{"min",p.damage_chance.value().first},
						{"max",p.damage_chance.value().second}
					}}
				};
			}
			else {
				j = nlohmann::json{ {"max_durability", p.durability} };
			}
		}

		void to_json(nlohmann::json& j, const ItemEntityPlacer& p) {
			j.update({ {"entity", p.entity} });
			if (p.use_on.has_value()) {
				j.update({ "use_on",p.use_on.value() });
			}
			if (p.dispense_on.has_value()) {
				j.update({ "dispense_on",p.dispense_on.value() });
			}
		}

		void to_json(nlohmann::json& j, const ItemFood& p) {
			j.update({ {"nutrition", p.nutrition}, {"saturation_modifier", p.saturation_modifier} });
			if (p.can_always_eat.has_value()) {
				j.update({ "can_always_eat",p.can_always_eat.value() });
			}
			if (p.using_converts_to.has_value()) {
				j.update({ "using_converts_to",p.using_converts_to.value() });
			}
		}
	}

	/**
	 * @brief Represents item properties such as icon, stack size, etc
	 *
	 */
	class ItemProperty {
	public:
		/**
		 * @brief Sets the "allow_off_hand" component
		 *
		 * @param value Whether the item can be placed in the off hand slot.
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetAllowOffHand(bool value) {
			this->allow_offhand = value;

			return *this;
		}

		/**
		 * @brief Sets the "block_placer" component
		 *
		 * @param value Defines the block that will be placed.
		 *
		 * @return ItemProperty
		 */
		ItemProperty PlacerBlock(std::string value) {
			this->placer_block_block = value;

			return *this;
		}

		/**
		 * @brief Sets the "block_placer" component
		 *
		 * @param block Defines the block that will be placed.
		 *
		 * @param used_on List of block descriptors that contain blocks that this item can be used on.
		 * If left empty, all blocks will be allowed.
		 *
		 * @return ItemProperty
		 */
		ItemProperty PlacerBlock(std::string block, std::vector<std::string> use_on) {
			this->placer_block_block = block;
			this->placer_block_use_on = use_on;

			return *this;
		}

		/**
		 * @brief Set the "max_stack_size" component
		 *
		 * @param value Defines whether the item can destroy blocks while in creative.
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetCanDestroyInCreative(bool value) {
			this->can_destroy_in_creative = value;

			return *this;
		}

		/**
		 * @brief Sets the "cooldown" component
		 *
		 * @param category The type of cool down for this item.
		 *
		 * @param duration The duration of time (in seconds) items with a matching category will spend cooling down before becoming usable again.
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetCooldown(std::string category, float duration) {
			this->cooldown_category = category;
			this->cooldown_duration = duration;

			return *this;
		}

		/**
		 * @brief Sets the "damage" component
		 *
		 * @param value How much extra damage the item does on attack.
		 * Note that this must be a positive value.
		 *
		 * @return nlohmann::json::object_t
		 */
		ItemProperty SetDamage(int value) {
			this->damage = value;

			return *this;
		}

		/**
		 * @brief Sets the "display_name" component
		 *
		 * @param value Set the display name for an item.
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetDisplayName(std::string value) {
			this->display_name = value;

			return *this;
		}

		/**
		 * @brief Sets the "display_name" component
		 *
		 * @param value ItemDurability struct
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetDisplayName(ItemDurability value) {
			this->durability = value;

			return *this;
		}

		/**
		 * @brief Sets the "durability" component
		 *
		 * @param value ItemDurability struct
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetDurability(ItemDurability value) {
			this->durability = value;

			return *this;
		}

		/**
		 * @brief Sets the "enchantable" component
		 *
		 * @param slot What enchantments can be applied (ex. Using bow would allow this item to be enchanted as if it were a bow).
		 *
		 * @param value The value of the enchantment (minimum of 0).
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetEnchantable(std::string slot, int value) {
			this->enchantable_slot = slot;
			this->enchantable_value = value;

			return *this;
		}

		/**
		 * @brief Sets the "entity_placer" component
		 *
		 * @param value ItemEntityPlacer struct
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetPlacerEntity(ItemEntityPlacer value) {
			this->placer_entity = value;

			return *this;
		}

		/**
		 * @brief Sets the "food" component
		 *
		 * @param value ItemFood struct
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetFood(ItemFood value) {
			this->food = value;

			return *this;
		}

		/**
		 * @brief Sets the "fuel" component
		 *
		 * @param value How long in seconds will this fuel cook items for.
		 * Minimum value: 0.05.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetFuel(float value) {
			this->fuel_duration = value;

			return *this;
		}

		/**
		 * @brief Sets the "fuel" component
		 *
		 * @param value Whether the item has the enchanted glint render effect.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetGlint(bool value) {
			this->glint = value;

			return *this;
		}

		/**
		 * @brief Sets the "fuel" component
		 *
		 * @param value Determines if the item is rendered like a tool in-hand.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetHandEquipped(bool value) {
			this->hand_equipped = value;

			return *this;
		}

		/**
		 * @brief Sets the "hover_text_color" component
		 *
		 * @param value The color of the item hover text.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetHoverTextColor(std::string value) {
			this->hover_text_color = value;

			return *this;
		}

		/**
		 * @brief Sets the "icon" component
		 *
		 * @param value This map contains the different textures that can be used for the item's icon.
		 * Default will contain the actual icon texture.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetIcon(std::string value) {
			this->icon = value;

			return *this;
		}

		/**
		 * @brief Sets the "interact_button" component
		 *
		 * @param value What text is displayed on the button.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetInteractButton(std::string value) {
			this->interact_button = value;

			return *this;
		}

		/**
		 * @brief Sets the "liquid_clipped" component
		 *
		 * @param value Whether an item interacts with liquid blocks on use.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetLiquidClipped(bool value) {
			this->liquid_clipped = value;

			return *this;
		}

		/**
		 * @brief Sets the "max_stack_size" component
		 *
		 * @param value How many of an item that can be stacked together.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetMaxStackSize(int value) {
			this->max_stack_size = value;

			return *this;
		}

		/**
		 * @brief Sets the "projectile" component
		 *
		  * @param projectile_entity The entity to be fired as a projectile.
		 *
		 * @param minimum_critical_power Defines the time a projectile needs to charge in order to critically hit.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetProjectile(std::string projectile_entity, float minimum_critical_power) {
			this->projectile_entity = projectile_entity;
			this->projectile_min_critical_power = minimum_critical_power;

			return *this;
		}
	private:
		bool allow_offhand = false;
		bool can_destroy_in_creative = false;
		std::string placer_block_block;
		std::vector<std::string> placer_block_use_on;
		std::string cooldown_category;
		float cooldown_duration;
		int damage;
		std::string display_name;
		ItemDurability durability;
		std::string enchantable_slot;
		std::string enchantable_value;
		ItemEntityPlacer placer_entity;
		ItemFood food;
		float fuel_duration;
		bool glint = false;
		bool hand_equipped = false;
		std::string hover_text_color;
		std::string icon;
		std::string interact_button;
		bool liquid_clipped = false;
		int max_stack_size = 64;
		float projectile_min_critical_power;
		std::string projectile_entity;
	};
} // namespace adk