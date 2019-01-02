/*
 * =====================================================================================
 *
 *       Filename:  GameState.cpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 12:37:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

#include <gk/system/Debug.hpp>

#include "Config.hpp"
#include "GameState.hpp"

GameState::GameState() {
	m_highway.setPosition(Config::screenWidth / 2 - 5 * 136 / 2, 0);

	m_shader.createProgram();
	m_shader.addShader(GL_VERTEX_SHADER, "resources/shaders/basic.v.glsl");
	m_shader.addShader(GL_FRAGMENT_SHADER, "resources/shaders/basic.f.glsl");
	m_shader.linkProgram();

	// m_projectionMatrix2d = glm::ortho(0.0f, (float)Config::screenWidth, (float)Config::screenHeight, 0.0f);

	m_camera.setAspectRatio((float)Config::screenWidth / Config::screenHeight);
	m_camera.setUpVector(0, -1, 0);

	// m_camera.setPosition(Config::screenWidth / 2.0f, Config::screenHeight + 400, -100);
	m_camera.setPosition(Config::screenWidth / 2.0f, Config::screenHeight + 300, -600);
	m_camera.setTargetPosition(Config::screenWidth / 2.0f, 0, 0);

	// m_camera.setPosition(Config::screenWidth / 2.0f, Config::screenHeight / 2.0f, -1000);
	// m_camera.setTargetPosition(Config::screenWidth / 2.0f, Config::screenHeight / 2.0f, 0);
}

void GameState::onEvent(const SDL_Event &event) {
	m_highway.onEvent(event);
}

void GameState::update() {
	m_songController.update();
	m_highway.update(m_songController.songTime());
}

void GameState::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	states.projectionMatrix = m_camera.getTransform();
	states.viewMatrix = m_camera.getViewTransform();

	states.shader = &m_shader;

	target.draw(m_highway, states);
}

