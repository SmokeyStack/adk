#ifndef BLOCK_H
#define BLOCK_H

#include <spdlog/spdlog.h>

#include <string>

#include "BlockComponent.h"
#include "BlockProperty.h"
#include "json.hpp"

/**
 * @brief Represents a Block
 *
 */
class Block {
   protected:
    BlockProperty _internal;
    BlockComponent helper;

    /**
     * @brief Ensure the collision_box and selection_box is valid
     *
     * @param component_check The vectors of origin and size
     * @param component Used to log collision or selection
     * @param id Identifier of block
     * @return true
     * @return false
     */

   public:
    using json = nlohmann::json;
    json j;
    std::string getType() { return "block"; };

    Block(){};
    /**
     * @brief Construct a new Block object
     *
     * @param property BlockProperty
     */
    Block(BlockProperty property) { _internal = property; }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return json
     */
    virtual json output(std::string mod_id, std::string id) {
        j["format_version"] = "1.20.10";
        j["minecraft:block"]["description"]["identifier"] = mod_id + ":" + id;

        if (_internal.getBlockLightFilter() != 15)
            j["minecraft:block"]["components"].update(
                helper.blockLightFilter(_internal.getBlockLightFilter(), id));

        if (_internal.getCrafting().has_value())
            j["minecraft:block"]["components"].update(
                helper.crafting(_internal.getCrafting().value()));

        if (std::get_if<bool>(&_internal.getExplosion())) {
            if (!std::get<bool>(_internal.getExplosion()))
                j["minecraft:block"]["components"].update(
                    helper.destructibleByExplosion(false));
        } else if (std::get_if<double>(&_internal.getExplosion()))
            j["minecraft:block"]["components"].update(
                helper.destructibleByExplosion(
                    std::get<double>(_internal.getExplosion())));

        if (std::get_if<bool>(&_internal.getMining())) {
            if (!std::get<bool>(_internal.getMining()))
                j["minecraft:block"]["components"].update(
                    helper.destructibleByMining(false));
        } else if (std::get_if<double>(&_internal.getMining()))
            j["minecraft:block"]["components"].update(
                helper.destructibleByMining(
                    std::get<double>(_internal.getMining())));

        if (!_internal.getName().empty())
            j["minecraft:block"]["components"].update(
                helper.displayName(_internal.getName()));

        if (_internal.getFlamamble().has_value())
            j["minecraft:block"]["components"].update(
                helper.flammable(_internal.getFlamamble().value()));

        if (_internal.getFriction() != 0.4)
            j["minecraft:block"]["components"].update(
                helper.friction(_internal.getFriction(), id));

        if (_internal.getLightEmission() != 0)
            j["minecraft:block"]["components"].update(
                helper.lightEmission(_internal.getLightEmission(), id));

        if (!_internal.getLoot().empty())
            j["minecraft:block"]["components"].update(
                helper.loot(_internal.getLoot()));

        if (!_internal.getColor().empty())
            j["minecraft:block"]["components"].update(
                helper.color(_internal.getColor()));

        if (_internal.getRotation() != std::vector<int>{0, 0, 0})
            j["minecraft:block"]["components"].update(
                helper.rotation(_internal.getRotation(), id));

        if (_internal.getTranslation() != std::vector<double>{0, 0, 0})
            j["minecraft:block"]["components"].update(
                helper.translation(_internal.getTranslation()));

        if (_internal.getScale() != std::vector<double>{0, 0, 0})
            j["minecraft:block"]["components"].update(
                helper.scale(_internal.getScale()));

        if (std::get_if<bool>(&_internal.getCollision())) {
            if (!std::get<bool>(_internal.getCollision()))
                j["minecraft:block"]["components"].update(
                    helper.collision(false, id));

        } else if (std::get_if<std::pair<std::vector<int>, std::vector<int>>>(
                       &_internal.getCollision())) {
            j["minecraft:block"]["components"].update(
                helper.collision(_internal.getCollision(), id));
        }

        if (std::get_if<bool>(&_internal.getSelection())) {
            if (!std::get<bool>(_internal.getSelection()))
                j["minecraft:block"]["components"].update(
                    helper.selection(false, id));

        } else if (std::get_if<std::pair<std::vector<int>, std::vector<int>>>(
                       &_internal.getSelection())) {
            j["minecraft:block"]["components"].update(
                helper.selection(_internal.getSelection(), id));
        }

        if (_internal.getCreative().has_value())
            j["minecraft:block"]["description"].update(
                helper.creativeMenu(_internal.getCreative().value()));

        return j;
    }
};

#endif