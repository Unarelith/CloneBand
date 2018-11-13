/*
 * =====================================================================================
 *
 *       Filename:  SongController.hpp
 *
 *    Description:
 *
 *        Created:  13/11/2018 11:32:02
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SONGCONTROLLER_HPP_
#define SONGCONTROLLER_HPP_

#include <SFML/Audio.hpp>

#include "Chart.hpp"

class SongController {
	public:
		SongController();

		void update();

		u32 songTime() const { return m_songTime; }
		// u32 songTime() const { return m_music.getPlayingOffset().asMilliseconds(); }

		const Chart &chart() const { return m_chart; }

	private:
		sf::Music m_music;
		Chart m_chart{"charts/WakingTheDemon/notes.chart"};

		u32 m_previousFrameTime = 0;
		u32 m_lastReportedPlayheadPosition = 0;
		u32 m_songTime = 0;
};

#endif // SONGCONTROLLER_HPP_
