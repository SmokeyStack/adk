#ifndef BLOCKCATEGORY_H
#define BLOCKCATEGORY_H

namespace adk {
enum class CreativeTab {
    COMMANDS,
    CONSTRUCTION,
    EQUIPMENT,
    ITEMS,
    NATURE,
    NONE
};
enum class CreativeCategory {
    ANVIL,
    ARROW,
    AXE,
    BANNER,
    BANNERPATTERN,
    BED,
    BOAT,
    BOOTS,
    BUTTONS,
    CANDLES,
    CHALKBOARD,
    CHEST,
    CHESTBOAT,
    CHESTPLATE,
    CONCRETE,
    CONCRETEPOWDER,
    COOKEDFOOD,
    COPPER,
    CORAL,
    CORALDECORATIONS,
    CROP,
    DOOR,
    DYE,
    ENCHANTEDBOOK,
    FENCE,
    FENCEGATE,
    FIREWORK,
    FIREWORKSTARS,
    FLOWER,
    GLASS,
    GLASSPANE,
    GLAZEDTERRACOTTA,
    GOATHORN,
    GRASS,
    HELMET,
    HOE,
    HORSEARMOR,
    LEAVES,
    LEGGINGS,
    LINGERINGPOTION,
    LOG,
    MINECART,
    MISCFOOD,
    MOBEGG,
    MONSTERSTONEEGG,
    MUSHROOM,
    NETHERWARTBLOCK,
    ORE,
    PERMISSION,
    PICKAXE,
    PLANKS,
    POTION,
    PRESSUREPLATE,
    RAIL,
    RAWFOOD,
    RECORD,
    SANDSTONE,
    SAPLING,
    SCULK,
    SEED,
    SHOVEL,
    SHULKERBOX,
    SIGN,
    SKULL,
    SLAB,
    SPLASHPOTION,
    STAINEDCLAY,
    STAIRS,
    STONE,
    STONEBRICK,
    SWORD,
    TRAPDOOR,
    WALLS,
    WOOD,
    WOOL,
    WOOLCARPET,
    NONE
};

/**
 * @brief Get the Creative Tab object
 *
 * @param tab enum CreativeTab
 * @return std::string
 */
inline std::string getCreativeTab(adk::CreativeTab tab) {
    switch (tab) {
        case adk::CreativeTab::COMMANDS:
            return "commands";
        case adk::CreativeTab::CONSTRUCTION:
            return "construction";
        case adk::CreativeTab::EQUIPMENT:
            return "equipment";
        case adk::CreativeTab::ITEMS:
            return "items";
        case adk::CreativeTab::NATURE:
            return "nature";
        case adk::CreativeTab::NONE:
            return "none";
        default:
            return "Error";
    }
}

/**
 * @brief Get the Creative Category object
 *
 * @param category enum CreativeCategory
 * @return std::string
 */
inline std::string getCreativeCategory(adk::CreativeCategory category) {
    switch (category) {
        case adk::CreativeCategory::ANVIL:
            return "itemGroup.name.anvil";
        case adk::CreativeCategory::ARROW:
            return "itemGroup.name.arrow";
        case adk::CreativeCategory::AXE:
            return "itemGroup.name.axe";
        case adk::CreativeCategory::BANNER:
            return "itemGroup.name.banner";
        case adk::CreativeCategory::BANNERPATTERN:
            return "itemGroup.name.banner_pattern";
        case adk::CreativeCategory::BED:
            return "itemGroup.name.bed";
        case adk::CreativeCategory::BOAT:
            return "itemGroup.name.boat";
        case adk::CreativeCategory::BOOTS:
            return "itemGroup.name.boots";
        case adk::CreativeCategory::BUTTONS:
            return "itemGroup.name.buttons";
        case adk::CreativeCategory::CANDLES:
            return "itemGroup.name.candles";
        case adk::CreativeCategory::CHALKBOARD:
            return "itemGroup.name.chalkboard";
        case adk::CreativeCategory::CHEST:
            return "itemGroup.name.chest";
        case adk::CreativeCategory::CHESTBOAT:
            return "itemGroup.name.chestboat";
        case adk::CreativeCategory::CHESTPLATE:
            return "itemGroup.name.chestplate";
        case adk::CreativeCategory::CONCRETE:
            return "itemGroup.name.concrete";
        case adk::CreativeCategory::CONCRETEPOWDER:
            return "itemGroup.name.concretePowder";
        case adk::CreativeCategory::COOKEDFOOD:
            return "itemGroup.name.cookedFood";
        case adk::CreativeCategory::COPPER:
            return "itemGroup.name.copper";
        case adk::CreativeCategory::CORAL:
            return "itemGroup.name.coral";
        case adk::CreativeCategory::CORALDECORATIONS:
            return "itemGroup.name.coralDecorations";
        case adk::CreativeCategory::CROP:
            return "itemGroup.name.crop";
        case adk::CreativeCategory::DOOR:
            return "itemGroup.name.door";
        case adk::CreativeCategory::DYE:
            return "itemGroup.name.dye";
        case adk::CreativeCategory::ENCHANTEDBOOK:
            return "itemGroup.name.enchantedBook";
        case adk::CreativeCategory::FENCE:
            return "itemGroup.name.fence";
        case adk::CreativeCategory::FENCEGATE:
            return "itemGroup.name.fenceGate";
        case adk::CreativeCategory::FIREWORK:
            return "itemGroup.name.firework";
        case adk::CreativeCategory::FIREWORKSTARS:
            return "itemGroup.name.fireworkStars";
        case adk::CreativeCategory::FLOWER:
            return "itemGroup.name.flower";
        case adk::CreativeCategory::GLASS:
            return "itemGroup.name.glass";
        case adk::CreativeCategory::GLASSPANE:
            return "itemGroup.name.glassPane";
        case adk::CreativeCategory::GLAZEDTERRACOTTA:
            return "itemGroup.name.glazedTerracotta";
        case adk::CreativeCategory::GOATHORN:
            return "itemGroup.name.goatHorn";
        case adk::CreativeCategory::GRASS:
            return "itemGroup.name.grass";
        case adk::CreativeCategory::HELMET:
            return "itemGroup.name.helmet";
        case adk::CreativeCategory::HOE:
            return "itemGroup.name.hoe";
        case adk::CreativeCategory::HORSEARMOR:
            return "itemGroup.name.horseArmor";
        case adk::CreativeCategory::LEAVES:
            return "itemGroup.name.leaves";
        case adk::CreativeCategory::LEGGINGS:
            return "itemGroup.name.leggings";
        case adk::CreativeCategory::LINGERINGPOTION:
            return "itemGroup.name.lingeringPotion";
        case adk::CreativeCategory::LOG:
            return "itemGroup.name.log";
        case adk::CreativeCategory::MINECART:
            return "itemGroup.name.minecart";
        case adk::CreativeCategory::MISCFOOD:
            return "itemGroup.name.miscFood";
        case adk::CreativeCategory::MOBEGG:
            return "itemGroup.name.mobEgg";
        case adk::CreativeCategory::MONSTERSTONEEGG:
            return "itemGroup.name.monsterStoneEgg";
        case adk::CreativeCategory::MUSHROOM:
            return "itemGroup.name.mushroom";
        case adk::CreativeCategory::NETHERWARTBLOCK:
            return "itemGroup.name.netherWartBlock";
        case adk::CreativeCategory::ORE:
            return "itemGroup.name.ore";
        case adk::CreativeCategory::PERMISSION:
            return "itemGroup.name.permission";
        case adk::CreativeCategory::PICKAXE:
            return "itemGroup.name.pickaxe";
        case adk::CreativeCategory::PLANKS:
            return "itemGroup.name.planks";
        case adk::CreativeCategory::POTION:
            return "itemGroup.name.potion";
        case adk::CreativeCategory::PRESSUREPLATE:
            return "itemGroup.name.pressurePlate";
        case adk::CreativeCategory::RAIL:
            return "itemGroup.name.rail";
        case adk::CreativeCategory::RAWFOOD:
            return "itemGroup.name.rawFood";
        case adk::CreativeCategory::RECORD:
            return "itemGroup.name.record";
        case adk::CreativeCategory::SANDSTONE:
            return "itemGroup.name.sandstone";
        case adk::CreativeCategory::SAPLING:
            return "itemGroup.name.sapling";
        case adk::CreativeCategory::SCULK:
            return "itemGroup.name.sculk";
        case adk::CreativeCategory::SEED:
            return "itemGroup.name.seed";
        case adk::CreativeCategory::SHOVEL:
            return "itemGroup.name.shovel";
        case adk::CreativeCategory::SHULKERBOX:
            return "itemGroup.name.shulkerBox";
        case adk::CreativeCategory::SIGN:
            return "itemGroup.name.sign";
        case adk::CreativeCategory::SKULL:
            return "itemGroup.name.skull";
        case adk::CreativeCategory::SLAB:
            return "itemGroup.name.slab";
        case adk::CreativeCategory::SPLASHPOTION:
            return "itemGroup.name.splashPotion";
        case adk::CreativeCategory::STAINEDCLAY:
            return "itemGroup.name.stainedClat";
        case adk::CreativeCategory::STAIRS:
            return "itemGroup.name.stairs";
        case adk::CreativeCategory::STONE:
            return "itemGroup.name.stone";
        case adk::CreativeCategory::STONEBRICK:
            return "itemGroup.name.stoneBrick";
        case adk::CreativeCategory::SWORD:
            return "itemGroup.name.sword";
        case adk::CreativeCategory::TRAPDOOR:
            return "itemGroup.name.trapdoor";
        case adk::CreativeCategory::WALLS:
            return "itemGroup.name.walls";
        case adk::CreativeCategory::WOOD:
            return "itemGroup.name.wood";
        case adk::CreativeCategory::WOOL:
            return "itemGroup.name.wool";
        case adk::CreativeCategory::WOOLCARPET:
            return "itemGroup.name.woolCarpet";
        case adk::CreativeCategory::NONE:
            return "itemGroup.name.woolCarpet";
        default:
            return "Error";
    }
}

}  // namespace adk
#endif