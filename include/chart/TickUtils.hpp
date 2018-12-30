/*
 * =====================================================================================
 *
 *       Filename:  TickUtils.hpp
 *
 *    Description:
 *
 *        Created:  09/11/2018 18:40:19
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TICKUTILS_HPP_
#define TICKUTILS_HPP_

#include <gk/core/IntTypes.hpp>

// Utility functions copied from Moonscraper
namespace TickUtils {
	const float SECONDS_PER_MINUTE = 60.0f;

	double disToTime(u64 tickStart, u64 tickEnd, float resolution, float bpm);
	double disToBpm(u64 tickStart, u64 tickEnd, double deltatime, double resolution);
	u64 timeToDis(float timeStart, float timeEnd, float resolution, float bpm);

	float worldYPositionToTime(float worldYPosition);
	float timeToWorldYPosition(float time);

	u64 tickScaling(u64 tick, float originalResolution, float outputResolution);
}

#endif // TICKUTILS_HPP_
