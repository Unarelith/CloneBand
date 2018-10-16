/*
 * =====================================================================================
 *
 *       Filename:  NetworkInputHandler.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 10:54:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORKINPUTHANDLER_HPP_
#define NETWORKINPUTHANDLER_HPP_

#include <SFML/Window/Keyboard.hpp>

#include "InputHandler.hpp"

class NetworkInputHandler : public InputHandler {
	public:
		void setKeyPressed(GameKey key, bool isPressed) {
			m_keysPressed[key] = isPressed;
		}
};

#endif // NETWORKINPUTHANDLER_HPP_
