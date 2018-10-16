/*
 * =====================================================================================
 *
 *       Filename:  GameClock.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:07:16
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GAMECLOCK_HPP_
#define GAMECLOCK_HPP_

#include <functional>

#include <SFML/System.hpp>

#include "IntTypes.hpp"

class GameClock {
	public:
		static u32 getTicks(bool realTime = false);

		void measureLastFrameDuration();

		void updateGame(std::function<void(void)> updateFunc);

		void drawGame(std::function<void(void)> drawFunc);

		void waitForNextFrame();

		void setTimestep(u8 timestep) { m_timestep = timestep; }

	private:
		static sf::Clock clock;
		static u32 ticks;

		u32 m_lastFrameDate = 0;
		u32 m_lag = 0;
		u32 m_timeDropped = 0;

		u8 m_timestep = 6;
		u8 m_numUpdates = 0;
};

#endif // GAMECLOCK_HPP_
