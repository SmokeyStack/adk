cmake_minimum_required(VERSION 3.12)

set(Headers
    ../adk/data/include/ArmorItem.h
    ../adk/data/include/ArmorType.h
    ../adk/data/include/AxisBlock.h
    ../adk/data/include/Block.h
    ../adk/data/include/BlockCategory.h
    ../adk/data/include/BlockProperty.h
    ../adk/data/include/BushBlock.h
    ../adk/data/include/CandleBlock.h
    ../adk/data/include/DurabilityItem.h
    ../adk/data/include/FoodItem.h
    ../adk/data/include/GlassBlock.h
    ../adk/data/include/HeadBlock.h
    ../adk/data/include/Item.h
    ../adk/data/include/ItemProperty.h
    ../adk/data/include/json.hpp
    ../adk/data/include/Registry.h
    ../adk/data/include/SaplingBlock.h
    ../adk/data/include/ShapedRecipeBuilder.h
    ../adk/data/include/SlabBlock.h
    ../adk/data/include/ToolItem.h
    ../adk/data/include/generator/BlockState.h
    ../adk/data/include/generator/ItemState.h
)

add_executable(BlockTest BlockTest.cpp ${Headers})
target_link_libraries(BlockTest PUBLIC
    gtest_main
    adkhead
)

add_test(
    NAME BlockTest
    COMMAND BlockTest
)

add_executable(ItemTest ItemTest.cpp ${Headers})
target_link_libraries(ItemTest PUBLIC
    gtest_main
    adkhead
)
