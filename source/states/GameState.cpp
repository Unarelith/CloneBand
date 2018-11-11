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

#include "Config.hpp"
#include "Debug.hpp"
#include "GameClock.hpp"
#include "GameState.hpp"

GameState::GameState() {
	m_music.openFromFile("charts/WakingTheDemon/song.ogg");

	m_previousFrameTime = GameClock::getTicks();
	m_lastReportedPlayheadPosition = 0;
	m_music.play();

	m_highway.setPosition(Config::screenWidth / 2 - 5 * 136 / 2, 0);
	// m_highway.setScale(0.1, 0.1);

	m_shader.createProgram();
	m_shader.addShader(GL_VERTEX_SHADER, "resources/shaders/basic.v.glsl");
	m_shader.addShader(GL_FRAGMENT_SHADER, "resources/shaders/basic.f.glsl");
	m_shader.linkProgram();

	m_projectionMatrix2d = glm::ortho(0.0f, (float)Config::screenWidth, (float)Config::screenHeight, 0.0f);
	// m_projectionMatrix3d = glm::perspective(90.0f, (float)Config::screenWidth / Config::screenHeight, 0.1f, 3000.0f);

	// m_viewMatrix = glm::lookAt(glm::vec3(Config::screenWidth / 2.0f, Config::screenHeight / 2.0f, -1000),
	//                            glm::vec3(Config::screenWidth / 2.0f, Config::screenHeight / 2.0f, 0),
	//                            glm::vec3(0, -1, 0));

	// m_viewMatrix = glm::lookAt(glm::vec3(Config::screenWidth / 2.0f, Config::screenHeight + 100, -600),
	//                            glm::vec3(Config::screenWidth / 2.0f, Config::screenHeight / 2.0f, 0),
	//                            glm::vec3(0, -1, 0));

	// m_viewMatrix = glm::lookAt(glm::vec3(Config::screenWidth / 2.0f, Config::screenHeight + 400, -100),
	//                            glm::vec3(Config::screenWidth / 2.0f, Config::screenHeight / 2.0f, 0),
	//                            glm::vec3(0, -1, 0));

	m_camera.setAspectRatio((float)Config::screenWidth / Config::screenHeight);
	m_camera.setPosition(Config::screenWidth / 2.0f, Config::screenHeight + 100, -600);
	m_camera.setTargetPosition(Config::screenWidth / 2.0f, Config::screenHeight / 2.0f, 0);
	m_camera.setUpVector(0, -1, 0);
}

void GameState::onEvent(const sf::Event &event) {
	m_highway.onEvent(event);
}

void GameState::update() {
	m_songTime += GameClock::getTicks() - m_previousFrameTime;
	m_previousFrameTime = GameClock::getTicks();
	if ((u32)m_music.getPlayingOffset().asMilliseconds() != m_lastReportedPlayheadPosition) {
		m_songTime = (m_songTime + m_music.getPlayingOffset().asMilliseconds()) / 2;
		m_lastReportedPlayheadPosition = m_music.getPlayingOffset().asMilliseconds();
	}

	m_highway.update(m_songTime);
}

void GameState::draw(RenderTarget &target, RenderStates states) const {
	states.projectionTransform *= m_camera.getTransform();
	states.viewTransform *= m_camera.getViewTransform();

	// states.projectionTransform = m_projectionMatrix3d;
	// states.viewTransform = m_viewMatrix;

	states.shader = &m_shader;

	target.draw(m_highway, states);
}

