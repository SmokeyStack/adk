#ifndef BLOCKPROPERTY_h
#define BLOCKPROPERTY_h

#include <string>
#include <variant>
#include <vector>

#include "BlockCategory.h"
#include "json.hpp"

/// @brief Turns enum CreativeTab into string
/// @param tab enum CreativeTab
/// @return String equivalent
std::string getCreativeTab(adk::CreativeTab tab) {
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

/// @brief Turns enum CreativeCategory into string
/// @param tab enum CreativeCategory
/// @return String equivalent
std::string getCreativeCategory(adk::CreativeCategory category) {
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
        default:
            return "Error";
    }
}

/// @brief Class that represents properties such as destroy speed, loot, etc
class BlockProperty {
   public:
    class Property {
       public:
        int block_light_filter = 15;
        nlohmann::json::object_t crafting = {
            {"crafting_table", {"crafting_table"}}, {"table_name", "Foo Bar"}};
        nlohmann::json::object_t explosion = {{"explosion_resistance", 0}};
        nlohmann::json::object_t mining = {{"seconds_to_destroy", 0.0}};
        std::string display_name = "";
        nlohmann::json::object_t flammable = {{"catch_chance_modifier", 5},
                                              {"destroy_chance_modifier", 20}};
        double friction = 0.4;
        std::string geometry = "";
        int light_emission = 0;
        std::string loot = "";
        std::string color = "";
        std::vector<int> rotation = {0, 0, 0};
        std::variant<bool, nlohmann::json::object_t> does_collide{true},
            collision;
        std::variant<bool, nlohmann::json::object_t> is_selectable{true},
            selection;
        std::string tab = "";
        std::string category = "";

        /// @brief Sets "light_dampening" component
        /// @param blf The amount that light will be dampened when it
        /// passes through the block, in a range (0-15). Higher value
        /// means the light will be dampened more.
        Property setBlockLightFilter(int blf) {
            this->block_light_filter = blf;
            return *this;
        }

        /// @brief Sets "crafting_table" component
        /// @param tags Defines the tags recipes should define to be crafted on
        /// this table. Limited to 64 tags. Each tag is limited to 64
        /// characters.
        /// @param name Specifies the language file key that maps to what text
        /// will be displayed in the UI of this table. If the string given can
        /// not be resolved as a loc string, the raw string given will be
        /// displayed. If this field is omitted, the name displayed will default
        /// to the name specified in the "display_name" component. If this block
        /// has no "display_name" component, the name displayed will default to
        /// the name of the block.
        Property setCrafting(std::vector<std::string>& tags, std::string name) {
            this->crafting = {{"crafting_table", tags}, {"table_name", name}};
            return *this;
        }

        /// @brief Sets "destructible_by_explosion" component
        /// @param e Sets the explosion resistance for the block.
        /// Greater values result in greater resistance to explosions. The scale
        /// will be different for different explosion power levels. A negative
        /// value or 0 means it will easily explode; larger numbers increase
        /// level of resistance.
        Property setExplosion(float e) {
            this->explosion = {{"explosion_resistance", e}};
            return *this;
        }

        /// @brief Sets "destructible_by_mining" component
        /// @param m Sets the number of seconds it takes to destroy the block
        /// with base equipment. Greater numbers result in greater mining times.
        Property setMining(float m) {
            this->mining = {{"seconds_to_destroy", m}};
            return *this;
        }

        /// @brief Sets "display_name" component
        /// @param n Specifies the language file key that maps to what text will
        /// be displayed when you hover over the block in your inventory and
        /// hotbar. If the string given can not be resolved as a loc string, the
        /// raw string given will be displayed. If this component is omitted,
        /// the name of the block will be used as the display name.
        Property setName(std::string n) {
            this->display_name = n;
            return *this;
        }

        /// @brief Sets "flammable" component
        /// @param catch_chance A modifier affecting the chance that this block
        /// will catch flame when next to a fire. Values are greater than or
        /// equal to 0, with a higher number meaning more likely to catch on
        /// fire. For a "catch_chance_modifier" greater than 0, the fire will
        /// continue to burn until the block is destroyed (or it will burn
        /// forever if the "destroy_chance_modifier" is 0). If the
        /// "catch_chance_modifier" is 0, and the block is directly ignited, the
        /// fire will eventually burn out without destroying the block (or it
        /// will have a chance to be destroyed if "destroy_chance_modifier" is
        /// greater than 0). The default value of 5 is the same as that of
        /// Planks.
        /// @param destroy A modifier affecting the chance that this block will
        /// be destroyed by flames when on fire. Values are greater than or
        /// equal to 0, with a higher number meaning more likely to be destroyed
        /// by fire. For a "destroy_chance_modifier" of 0, the block will never
        /// be destroyed by fire, and the fire will burn forever if the
        /// "catch_chance_modifier" is greater than 0. The default value of 20
        /// is the same as that of Planks.
        Property setFlammable(int catch_chance, int destroy) {
            this->flammable = {{"catch_chance_modifier", catch_chance},
                               {"destroy_chance_modifier", destroy}};
            return *this;
        }

        /// @brief Sets "friction" component
        /// @param f Describes the friction for this block in a range of
        /// (0.0-0.9). Friction affects an entity's movement speed when it
        /// travels on the block. Greater value results in more friction.
        Property setFriction(double f) {
            this->friction = f;
            return *this;
        }

        /// @brief Sets "geometry" component
        /// @param g The description identifier of the geometry file to use to
        /// render this block. This identifier must match an existing geometry
        /// identifier in any of the currently loaded resource packs.
        Property setGeometry(std::string g) {
            this->geometry = g;
            return *this;
        }

        /// @brief Sets "light_emission" component
        /// @param le The amount of light this block will emit in a range
        /// (0-15). Higher value means more light will be emitted.
        Property setLightEmission(int le) {
            this->light_emission = le;
            return *this;
        }

        /// @brief Sets "loot" component
        /// @param l The path to the loot table, relative to the behavior pack.
        /// Path string is limited to 256 characters.
        Property setLoot(std::string l) {
            this->loot = l;
            return *this;
        }

        /// @brief Sets "map_color" component
        /// @param c Sets the color of the block when rendered to a map. The
        /// color is represented as a hex value in the format "#RRGGBB". If this
        /// component is omitted, the block will not show up on the map.
        Property setColor(std::string c) {
            this->color = c;
            return *this;
        }

        /// @brief Sets "rotation" component
        /// @param r The block's rotation around the center of the cube in
        /// degrees. The rotation is specified as [x, y, z]. Angles need to be
        /// in factors of 90.
        Property setRotation(std::vector<int> r) {
            this->rotation = r;
            return *this;
        }

        Property setCollision(bool origin) {
            this->does_collide = origin;
            return *this;
        }

        Property setCollision(std::vector<int> b, std::vector<int> c) {
            nlohmann::json::object_t temp = {{"origin", b}, {"size", c}};
            this->collision = temp;
            return *this;
        }

        Property setSelection(bool origin) {
            this->is_selectable = origin;
            return *this;
        }

        Property setSelection(std::vector<int> b, std::vector<int> c) {
            nlohmann::json::object_t temp = {{"origin", b}, {"size", c}};
            this->selection = temp;
            return *this;
        }

        Property setTab(adk::CreativeTab tab) {
            this->tab = getCreativeTab(tab);
            return *this;
        }

        Property setCategory(adk::CreativeCategory category) {
            this->category = getCreativeCategory(category);
            return *this;
        }
    };
};

#endif