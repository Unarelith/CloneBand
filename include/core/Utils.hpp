/*
 * =====================================================================================
 *
 *       Filename:  Utils.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:53:06
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <cstring>

#define _FILE_ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

template<typename T>
sf::Rect<T> operator+(const sf::Rect<T> &rect, const sf::Vector2<T> &vec) {
	return sf::Rect<T>(rect.left + vec.x, rect.top + vec.y, rect.width, rect.height);
}

template<typename T>
sf::Rect<T> operator+=(sf::Rect<T> &rect, const sf::Vector2<T> &vec) {
	rect = rect + vec;
	return rect;
}

#endif // UTILS_HPP_
