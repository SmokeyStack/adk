#pragma once

#include <string>
#include <vector>

#include "json.hpp"
#include "shared_construct.h"

namespace adk {
	/**
	 * @brief Represents the enchantable slots
	 */
	enum class EnchantableSlot {
		ArmorFeet,
		ArmorTorso,
		ArmorHead,
		ArmorLegs,
		Axe,
		Bow,
		CosmeticHead,
		Crossbow,
		Elytra,
		FishingRod,
		Flintsteel,
		Hoe,
		Pickaxe,
		Shears,
		Shield,
		Shovel,
		Sword,
		All,
		CarrotStick,
		Spear,
		None
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
		case EnchantableSlot::ArmorFeet:
			return "armor_feet";
		case EnchantableSlot::ArmorTorso:
			return "armor_torso";
		case EnchantableSlot::ArmorHead:
			return "armor_head";
		case EnchantableSlot::ArmorLegs:
			return "armor_legs";
		case EnchantableSlot::Axe:
			return "axe";
		case EnchantableSlot::Bow:
			return "bow";
		case EnchantableSlot::CosmeticHead:
			return "cosmetic_head";
		case EnchantableSlot::Crossbow:
			return "crossbow";
		case EnchantableSlot::Elytra:
			return "elytra";
		case EnchantableSlot::FishingRod:
			return "fishing_rod";
		case EnchantableSlot::Flintsteel:
			return "flintsteel";
		case EnchantableSlot::Hoe:
			return "hoe";
		case EnchantableSlot::Pickaxe:
			return "pickaxe";
		case EnchantableSlot::Shears:
			return "shears";
		case EnchantableSlot::Shield:
			return "shield";
		case EnchantableSlot::Shovel:
			return "shovel";
		case EnchantableSlot::Sword:
			return "sword";
		case EnchantableSlot::All:
			return "all";
		case EnchantableSlot::CarrotStick:
			return "carrot_stick";
		case EnchantableSlot::Spear:
			return "spear";
		case EnchantableSlot::None:
		default:
			return "Error";
		}
	}

	/**
	 * @brief Represents the wearable slots
	 */
	enum class WearableSlot {
		WeaponOffhand,
		ArmorHead,
		ArmorChest,
		ArmorLegs,
		ArmorFeet,
		None
	};

	/**
	 * @brief Gets the Wearable slot object
	 *
	 * @param slot enum WearableSlot
	 *
	 * @return std::string
	 */
	inline std::string GetWearableSlot(WearableSlot slot) {
		switch (slot) {
		case WearableSlot::WeaponOffhand:
			return "slot.weapon.offhand";
		case WearableSlot::ArmorHead:
			return "slot.armor.head";
		case WearableSlot::ArmorChest:
			return "slot.armor.chest";
		case WearableSlot::ArmorLegs:
			return "slot.armor.legs";
		case WearableSlot::ArmorFeet:
			return "slot.armor.feet";
		case WearableSlot::None:
		default:
			return "Error";
		}
	}

	namespace {
		/**
		 * @brief A list of blocks to dig, with correlating speeds of digging.
		 *
		 * @param block What blocks the item will destroy.
		 *
		 * @param speed The speed at which the item will destroy the block.
		 */
		struct ItemDiggerDestroySpeeds {
			int speed;
			std::variant<std::string, BlockDescriptor> block;
		};

		/**
		 * @brief
		 *
		 * @param destroy_speeds A list of blocks to dig, with correlating speeds of digging.
		 *
		 * @param use_efficiency Determines whether the item should be impacted if the "efficiency" enchant is applied to it.
		 */
		struct ItemDigger {
			std::vector<ItemDiggerDestroySpeeds> destroy_speeds;
			bool use_efficiency = false;
		};

		/**
		 * @brief Determines how much damage the item can take before breaking, and allows the item to be combined in crafting.
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
			std::pair<int, int> damage_chance{ 100,100 };
		};

		/**
		 * @brief Allows the item to place specified entities into the world.
		 *
		 * @param entity The entity to be placed in the world.
		 *
		 * @param use_on List of block descriptors that contain blocks that this item can be used on. If left empty, all blocks will be allowed.
		 *
		 * @param dispense_on List of block descriptors that contain blocks that this item can be dispensed on. If left empty, all blocks will be allowed.
		 */
		struct ItemEntityPlacer {
			std::string entity;
			std::vector<std::string> use_on;
			std::vector<std::string> dispense_on;
		};

		/**
		 * @brief When an item has a food component, it becomes edible to the player.
		 * Must have the "minecraft:use_modifiers" component in order to function properly.
		 *
		 * @param nutrition The value that is added to the actor's nutrition when the item is used.
		 *
		 * @param saturation_modifier Saturation Modifier is used in this formula: (nutrition * saturation_modifier * 2) when applying the saturation buff.
		 *
		 * @param can_always_eat If "true" you can always eat this item (even when not hungry).
		 *
		 * @param using_converts_to When used, converts to the item specified by the string in this field.
		 */
		struct ItemFood {
			int nutrition = 0;
			double saturation_modifier = 0.6;
			bool can_always_eat = false;
			std::string using_converts_to;
		};

		/**
		 * @brief The record item component allows the item to play a sound when used in a jukebox.
		 *
		 * @param comparator_signal Signal strength for comparator blocks to use from 1 - 13.
		 *
		 * @param duration_seconds Duration of sound event in seconds float value.
		 *
		 * @param sound_event Sound event types
		*/
		struct ItemRecord {
			std::string sound_event;
			double duration_seconds = 0.0;
			int comparator_signal = 1;
		};

		/**
		 * @brief Repair item entries.
		 *
		 * @param repair_amount How much durability is repaired.
		 *
		 * @param items List of items that can be used to repair the item.
		 */
		struct ItemRepairableItems {
			std::variant<int, std::string> repair_amount = 0;
			std::vector<std::string> items;
		};

		/**
		 * @brief Repairable item component: Determines which items can be used to repair a defined item, as well as the amount of durability specified items will repair.
		 *
		 * @param repair_items List of repair item entries.
		 */
		struct ItemRepairable {
			std::vector<ItemRepairableItems> repair_items;
		};

		/**
		 * @brief The projectile entity
		 *
		 * @param item Denotes the item description identifier.
		 *
		 * @param use_offhand When set to true, ammunition can be used from the offhand.
		 *
		 * @param search_inventory Determines whether the inventory can be searched for ammunition to use.
		 *
		 * @param use_in_creative Determines whether the item can be used in creative mode.
		 */
		struct ItemShooterAmmunition {
			std::string item;
			bool use_offhand = false;
			bool search_inventory = false;
			bool use_in_creative = false;
		};

		/**
		 * @brief Shooter Item Component.
		 *
		 * @param ammunition List of projectile entity that is used as ammunition.
		 *
		 * @param charge_on_draw Determines if the item should charge when drawn.
		 *
		 * @param max_draw_duration Determines how long can the weapon can be drawn before releasing automatically.
		 *
		 * @param scale_power_by_draw_duration When set to true, the longer the weapon is drawn, the more power it will have when released.
		 */
		struct ItemShooter {
			std::vector<ItemShooterAmmunition> ammunition;
			bool charge_on_draw = false;
			double max_draw_duration = 0.0;
			bool scale_power_by_draw_duration = false;
		};

		/**
		 * @brief Throwable item component. Throwable items, such as a snowball.
		 *
		 * @param do_swing_animation Whether the item should use the swing animation when thrown.
		 *
		 * @param launch_power_scale The scale at which the power of the throw increases.
		 *
		 * @param max_draw_duration The maximum duration to draw a throwable item.
		 *
		 * @param max_launch_power The maximum power to launch the throwable item.
		 *
		 * @param min_draw_duration The minimum duration to draw a throwable item.
		 *
		 * @param scale_power_by_draw_duration Whether or not the power of the throw increases with duration charged.
		 * When "true", The longer you hold, the more power it will have when released.
		 */
		struct ItemThrowable {
			bool do_swing_animation = false;
			float launch_power_scale = 1.0;
			float max_draw_duration = 0.0;
			float max_launch_power = 1.0;
			float min_draw_duration = 0.0;
			bool scale_power_by_draw_duration = false;
		};

		void to_json(nlohmann::json& j, const ItemDiggerDestroySpeeds& p) {
			if (std::holds_alternative<std::string>(p.block))
				j.update({ {"speed", p.speed}, {"block", std::get<std::string>(p.block)} });
			else
				j.update({ {"speed", p.speed}, {"block", std::get<BlockDescriptor>(p.block)} });
		}

		void to_json(nlohmann::json& j, const ItemDigger& p) {
			j.update({ {"destroy_speeds", p.destroy_speeds} });

			if (p.use_efficiency)
				j.update({ "use_efficieny",p.use_efficiency });
		}

		void to_json(nlohmann::json& j, const ItemDurability& p) {
			j.update({ {"max_durability", p.durability} });

			if (p.damage_chance.first != 100 || p.damage_chance.second != 100)
				j.update({ {"damage_chance",{ {"min", p.damage_chance.first}, {"max",p.damage_chance.second}}} });
		}

		void to_json(nlohmann::json& j, const ItemEntityPlacer& p) {
			j.update({ {"entity", p.entity} });

			if (!p.use_on.empty())
				j.update({ { "use_on",p.use_on } });
			if (!p.dispense_on.empty())
				j.update({ { "dispense_on",p.dispense_on } });
		}

		void to_json(nlohmann::json& j, const ItemFood& p) {
			if (p.nutrition != 0)
				j.update({ {"nutrition", p.nutrition} });
			if (p.can_always_eat)
				j.update({ {"can_always_eat", p.can_always_eat} });
			if (p.saturation_modifier != 0.6)
				j.update({ {"saturation_modifier", p.saturation_modifier} });
			if (!p.using_converts_to.empty())
				j.update({ {"using_converts_to", p.using_converts_to} });
		}

		void to_json(nlohmann::json& j, const ItemRecord& p) {
			j.update({ {"sound_event", p.sound_event} });

			if (p.duration_seconds != 0.0)
				j.update({ {"duration", p.duration_seconds} });
			if (p.comparator_signal != 1)
				j.update({ {"comparator_signal", p.comparator_signal} });
		}

		void to_json(nlohmann::json& j, const ItemRepairableItems& p) {
			j.update({ {"items", p.items} });

			if (std::holds_alternative<int>(p.repair_amount))
				j.update({ {"repair_amount", std::get<int>(p.repair_amount) } });
			else
				j.update({ {"repair_amount", std::get<std::string>(p.repair_amount) } });
		}

		void to_json(nlohmann::json& j, const ItemRepairable& p) {
			j.update({ {"repair_items", p.repair_items } });
		}

		void to_json(nlohmann::json& j, const ItemShooterAmmunition& p) {
			j.update({ {"item", p.item} });

			if (p.use_offhand)
				j.update({ {"use_offhand",p.use_offhand} });
			if (p.search_inventory)
				j.update({ {"search_inventory",p.search_inventory} });
			if (p.use_in_creative)
				j.update({ {"use_in_creative",p.use_in_creative } });
		}

		void to_json(nlohmann::json& j, const ItemShooter& p) {
			j.update({ {"ammunition", p.ammunition} });

			if (p.charge_on_draw)
				j.update({ { "charge_on_draw",p.charge_on_draw } });
			if (p.max_draw_duration != 0.0)
				j.update({ { "max_draw_duration",p.max_draw_duration } });
			if (p.scale_power_by_draw_duration)
				j.update({ { "scale_power_by_draw_duration",p.scale_power_by_draw_duration } });
		}

		void to_json(nlohmann::json& j, const ItemThrowable& p) {
			if (p.do_swing_animation)
				j.update({ { "do_swing_animation",p.do_swing_animation } });
			if (p.launch_power_scale != 1.0)
				j.update({ { "launch_power_scale",p.launch_power_scale } });
			if (p.max_draw_duration != 0.0)
				j.update({ { "max_draw_duration",p.max_draw_duration } });
			if (p.max_launch_power != 1.0)
				j.update({ { "max_launch_power",p.max_launch_power } });
			if (p.min_draw_duration != 0.0)
				j.update({ { "min_draw_duration",p.min_draw_duration } });
			if (p.scale_power_by_draw_duration)
				j.update({ { "scale_power_by_draw_duration",p.scale_power_by_draw_duration } });
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
		 * @param value Determine whether an item can be placed in the off-hand slot of the inventory.
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
		 * @param used_on List of block descriptors that contain blocks that this item can be used on.
		 * If left empty, all blocks will be allowed.
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetPlacerBlock(std::string value, std::vector<std::string> use_on = {}) {
			this->placer_block_block = value;

			if (!use_on.empty())
				this->placer_block_use_on = use_on;

			return *this;
		}

		/**
		 * @brief Set the "can_destroy_in_creative" component
		 *
		 * @param value Determines if the item will break blocks in Creative Mode while swinging.
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
		 * @param duration_seconds The duration of time (in seconds) items with a matching category will spend cooling down before becoming usable again.
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetCooldown(std::string category, double duration_seconds) {
			this->cooldown_category = category;
			this->cooldown_duration_seconds = duration_seconds;

			return *this;
		}

		/**
		 * @brief Sets the "custom_components" component
		 *
		 * @param value Array of custom components
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetCustomComponents(std::vector<std::string> value) {
			this->custom_components = value;

			return *this;
		}

		/**
		 * @brief Sets the "damage" component
		 *
		 * @param value Determines how much extra damage the item does on attack.
		 * How much extra damage the item does on attack.
		 * Note that this must be a positive value.
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetDamage(int value) {
			this->damage = value;

			return *this;
		}

		/**
		 * @brief Sets the "digger" component
		 *
		 * @param value ItemDigger struct
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetDigger(ItemDigger value) {
			this->digger = value;

			return *this;
		}

		/**
		 * @brief Sets the "display_name" component
		 *
		 * @param value Defines the text shown when an item name is shown, such as hover text.
		 *
		 * @return ItemProperty
		 */
		ItemProperty SetDisplayName(std::string value) {
			this->display_name = value;

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
		 * @param slot What enchantments can be applied (ex. Using "bow" would allow this item to be enchanted as if it were a bow).
		 *
		 * @param value The value of the enchantment (minimum of 0).
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetEnchantable(EnchantableSlot slot, int value) {
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
		ItemProperty SetFuel(double value) {
			this->fuel_duration = value;

			return *this;
		}

		/**
		 * @brief Sets the "glint" component
		 *
		 * @param value Determines whether the item has the enchanted glint render effect on it.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetGlint(bool value) {
			this->glint = value;

			return *this;
		}

		/**
		 * @brief Sets the "hand_equipped" component
		 *
		 * @param value Determines if an item is rendered like a tool while in hand.
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
		 * @param value Determines the color of the item name when hovering over it.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetHoverTextColor(std::string value) {
			this->hover_text_color = value;

			return *this;
		}

		/**
		 * @brief Sets the "interact_button" component
		 *
		 * @param value This component is a boolean or string that determines if the interact button is shown in touch controls and what text is displayed on the button.
		 * When set to 'true', default 'Use Item' text will be used.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetInteractButton(std::variant<bool, std::string> value) {
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
		 * If no namespace is specified, it is assumed to be minecraft.
		 *
		 * @param minimum_critical_power Defines the time a projectile needs to charge in order to critically hit.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetProjectile(std::string projectile_entity, double minimum_critical_power) {
			this->projectile_entity = projectile_entity;
			this->projectile_min_critical_power = minimum_critical_power;

			return *this;
		}

		/**
		 * @brief Sets the "record" component
		 *
		 * @param value ItemRecord struct
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetRecord(ItemRecord value) {
			this->record = value;

			return *this;
		}

		/**
		 * @brief Sets the "repariable" component
		 *
		 * @param value ItemRepairable struct
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetRepairable(ItemRepairable value) {
			this->repairable = value;

			return *this;
		}

		/**
		 * @brief Sets the "shooter" component
		 *
		 * @param value ItemShooter struct
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetShooter(ItemShooter value) {
			this->shooter = value;

			return *this;
		}

		/**
		 * @brief Sets the "should_despawn" component
		 *
		 * @param value Determines whether an item should eventually despawn while floating in the world.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetShouldDespawn(bool value) {
			this->should_despawn = value;

			return *this;
		}

		/**
		 * @brief Sets the "stacked_by_data" component
		 *
		 * @param value Determines if the same item with different aux values can stack.
		 * Additionally, defines whether the item actors can merge while floating in the world.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetStackedByData(bool value) {
			this->stacked_by_data = value;

			return *this;
		}

		/**
		 * @brief Sets the "tags" component
		 *
		 * @param value The "tags" component determines which tags are attached to an item.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetTags(std::vector<std::string> value) {
			this->tags = value;

			return *this;
		}

		/**
		 * @brief Sets the "throwable" component
		 *
		 * @param value ItemThrowable struct
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetThrowable(ItemThrowable value) {
			this->throwable = value;

			return *this;
		}

		/**
		 * @brief Sets the "use_animation" component
		 *
		 * @param value Which animation to play when using an item.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetUseAnimation(std::string value) {
			this->use_animation = value;

			return *this;
		}

		/**
		 * @brief Sets the "use_modifiers" component
		 *
		 * @param use_duration_seconds How long the item takes to use in seconds.
		 *
		 * @param movement_modifier Modifier value to scale the players movement speed when item is in use.
		 * Range: 0-1.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetUseModifiers(double use_duration_seconds, double movement_modifier) {
			this->use_modifiers_movement = movement_modifier;
			this->use_modifiers_duration_seconds = use_duration_seconds;

			return *this;
		}

		/**
		 * @brief Sets the "wearable" component
		 *
		 * @param slot Determines where the item can be worn.
		 * If any non-hand slot is chosen, the max stack size is set to 1.
		 *
		 * @param protection How much protection the wearable has.
		 *
		 * @return ItemProperty
		*/
		ItemProperty SetWearable(WearableSlot slot, int protection) {
			this->wearable_slot = slot;
			this->wearable_protection = protection;

			return *this;
		}

		/**
		 * @brief Gets the "allow_off_hand" component
		 *
		 * @return bool
		 */
		bool GetAllowOffHand() const { return allow_offhand; }

		/**
		 * @brief Gets the "can_destroy_in_creative" component
		 *
		 * @return bool
		 */
		bool GetCanDestoryInCreative() const { return can_destroy_in_creative; }

		/**
		 * @brief Gets the "block_placer" component. Block.
		 *
		 * @return std::string
		 */
		std::string GetPlacerBlockBlock() const { return placer_block_block; }

		/**
		 * @brief Gets the "block_placer" component. Use On.
		 *
		 * @return std::vector<std::string>
		 */
		std::vector<std::string> GetPlacerBlockUseOn() const { return placer_block_use_on; }

		/**
		 * @brief Gets the "cooldown" component. Category
		 *
		 * @return std::string
		 */
		std::string GetCooldownCategory() const { return cooldown_category; }

		/**
		 * @brief Gets the "cooldown" component. Duration
		 *
		 * @return double
		 */
		double GetCooldownDurationSeconds() const { return cooldown_duration_seconds; }

		/**
		 * @brief Gets the "custom_components" component
		 *
		 * @return std::vector<std::string>
		 */
		std::vector<std::string> GetCustomComponents() const { return custom_components; }

		/**
		 * @brief Gets the "damage" component
		 *
		 * @return int
		 */
		int GetDamage() const { return damage; }

		/**
		 * @brief Gets the "digger" component
		 *
		 * @return ItemDigger
		 */
		ItemDigger GetDigger() const { return digger; }

		/**
		 * @brief Gets the "display_name" component
		 *
		 * @return std::string
		 */
		std::string GetDisplayName() const { return display_name; }

		/**
		 * @brief Gets the "durability" component
		 *
		 * @return ItemDurability
		 */
		ItemDurability GetDurability() const { return durability; }

		/**
		 * @brief Gets the "enchantable" component. Slot
		 *
		 * @return EnchantableSlot
		 */
		EnchantableSlot GetEnchantableSlot() const { return enchantable_slot; }

		/**
		 * @brief Gets the "enchantable" component. Value
		 *
		 * @return int
		 */
		int GetEnchantableValue() const { return enchantable_value; }

		/**
		 * @brief Gets the "entity_placer" component
		 *
		 * @return ItemEntityPlacer
		 */
		ItemEntityPlacer GetPlacerEntity() const { return placer_entity; }

		/**
		 * @brief Gets the "food" component
		 *
		 * @return ItemFood
		 */
		ItemFood GetFood() const { return food; }

		/**
		 * @brief Gets the "fuel" component
		 *
		 * @return double
		 */
		double GetFuelDurationSeconds() const { return fuel_duration; }

		/**
		 * @brief Gets the "glint" component
		 *
		 * @return bool
		 */
		bool GetGlint() const { return glint; }

		/**
		 * @brief Gets the "hand_equipped" component
		 *
		 * @return bool
		 */
		bool GetHandEquipped() const { return hand_equipped; }

		/**
		 * @brief Gets the "hover_text_color" component
		 *
		 * @return std::string
		 */
		std::string GetHoverTextColor() const { return hover_text_color; }

		/**
		 * @brief Gets the "interact_button" component
		 *
		 * @return std::variant<bool, std::string>
		 */
		std::variant<bool, std::string> GetInteractButton() const { return interact_button; }

		/**
		 * @brief Gets the "liquid_component" component
		 *
		 * @return bool
		 */
		bool GetLiquidClipped() const { return liquid_clipped; }

		/**
		 * @brief Gets the "max_stack_size" component
		 *
		 * @return int
		 */
		int GetMaxStackSize() const { return max_stack_size; }

		/**
		 * @brief Gets the "projectile" component. Min Critical Power
		 *
		 * @return double
		 */
		double GetProjectileMinCriticalPower() const { return projectile_min_critical_power; }

		/**
		 * @brief Gets the "projectile" component. Entity
		 *
		 * @return std::string
		 */
		std::string GetProjectileEntity() const { return projectile_entity; }

		/**
		 * @brief Gets the "record" component
		 *
		 * @return ItemRecord
		 */
		ItemRecord GetRecord() const { return record; }

		/**
		 * @brief Gets the "repairable" component
		 *
		 * @return ItemRepairable
		 */
		ItemRepairable GetRepairable() const { return repairable; }

		/**
		 * @brief Gets the "shooter" component
		 *
		 * @return ItemShooter
		 */
		ItemShooter GetShooter() const { return shooter; }

		/**
		 * @brief Gets the "should_despawn" component
		 *
		 * @return bool
		 */
		bool GetShouldDespawn() const { return should_despawn; }

		/**
		 * @brief Gets the "stacked_by_data" component
		 *
		 * @return bool
		 */
		bool GetStackedByData() const { return stacked_by_data; }

		/**
		 * @brief Gets the "tags" component
		 *
		 * @return std::vector<std::string>
		 */
		std::vector<std::string> GetTags() const { return tags; }

		/**
		 * @brief Gets the "throwable" component
		 *
		 * @return ItemThrowable
		 */
		ItemThrowable GetThrowable() const { return throwable; }

		/**
		 * @brief Gets the "use_animation" component
		 *
		 * @return std::string
		 */
		std::string GetUseAnimation() const { return use_animation; }

		/**
		 * @brief Gets the "use_modifiers" component. Movement
		 *
		 * @return double
		 */
		double GetUseModifiersMovement() const { return use_modifiers_movement; }

		/**
		 * @brief Gets the "use_modifiers" component. Duration
		 *
		 * @return double
		 */
		double GetUseModifiersDurationSeconds() const { return use_modifiers_duration_seconds; }

		/**
		 * @brief Gets the "wearable" component. Slot
		 *
		 * @return WearableSlot
		 */
		WearableSlot GetWearableSlot() const { return wearable_slot; }

		/**
		 * @brief Gets the "wearable" component. Protection
		 *
		 * @return int
		 */
		int GetWearableProtection() const { return wearable_protection; }
	private:
		bool allow_offhand = false;
		bool can_destroy_in_creative = true;
		std::string placer_block_block;
		std::vector<std::string> placer_block_use_on;
		std::string cooldown_category;
		double cooldown_duration_seconds;
		std::vector<std::string> custom_components;
		int damage = 0;
		ItemDigger  digger;
		std::string display_name;
		ItemDurability durability;
		EnchantableSlot enchantable_slot = EnchantableSlot::None;
		int enchantable_value;
		ItemEntityPlacer placer_entity;
		ItemFood food;
		double fuel_duration;
		bool glint = false;
		bool hand_equipped = false;
		std::string hover_text_color;
		std::variant<bool, std::string> interact_button = true;
		bool liquid_clipped = false;
		int max_stack_size = 64;
		double projectile_min_critical_power;
		std::string projectile_entity;
		ItemRecord record;
		ItemRepairable repairable;
		ItemShooter shooter;
		bool should_despawn = true;
		bool stacked_by_data = false;
		std::vector<std::string> tags;
		ItemThrowable throwable;
		std::string use_animation;
		double use_modifiers_movement;
		double use_modifiers_duration_seconds;
		WearableSlot wearable_slot = WearableSlot::None;
		int wearable_protection = 0;
	};
} // namespace adk