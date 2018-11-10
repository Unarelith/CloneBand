/*
 * =====================================================================================
 *
 *       Filename:  TickUtils.cpp
 *
 *    Description:
 *
 *        Created:  09/11/2018 18:40:30
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <cmath>

#include "GameSettings.hpp"
#include "TickUtils.hpp"

double TickUtils::disToTime(u64 tickStart, u64 tickEnd, float resolution, float bpm) {
	return (tickEnd - tickStart) / resolution * SECONDS_PER_MINUTE / bpm;
}

double TickUtils::disToBpm(u64 tickStart, u64 tickEnd, double deltatime, double resolution) {
	return (tickEnd - tickStart) / resolution * SECONDS_PER_MINUTE / deltatime;
}

u64 TickUtils::timeToDis(float timeStart, float timeEnd, float resolution, float bpm) {
	return (u64)roundf((timeEnd - timeStart) * bpm / SECONDS_PER_MINUTE * resolution);
}

float TickUtils::worldYPositionToTime(float worldYPosition) {
	return worldYPosition / (GameSettings::hyperspeed / GameSettings::gameSpeed);
}

float TickUtils::timeToWorldYPosition(float time) {
	return time * GameSettings::hyperspeed / GameSettings::gameSpeed;
}

u64 TickUtils::tickScaling(u64 tick, float originalResolution, float outputResolution) {
	tick = (u64)roundf(tick * outputResolution / originalResolution);
	return tick;
}

