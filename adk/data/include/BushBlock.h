#ifndef BUSHBLOCK_H
#define BUSHBLOCK_H

#include "Block.h"
#include "BlockProperty.h"
#include "json.hpp"

/**
 * @brief Represents a Bush Block
 *
 */
class BushBlock : public Block {
   public:
    BushBlock(){};
    /**
     * @brief Construct a new Bush Block object
     *
     * @param property BlockProperty
     */
    BushBlock(BlockProperty property) {
        _internal = property;
    }

    /**
     * @brief Generates the json object
     *
     * @param mod_id Namespace identifier
     * @param id Identifier for the item
     * @return json
     */
    json output(std::string mod_id, std::string id) {
        j = Block::output(mod_id, id);
        j["minecraft:block"]["components"]["minecraft:placement_filter"]
         ["conditions"] = {{{"allowed_faces", json::array({"up"})},
                            {"block_filter",
                             json::array({{{"tags", "q.any_tag('dirt')"}},
                                          {{"tags", "q.any_tag('grass')"}}})}}};

        return j;
    }
};

#endif