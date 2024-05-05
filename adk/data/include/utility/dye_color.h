#pragma once

#include <string>

namespace adk {
    enum class DyeColor {
        Black,
        Blue,
        Brown,
        Cyan,
        Gray,
        Green,
        LightBlue,
        Lime,
        Magenta,
        Orange,
        Pink,
        Purple,
        Red,
        Silver,
        White,
        Yellow,
	};

	inline std::string GetDyeColor(DyeColor color) {
		switch (color) {
			case DyeColor::Black: return "black";
			case DyeColor::Blue: return "blue";
			case DyeColor::Brown: return "brown";
			case DyeColor::Cyan: return "cyan";
			case DyeColor::Gray: return "gray";
			case DyeColor::Green: return "green";
			case DyeColor::LightBlue: return "light_blue";
			case DyeColor::Lime: return "lime";
			case DyeColor::Magenta: return "magenta";
			case DyeColor::Orange: return "orange";
			case DyeColor::Pink: return "pink";
			case DyeColor::Purple: return "purple";
			case DyeColor::Red: return "red";
			case DyeColor::Silver: return "silver";
			case DyeColor::White: return "white";
			case DyeColor::Yellow: return "yellow";
		}
	}
} // namespace adk