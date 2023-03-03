#ifndef ITEMPROPERTY_H
#define ITEMPROPERTY_H

#include <string>
#include <vector>

/**
 * @brief Represents dye color in Minecraft
 *
 */
enum class Dye {
    BLACK,
    RED,
    GREEN,
    BROWN,
    BLUE,
    PURPLE,
    CYAN,
    SILVER,
    GRAY,
    PINK,
    LIME,
    YELLOW,
    LIGHTBLUE,
    MAGENTA,
    ORANGE,
    WHITE
};

/**
 * @brief Get the Dye object
 *
 * @param dye enum Dye
 * @return std::string
 */
std::string getDye(Dye dye) {
    switch (dye) {
        case Dye::BLACK:
            return "black";
        case Dye::RED:
            return "red";
        case Dye::GREEN:
            return "green";
        case Dye::BROWN:
            return "brown";
        case Dye::BLUE:
            return "blue";
        case Dye::PURPLE:
            return "purple";
        case Dye::CYAN:
            return "cyan";
        case Dye::SILVER:
            return "silver";
        case Dye::GRAY:
            return "gray";
        case Dye::PINK:
            return "pink";
        case Dye::LIME:
            return "lime";
        case Dye::YELLOW:
            return "yellow";
        case Dye::LIGHTBLUE:
            return "lightblue";
        case Dye::MAGENTA:
            return "magenta";
        case Dye::ORANGE:
            return "orange";
        case Dye::WHITE:
            return "white";
        default:
            return "Error";
    }
}

/**
 * @brief Represents item properties such as icon, stack size, etc
 *
 */
class ItemProperty {
   private:
    std::string display_name;
    std::string icon;
    int stack;
    std::string block_placer;
    std::vector<std::string> block_placer_placement;
    std::string cooldown_category;
    float cooldown_time;
    std::string dye;
    std::string entity_placer;
    std::vector<std::string> entity_placer_placement;
    std::vector<std::string> entity_placer_dispense;
    std::vector<double> offset_main;
    std::vector<double> offset_offhand;

   public:
    /**
     * @brief Set the "display_name" component
     *
     * @param name Display Name item component. Display Names set the name to
     * display when an item is in use or hovered over.
     * @return ItemProperty
     */
    ItemProperty setName(std::string name) {
        this->display_name = name;
        return *this;
    }

    /**
     * @brief Set the "icon" object
     *
     * @param icon The icon item component determines the icon to represent the
     item.
     * @return ItemProperty
     */
    ItemProperty setIcon(std::string icon) {
        this->icon = icon;
        return *this;
    }

    /**
     * @brief Set the "max_stack_size" object
     *
     * @param stack_size The max stack size this item can hold
     * @return ItemProperty
     */
    ItemProperty setStack(int stack_size) {
        this->stack = stack_size;
        return *this;
    }

    /**
     * @brief Set the "block_placer" object
     *
     * @param block Set the placement block name for the planter item
     * @param placement List of block descriptors that contain blocks that this
     * item can be used on. If left empty, all blocks will be allowed.
     * @return ItemProperty
     */
    ItemProperty setBlockPlacer(std::string block,
                                std::vector<std::string> placement) {
        this->block_placer = block;
        this->block_placer_placement = placement;
        return *this;
    }

    /**
     * @brief Set the "cooldown" object
     *
     * @param category The type of cool down for this item
     * @param time The duration of time this item will spend cooling down before
     * becoming usable again
     * @return ItemProperty
     */
    ItemProperty setCooldown(std::string category, float time) {
        this->cooldown_category = category;
        this->cooldown_time = time;
        return *this;
    }

    /**
     * @brief Set the "dye_powder" object
     *
     * @param dye enum Dye
     * @return ItemProperty
     */
    ItemProperty setDye(Dye dye) {
        this->dye = getDye(dye);
        return *this;
    }

    /**
     * @brief Set the "entity_placer" object
     *
     * @param entity The entity to be placed in the world
     * @param placement List of block descriptors that contain blocks that this
     * item can be used on. If left empty, all blocks will be allowed
     * @param dispense List of block descriptors that contain blocks that this
     * item can be dispensed on. If left empty, all blocks will be allowed
     * @return ItemProperty
     */
    ItemProperty setEntityPlacer(std::string entity,
                                 std::vector<std::string> placement,
                                 std::vector<std::string> dispense) {
        this->entity_placer = entity;
        this->entity_placer_placement = placement;
        this->entity_placer_dispense = dispense;
        return *this;
    }

    /**
     * @brief Set the "render_offsets" object - main hand
     *
     * @param offset Main hand transform data.
     * @return ItemProperty
     */
    ItemProperty setRenderMain(std::vector<double> offset) {
        this->offset_main = offset;
        return *this;
    }

    /**
     * @brief Set the "render_offsets" object - off hand
     *
     * @param offset Off hand transform data.
     * @return ItemProperty
     */
    ItemProperty setRenderOffhand(std::vector<double> offset) {
        this->offset_offhand = offset;
        return *this;
    }

    std::string getName() { return display_name; }

    std::string getIcon() { return icon; }

    int getStack() { return stack; }

    std::string getBlockPlacer() { return block_placer; }

    std::vector<std::string> getBlockPlacerPlacement() {
        return block_placer_placement;
    }

    std::string getCooldownCategory() { return cooldown_category; }

    float getCooldownTime() { return cooldown_time; }

    std::string getDyeProperty() { return dye; }

    std::string getEntityPlacer() { return entity_placer; }

    std::vector<std::string> getEntityPlacerPlacement() {
        return entity_placer_placement;
    }

    std::vector<std::string> getEntityPlacerDispense() {
        return entity_placer_dispense;
    }

    std::vector<double> getOffsetMain() { return offset_main; }

    std::vector<double> getOffsetOff() { return offset_offhand; }
};

#endif