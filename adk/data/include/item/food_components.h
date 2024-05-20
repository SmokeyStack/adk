#pragma once

#include <string>
#include <unordered_map>

#include "item/armor_material.h"
#include "item/item.h"

namespace adk {
	/**
	 * @brief Contains all the default food components used in vanilla food items.
	 */
	class FoodComponents {
	public:
		static ItemFood Apple;
	};

	ItemFood FoodComponents::Apple = ItemFood{
		4, 0.3,
	};
} // namespace adk