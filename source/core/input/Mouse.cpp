/*
 * =====================================================================================
 *
 *       Filename:  Mouse.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:24:17
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Mouse.hpp"

sf::Window *Mouse::window = nullptr;

sf::Vector2i Mouse::getPosition() {
	return sf::Mouse::getPosition(*window);
}

