#pragma once

#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <variant>

#include "block.h"
#include "item.h"

namespace fs = std::filesystem;

namespace adk {
	/**
	 * @brief Not directly used except for putting adk::Registry<T> into vectors
	 */
	class Registrar {
	public:
		virtual void Subscribe(std::string id,
			std::variant<Block*, Item*> object) {}

		virtual std::map<std::string, std::variant<Block*, Item*>> GetRegistry() {
			std::map<std::string, std::variant<Block*, Item*>> registry;
			return registry;
		}
	};

	/**
	 * @brief Used to register objects into the game
	 *
	 * @param T Object type such as Block or Item
	 */
	template <typename T>
	class Registry : public Registrar {
	public:
		/**
		 * @brief Construct a new Registry object
		 *
		 * @param id namespace identifier
		 */
		Registry(std::string id) { mod_id_ = id; };

		/**
		 * @brief Generates the json file
		 *
		 * @param id The name of the identifier, omit the namespace
		 * 
		 * @param object Class Objects such as Blocks, items, etc
		 */
		void Subscribe(std::string id, std::variant<Block*, Item*> object) {
			if (!registry_.empty() && registry_.count(id)) {
				adk::log::error("{} has already been defined!", id);
				exit(EXIT_FAILURE);
			}

			std::visit(
				[=](auto&& content) {
					adk::log::info("Creating {} - {}:{}", content->getType(), mod_id_, id);
					registry_[mod_id_ + ":" + id] = content;

					if (!fs::exists("./BP/" + content->getType() + "s/"))
						fs::create_directory("./BP/" + content->getType() + "s/");

					std::ofstream output("./BP/" + content->getType() + "s/" + id +
						".json");
					output << content->Generate(mod_id_, id).dump();
					output.close();
				},
				object);
		};

		/**
		 * @brief Gets the Registry
		 *
		 * @return std::map<std::string, std::variant<Block*, Item*>>
		 */
		std::map<std::string, std::variant<Block*, Item*>> GetRegistry() {
			return registry_;
		};

		/**
		 * @brief Get the instance of ID from the Registry
		 * 
		 * @param id The name of the identifier, including the namespace
		 * 
		 * @return std::variant<Block*, Item*>
		*/
		std::variant<Block*, Item*> get(std::string id) {
			if (registry_.count(id))
				return registry_[id];
			else {
				adk::log::error("{} has not been defined!", id);
				exit(EXIT_FAILURE);
			}
		}

	private:
		std::string mod_id_;
		std::map<std::string, std::variant<Block*, Item*>> registry_;
	};
} // namespace adk