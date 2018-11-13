/*
 * =====================================================================================
 *
 *       Filename:  SongController.cpp
 *
 *    Description:
 *
 *        Created:  13/11/2018 11:32:21
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "GameClock.hpp"
#include "SongController.hpp"

SongController::SongController() {
	m_music.openFromFile("charts/WakingTheDemon/song.ogg");

	m_previousFrameTime = GameClock::getTicks();
	m_lastReportedPlayheadPosition = 0;
	m_music.play();
}

void SongController::update() {
	m_songTime += GameClock::getTicks() - m_previousFrameTime;
	m_previousFrameTime = GameClock::getTicks();
	if ((u32)m_music.getPlayingOffset().asMilliseconds() != m_lastReportedPlayheadPosition) {
		m_songTime = (m_songTime + m_music.getPlayingOffset().asMilliseconds()) / 2;
		m_lastReportedPlayheadPosition = m_music.getPlayingOffset().asMilliseconds();
	}
}

