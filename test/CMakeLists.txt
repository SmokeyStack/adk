cmake_minimum_required(VERSION 3.12)

set(This BlockTests)

set(Sources
    AdkTest.cpp
)

set(Headers
    ../adk/data/include/ArmorItem.h
    ../adk/data/include/ArmorType.h
    ../adk/data/include/AxisBlock.h
    ../adk/data/include/Block.h
    ../adk/data/include/BlockCategory.h
    ../adk/data/include/BlockProperty.h
    ../adk/data/include/BushBlock.h
    ../adk/data/include/CandleBlock.h
    ../adk/data/include/GlassBlock.h
    ../adk/data/include/HeadBlock.h
    ../adk/data/include/Item.h
    ../adk/data/include/ItemProperty.h
    ../adk/data/include/json.hpp
    ../adk/data/include/Registry.h
    ../adk/data/include/SaplingBlock.h
    ../adk/data/include/ShapedRecipeBuilder.h
    ../adk/data/include/SlabBlock.h
    ../adk/data/include/generator/BlockState.h
    ../adk/data/include/generator/ItemState.h
)

add_executable(${This} ${Sources} ${Headers})
target_link_libraries(${This} PUBLIC
    gtest_main
    adkhead
)

add_test(
    NAME ${This}
    COMMAND ${This}
)