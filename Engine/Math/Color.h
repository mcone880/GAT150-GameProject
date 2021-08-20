#pragma once
#include <iostream>
#include "SDL.h"


namespace MAC {

	struct Color {

		float r, g, b; 

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {}
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {}
		Color(std::uint32_t rgb) // uint32_t( x | b | g | r ) 
		{
			r = (rgb & 0xFF) / 255.0f;		   // 0 - 255 -> 0 - 1
			g = ((rgb >> 8) & 0xFF) / 255.0f;  // 0 - 255 -> 0 - 1
			b = ((rgb >> 16) & 0xFF) / 255.0f; // 0 - 255 -> 0 - 1
		}

		float operator [] (size_t index) const { return (&r)[index]; }
		float& operator [] (size_t index) { return (&r)[index]; }

		operator SDL_Color() const
		{
			SDL_Color color;
			color.r = static_cast<Uint8>(r * 255);
			color.g = static_cast<Uint8>(g * 255);
			color.b = static_cast<Uint8>(g * 255);
			color.a = 255;

			return color;
		}

		Color operator + (const Color& color) const { return { r + color.r, g + color.g, b + color.b }; }
		Color operator - (const Color& color) const { return { r - color.r, g - color.g, b - color.b }; }
		Color operator * (float s) const { return { r * s, g * s, b * s }; }
		operator uint32_t() const { return toRGB(); }

		uint32_t toRGB() const {
			std::uint8_t red = static_cast<std::uint8_t>(r * 255); // 0 - 1 -> 0 - 255
			std::uint8_t green = static_cast<std::uint8_t>(g * 255); // 0 - 1 -> 0 - 255
			std::uint8_t blue = static_cast<std::uint8_t>(b * 255); // 0 - 1 -> 0 - 255

			return (red | green << 8 | blue << 16);
		}

		friend std::istream& operator >> (std::istream& stream, Color& c);
		friend std::ostream& operator << (std::ostream& stream, Color& c);

		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color purple;
		static const Color cyan;
		static const Color orange;
		static const Color yellow;
	};

}