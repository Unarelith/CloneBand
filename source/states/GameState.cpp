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

void GameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_highway, states);
}

