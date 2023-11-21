//#ifndef ITEMCOMPONENT_H
//#define ITEMCOMPONENT_H
//
//#include <spdlog/spdlog.h>
//
//#include <string>
//#include <vector>
//
//#include "json.hpp"
//
//class ItemComponent {
//   public:
//    /**
//     * @brief
//     *
//     * @param value
//     * @return nlohmann::json::object_t
//     */
//    nlohmann::json::object_t allowOffHand(bool value) {
//        nlohmann::json::object_t temp = {{"minecraft:allow_off_hand", value}};
//
//        return temp;
//    }
//
//    nlohmann::json::object_t blockPlacer(std::string block) {
//        nlohmann::json::object_t temp = {
//            {"minecraft:block_placer", {{"block", block}}}};
//
//        return temp;
//    }
//
//    nlohmann::json::object_t blockPlacer(std::string block,
//                                         std::vector<std::string> used_on) {
//        nlohmann::json::object_t temp = {
//            {"minecraft:block_placer",
//             {{"block", block}, {"used_on", used_on}}}};
//
//        return temp;
//    }
//
//    nlohmann::json::object_t destroyInCreative(bool value) {
//        nlohmann::json::object_t temp = {
//            {"minecraft:can_destroy_in_creative", value}};
//
//        return temp;
//    }
//
//    nlohmann::json::object_t cooldown(std::string category, float duration) {
//        nlohmann::json::object_t temp = {
//            {"minecraft:cooldown",
//             {{"category", category}, {"duration", duration}}}};
//
//        return temp;
//    }
//
//    nlohmann::json::object_t damage(int value) {
//        nlohmann::json::object_t temp = {{"minecraft:damage", value}};
//
//        return temp;
//    }
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//
//    nlohmann::json::object_t blockPlacer() {}
//};
//
//#endif