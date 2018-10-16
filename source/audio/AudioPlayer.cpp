/*
 * =====================================================================================
 *
 *       Filename:  AudioPlayer.cpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 04:48:48
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <SFML/Audio/Music.hpp>

#include "AudioPlayer.hpp"
#include "ResourceHandler.hpp"

bool AudioPlayer::s_muteState = false;
bool AudioPlayer::s_isPaused = false;
std::string AudioPlayer::s_currentMusic;

void AudioPlayer::playMusic(const std::string &resourceName) {
	if (!s_muteState) {
		if (!s_currentMusic.empty())
			ResourceHandler::getInstance().get<sf::Music>(s_currentMusic).stop();

		ResourceHandler::getInstance().get<sf::Music>(resourceName).setVolume(70);

		if (!s_isPaused)
			ResourceHandler::getInstance().get<sf::Music>(resourceName).play();

		s_currentMusic = resourceName;
	}
}

void AudioPlayer::pauseMusic() {
	if (!s_currentMusic.empty())
		ResourceHandler::getInstance().get<sf::Music>(s_currentMusic).pause();

	s_isPaused = true;
}

void AudioPlayer::resumeMusic() {
	if (!s_currentMusic.empty() && !s_muteState)
		ResourceHandler::getInstance().get<sf::Music>(s_currentMusic).play();

	s_isPaused = false;
}

void AudioPlayer::playSound(const std::string &resourceName) {
	if (!s_muteState && !s_isPaused)
		ResourceHandler::getInstance().get<sf::Music>(resourceName).play();
}

