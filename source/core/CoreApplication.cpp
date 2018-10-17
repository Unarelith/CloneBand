/*
 * =====================================================================================
 *
 *       Filename:  CoreApplication.cpp
 *
 *    Description:
 *
 *        Created:  09/04/2018 20:16:45
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "AudioPlayer.hpp"
#include "CoreApplication.hpp"
#include "GamePad.hpp"
#include "Mouse.hpp"

CoreApplication::CoreApplication(int, char **) {
}

void CoreApplication::init() {
	std::srand(std::time(nullptr));

	Mouse::setWindow(m_window);

	GamePad::init(m_keyboardHandler);

	ApplicationStateStack::setInstance(m_stateStack);
	ResourceHandler::setInstance(m_resourceHandler);
}

int CoreApplication::run() {
	try {
		init();
		mainLoop();
	}
	catch(const Exception &e) {
		std::cerr << "Fatal error " << e.what() << std::endl;
		return 1;
	}
	catch(const std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 1;
	}
	catch(...) {
		std::cerr << "Fatal error: Unknown error." << std::endl;
		return 1;
	}

	return 0;
}

void CoreApplication::createWindow(u16 screenWidth, u16 screenHeight, const char *windowTitle) {
	m_window.create(sf::VideoMode(screenWidth, screenHeight), windowTitle, sf::Style::Close);
	m_window.setKeyRepeatEnabled(false);
}

void CoreApplication::handleEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::GainedFocus) {
			AudioPlayer::resumeMusic();
		}
		else if (event.type == sf::Event::LostFocus) {
			AudioPlayer::pauseMusic();
		}

		if (!m_stateStack.empty())
			m_stateStack.top().onEvent(event);

		m_keyboardHandler.updateState(event);

		if (event.type == sf::Event::Closed
		|| (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			m_window.close();
	}
}

void CoreApplication::mainLoop() {
	while(m_window.isOpen() && m_stateStack.size()) {
		handleEvents();

		m_clock.updateGame([&] {
			if (!m_stateStack.empty())
				m_stateStack.top().update();

			m_stateStack.clearDeletedStates();
		});

		m_clock.drawGame([&] {
			m_window.clear();

			if(!m_stateStack.empty())
				m_window.draw(m_stateStack.top());

			m_window.display();
		});
	}
}

