#pragma once

#include <string>

#include "item/item.h"
#include "item/item_property.h"
#include "json.hpp"

namespace adk {
	/**
	 * @brief Represents a Music Disc Item
	 */
	class ItemMusicDisc : public Item {
	public:
		/**
		 * @brief Construct a new Music Disc Item object
		 *
		 * @param comparator_signal Signal strength for comparator blocks to use.
		 * 
		 * @param sound Sound to play when the disc is used.
		 * 
		 * @param property ItemProperty
		 *
		 * @param length_seconds Length of the music disc in seconds.
		 */
		ItemMusicDisc(int comparator_signal, std::string sound, ItemProperty property, int duration_seconds) {
			internal_ = property;
			comparator_signal_ = comparator_signal;
			sound_ = sound;
			duration_seconds_ = duration_seconds;
		}

		/**
		 * @brief Generates the json object
		 *
		 * @param mod_id Namespace identifier
		 *
		 * @param id Identifier for the item
		 *
		 * @return nlohmann::json
		 */
		nlohmann::json Generate(std::string mod_id, std::string id) {
			output_ = Item::Generate(mod_id, id);
			ItemRecord record;
			record.sound_event = sound_;
			record.comparator_signal = comparator_signal_;
			record.duration_seconds = duration_seconds_;

			output_["minecraft:item"]["components"].update(
				helper_.Record(record, id)
			);

			return output_;
		}
	private:
		int comparator_signal_;
		std::string sound_;
		int duration_seconds_;
	};
} // namespace adk