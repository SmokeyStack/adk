#pragma once

#include <string>

#include "item_component.h"
#include "item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Item
	 *
	 */
	class Item {
	public:
		std::string getType() { return "item"; };

		Item() {};

		/**
		 * @brief Construct a new Item object
		 *
		 * @param property ItemProperty
		 */
		Item(ItemProperty property) { internal_ = property; }

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the item
		 *
		 * @return nlohmann::json
		 */
		virtual nlohmann::json Generate(std::string mod_id, std::string id) {
			output_["format_version"] = "1.20.80";
			output_["minecraft:item"]["description"]["identifier"] = mod_id + ":" + id;

			if (internal_.GetAllowOffHand())
				output_["minecraft:item"]["components"].update(helper_.AllowOffHand(internal_.GetAllowOffHand()));

			if (!internal_.GetCanDestoryInCreative())
				output_["minecraft:item"]["components"].update(helper_.CanDestroyInCreative(internal_.GetCanDestoryInCreative()));

			if (!internal_.GetPlacerBlockBlock().empty()) {
				output_["minecraft:item"]["components"].update(helper_.PlacerBlock(internal_.GetPlacerBlockBlock()));

				if (internal_.GetPlacerBlockUseOn().size() != 0)
					output_["minecraft:item"]["components"].update(helper_.PlacerBlock(internal_.GetPlacerBlockBlock(), internal_.GetPlacerBlockUseOn()));
			}

			if (!internal_.GetCooldownCategory().empty())
				output_["minecraft:item"]["components"].update(helper_.Cooldown(internal_.GetCooldownCategory(), internal_.GetCooldownDuration()));

			if (internal_.GetDamage() != 0)
				output_["minecraft:item"]["components"].update(helper_.Damage(internal_.GetDamage(), id));

			if (!internal_.GetDisplayName().empty())
				output_["minecraft:item"]["components"].update(helper_.DisplayName(internal_.GetDisplayName()));

			if (internal_.GetDurability().durability != 0) {
				if (internal_.GetDurability().damage_chance.has_value())
					output_["minecraft:item"]["components"].update(helper_.Durability(internal_.GetDurability().durability, internal_.GetDurability().damage_chance.value().first, internal_.GetDurability().damage_chance.value().second, id));
				else
					output_["minecraft:item"]["components"].update(helper_.Durability(internal_.GetDurability().durability, 0, 0, id));
			}

			if (internal_.GetEnchantableSlot() != adk::EnchantableSlot::NONE)
				output_["minecraft:item"]["components"].update(helper_.Enchantable(adk::GetEnchantableSlot(internal_.GetEnchantableSlot()), internal_.GetEnchantableValue(), id));

			if (!internal_.GetPlacerEntity().entity.empty()) {
				std::vector<std::string> use_on;
				std::vector<std::string> dispense_on;

				if (internal_.GetPlacerEntity().use_on.has_value())
					use_on = internal_.GetPlacerEntity().use_on.value();
				if (internal_.GetPlacerEntity().dispense_on.has_value())
					dispense_on = internal_.GetPlacerEntity().dispense_on.value();

				output_["minecraft:item"]["components"].update(helper_.PlacerEntity(
					internal_.GetPlacerEntity().entity,
					use_on,
					dispense_on
				));
			}

			if (internal_.GetFood().nutrition != 0 && internal_.GetFood().saturation_modifier != 0) {
				bool can_always_eat = false;
				std::string using_converts_to;

				if (internal_.GetFood().can_always_eat.has_value())
					can_always_eat = internal_.GetFood().can_always_eat.value();
				if (internal_.GetFood().using_converts_to.has_value())
					using_converts_to = internal_.GetFood().using_converts_to.value();


				output_["minecraft:item"]["components"].update(helper_.Food(
					internal_.GetFood().nutrition,
					internal_.GetFood().saturation_modifier,
					can_always_eat,
					using_converts_to
				));
			}

			if (internal_.GetFuelDuration() != 0)
				output_["minecraft:item"]["components"].update(helper_.Fuel(internal_.GetFuelDuration(), id));

			if (internal_.GetGlint())
				output_["minecraft:item"]["components"].update(helper_.Glint(internal_.GetGlint()));

			if (internal_.GetHandEquipped())
				output_["minecraft:item"]["components"].update(helper_.HandEquipped(internal_.GetHandEquipped()));

			if (!internal_.GetHoverTextColor().empty())
				output_["minecraft:item"]["components"].update(helper_.HoverTextColor(internal_.GetHoverTextColor()));

			if (!internal_.GetIcon().empty())
				output_["minecraft:item"]["components"].update(helper_.Icon(internal_.GetIcon()));
			if (!internal_.GetInteractButton().empty())
				output_["minecraft:item"]["components"].update(helper_.InteractButton(internal_.GetInteractButton()));

			if (internal_.GetLiquidClipped())
				output_["minecraft:item"]["components"].update(helper_.LiquidClipped(internal_.GetLiquidClipped()));

			if (internal_.GetMaxStackSize() != 64)
				output_["minecraft:item"]["components"].update(helper_.MaxStackSize(internal_.GetMaxStackSize()));

			if (!internal_.GetProjectileEntity().empty())
				output_["minecraft:item"]["components"].update(helper_.Projectile(internal_.GetProjectileEntity(),
					internal_.GetProjectileMinCriticalPower()
				));

			if (!internal_.GetRecord().sound_event.empty())
				output_["minecraft:item"]["components"].update(helper_.Record(
					internal_.GetRecord().sound_event,
					internal_.GetRecord().duration,
					internal_.GetRecord().comparator_signal,
					id
				));

			if (internal_.GetShooter().ammunition.size() != 0)
				output_["minecraft:item"]["components"].update(helper_.Shooter(internal_.GetShooter()));

			if (internal_.GetShouldDespawn())
				output_["minecraft:item"]["components"].update(helper_.ShouldDespawn(internal_.GetShouldDespawn()));

			if (internal_.GetStackedByData())
				output_["minecraft:item"]["components"].update(helper_.StackedByData(internal_.GetStackedByData()));

			if (!internal_.GetTags().empty())
				output_["minecraft:item"]["components"].update(helper_.Tags(internal_.GetTags()));

			if (internal_.GetThrowable().is_throwable)
				output_["minecraft:item"]["components"].update(helper_.Throwable(internal_.GetThrowable()));

			if (!internal_.GetUseAnimation().empty())
				output_["minecraft:item"]["components"].update(helper_.UseAnimation(internal_.GetUseAnimation()));

			if (internal_.GetUseModifiersDuration() != 0)
				output_["minecraft:item"]["components"].update(helper_.UseModifiers(
					internal_.GetUseModifiersDuration(),
					internal_.GetUseModifiersMovement(),
					id
				));

			if (internal_.GetWearableSlot() != adk::WearableSlot::NONE)
				output_["minecraft:item"]["components"].update(helper_.Wearable(
					internal_.GetWearableProtection(),
					adk::GetWearableSlot(internal_.GetWearableSlot()
					)));

			return output_;
		}
	protected:
		ItemProperty internal_;
		ItemComponent helper_;
		nlohmann::json output_;
	};
} // namespace adk