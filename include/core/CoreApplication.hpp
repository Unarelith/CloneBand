/*
 * =====================================================================================
 *
 *       Filename:  CoreApplication.hpp
 *
 *    Description:
 *
 *        Created:  09/04/2018 20:16:36
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef COREAPPLICATION_HPP_
#define COREAPPLICATION_HPP_

#include <SFML/Graphics.hpp>

#include "ApplicationStateStack.hpp"
#include "GameClock.hpp"
#include "KeyboardHandler.hpp"
#include "ResourceHandler.hpp"

class CoreApplication {
	public:
		CoreApplication(int argc, char **argv);

		virtual void init();

		int run();

	protected:
		void createWindow(u16 screenWidth, u16 screenHeight, const char *windowTitle);

		sf::RenderWindow m_window;

		ApplicationStateStack m_stateStack;

		GameClock m_clock;

		KeyboardHandler m_keyboardHandler;

		ResourceHandler m_resourceHandler;

	private:
		void handleEvents();

		void mainLoop();
};

#endif // COREAPPLICATION_HPP_
