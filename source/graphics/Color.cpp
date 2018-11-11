/*
 * =====================================================================================
 *
 *       Filename:  Color.cpp
 *
 *    Description:
 *
 *        Created:  27/09/2014 22:35:45
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Color.hpp"

Color Color::Black(0, 0, 0);
Color Color::White(255, 255, 255);

Color Color::Green(0, 255, 0);
Color Color::Red(232, 8, 24);
Color Color::Yellow(255, 255, 0);
Color Color::Blue(32, 168, 248);
Color Color::Orange(255, 165, 0);

Color::Color(u8 _r, u8 _g, u8 _b, u8 _a) {
	r = _r / 255.0f;
	g = _g / 255.0f;
	b = _b / 255.0f;
	a = _a / 255.0f;
}

Color Color::operator-(const Color &color) {
	return Color(r - color.r, g - color.g, b - color.b, a - color.a);
}

