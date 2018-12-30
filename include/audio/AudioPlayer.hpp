/*
 * =====================================================================================
 *
 *       Filename:  AudioPlayer.hpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 04:48:39
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef AUDIOPLAYER_HPP_
#define AUDIOPLAYER_HPP_

#include <string>

#include <gk/core/IntTypes.hpp>

class AudioPlayer {
	public:
		static void playMusic(const std::string &resourceName);
		static void playSound(const std::string &resourceName);

		static void pauseMusic();
		static void resumeMusic();

		static void setMuteState(bool muteState) { s_muteState = muteState; }

	private:
		static bool s_muteState;
		static bool s_isPaused;
		static std::string s_currentMusic;
};

#endif // AUDIOPLAYER_HPP_
