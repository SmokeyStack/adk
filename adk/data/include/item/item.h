#pragma once

#include <string>
#include <variant>

#include "item/item_component.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents an Item
	 */
	class Item {
	public:
		/**
		 * @brief Returns the type of the object
		 * 
		 * @return std::string
		 */
		std::string GetType() { return "item"; };

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
			output_["format_version"] = "1.21.10";
			output_["minecraft:item"]["description"]["identifier"] = mod_id + ":" + id;
			nlohmann::json temp;

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
				output_["minecraft:item"]["components"].update(helper_.Cooldown(internal_.GetCooldownCategory(), internal_.GetCooldownDurationSeconds()));

			if (!internal_.GetCustomComponents().empty())
				output_["minecraft:item"]["components"].update(helper_.CustomComponents(internal_.GetCustomComponents()));

			if (internal_.GetDamage() != 0)
				output_["minecraft:item"]["components"].update(helper_.Damage(internal_.GetDamage(), id));

			if (!internal_.GetDigger().destroy_speeds.empty())
				output_["minecraft:item"]["components"].update(helper_.Digger(internal_.GetDigger()));

			if (!internal_.GetDisplayName().empty())
				output_["minecraft:item"]["components"].update(helper_.DisplayName(internal_.GetDisplayName()));

			if (internal_.GetDurability().durability != 0) {
				output_["minecraft:item"]["components"].update(helper_.Durability(internal_.GetDurability(), id));
			}

			if (internal_.GetEnchantableSlot() != EnchantableSlot::None)
				output_["minecraft:item"]["components"].update(helper_.Enchantable(GetEnchantableSlot(internal_.GetEnchantableSlot()), internal_.GetEnchantableValue(), id));

			if (!internal_.GetPlacerEntity().entity.empty())
				output_["minecraft:item"]["components"].update(helper_.PlacerEntity(internal_.GetPlacerEntity()));

			temp = internal_.GetFood();
			if (!temp.is_null())
				output_["minecraft:item"]["components"].update(helper_.Food(internal_.GetFood()));

			if (internal_.GetFuelDurationSeconds() != 0)
				output_["minecraft:item"]["components"].update(helper_.Fuel(internal_.GetFuelDurationSeconds(), id));

			if (internal_.GetGlint())
				output_["minecraft:item"]["components"].update(helper_.Glint(internal_.GetGlint()));

			if (internal_.GetHandEquipped())
				output_["minecraft:item"]["components"].update(helper_.HandEquipped(internal_.GetHandEquipped()));

			if (!internal_.GetHoverTextColor().empty())
				output_["minecraft:item"]["components"].update(helper_.HoverTextColor(internal_.GetHoverTextColor()));

			if (std::holds_alternative<bool>(internal_.GetInteractButton()))
				if (!std::get<bool>(internal_.GetInteractButton()))
					output_["minecraft:item"]["components"].update(helper_.InteractButton(internal_.GetInteractButton()));

			if (std::holds_alternative<std::string>(internal_.GetInteractButton()))
				output_["minecraft:item"]["components"].update(helper_.InteractButton(internal_.GetInteractButton()));

			if (internal_.GetLiquidClipped())
				output_["minecraft:item"]["components"].update(helper_.LiquidClipped(internal_.GetLiquidClipped()));

			if (internal_.GetMaxStackSize() != 64)
				output_["minecraft:item"]["components"].update(helper_.MaxStackSize(internal_.GetMaxStackSize()));

			if (!internal_.GetProjectileEntity().empty())
				output_["minecraft:item"]["components"].update(helper_.Projectile(internal_.GetProjectileEntity(), internal_.GetProjectileMinCriticalPower()));

			if (!internal_.GetRecord().sound_event.empty())
				output_["minecraft:item"]["components"].update(helper_.Record(internal_.GetRecord(), id));

			if (!internal_.GetRepairable().repair_items.empty())
				output_["minecraft:item"]["components"].update(helper_.Repairable(internal_.GetRepairable()));

			if (internal_.GetShooter().ammunition.size() != 0)
				output_["minecraft:item"]["components"].update(helper_.Shooter(internal_.GetShooter()));

			if (!internal_.GetShouldDespawn())
				output_["minecraft:item"]["components"].update(helper_.ShouldDespawn(internal_.GetShouldDespawn()));

			if (internal_.GetStackedByData())
				output_["minecraft:item"]["components"].update(helper_.StackedByData(internal_.GetStackedByData()));

			if (!internal_.GetTags().empty())
				output_["minecraft:item"]["components"].update(helper_.Tags(internal_.GetTags()));

			temp = internal_.GetThrowable();
			if (!temp.is_null())
				output_["minecraft:item"]["components"].update(helper_.Throwable(internal_.GetThrowable()));

			if (!internal_.GetUseAnimation().empty())
				output_["minecraft:item"]["components"].update(helper_.UseAnimation(internal_.GetUseAnimation()));

			if (internal_.GetUseModifiersDurationSeconds() != 0)
				output_["minecraft:item"]["components"].update(helper_.UseModifiers(
					internal_.GetUseModifiersDurationSeconds(),
					internal_.GetUseModifiersMovement(),
					id
				));

			if (internal_.GetWearableSlot() != WearableSlot::None)
				output_["minecraft:item"]["components"].update(helper_.Wearable(GetWearableSlot(internal_.GetWearableSlot()), internal_.GetWearableProtection(), id));

			return output_;
		}
	protected:
		ItemProperty internal_;
		ItemComponent helper_;
		nlohmann::json output_;
	};
} // namespace adk