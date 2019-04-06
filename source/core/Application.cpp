/*
 * =====================================================================================
 *
 *       Filename:  Application.cpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 12:27:30
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/resource/ResourceHandler.hpp>
#include <gk/resource/TextureLoader.hpp>

#include "Application.hpp"
#include "Config.hpp"

#include "GameState.hpp"

void Application::init() {
	gk::CoreApplication::init();

	createWindow(sf::VideoMode(Config::screenWidth, Config::screenHeight), Config::windowTitle, sf::Style::Close);
	// m_window.disableView();

	initOpenGL();

	m_resourceHandler.loadConfigFile<gk::TextureLoader>("resources/config/textures.xml");

	m_stateStack.push<GameState>();
}

void Application::initOpenGL() {
	// glEnable(GL_TEXTURE_2D);
    //
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //
	// glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
    //
	// glClearColor(0, 0, 0, 1.0);
}

void Application::onEvent(const sf::Event &event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
		m_isRunning = false;
	}
}

