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
#include "Application.hpp"
#include "Config.hpp"
#include "ResourceHandler.hpp"
#include "TextureLoader.hpp"

#include "GameState.hpp"

void Application::init() {
	CoreApplication::init();

	createWindow(Config::windowTitle, Config::screenWidth, Config::screenHeight);

	m_resourceHandler.loadConfigFile<TextureLoader>("resources/config/textures.xml");

	ApplicationStateStack::getInstance().push<GameState>();
}

