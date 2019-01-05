/*
 * =====================================================================================
 *
 *       Filename:  Highway.cpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 13:04:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>

#include <gk/core/Debug.hpp>
#include <gk/core/GameClock.hpp>

#include "GameSettings.hpp"
#include "Highway.hpp"
#include "TickUtils.hpp"

Highway::Highway(const Chart &chart) : m_chart(chart) {
	float backgroundScale = 1.5;
	m_background1.setScale(backgroundScale, backgroundScale);
	m_background2.setScale(backgroundScale, backgroundScale);

	// m_background1.setColor(Color(127, 127, 127));
	// m_background2.setColor(Color(127, 127, 127));

	m_background1.setPosition(m_frets[0].width() * 5 / 2 - m_background1.width() / 2, 0);
	m_background2.setPosition(m_frets[0].width() * 5 / 2 - m_background1.width() / 2, -m_background1.height());

	m_sideBars.setScale(0.71, 0.71);
	m_sideBars.setPosition(m_background1.getPosition().x, 0);

	m_centerLines.setScale(1.16, 1.16);
	m_centerLines.setPosition(0, 0);

	for (u8 i = 0 ; i < 5 ; ++i) {
		m_frets[i].setPosition(i * m_frets[0].width() + 32, 1010);
	}

	// setRotation(-30.0f, glm::vec3{1, 0, 0});
	// setRotation(-30.0f, Vector3{1, 0, 0});
}

void Highway::onEvent(const SDL_Event &event) {
	handleKeyboard(event);
	handleGamepad(event);
}

void Highway::handleKeyboard(const SDL_Event &event) {
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		int key = -1;

		if (event.key.keysym.sym == SDLK_h) key = 0;
		if (event.key.keysym.sym == SDLK_j) key = 1;
		if (event.key.keysym.sym == SDLK_k) key = 2;
		if (event.key.keysym.sym == SDLK_l) key = 3;
		if (event.key.keysym.sym == SDLK_m) key = 4;

		if (key != -1) {
			if (event.type == SDL_KEYDOWN) {
				m_frets[key].setPressedState(true);
				keyPressed(key);
			} else {
				m_frets[key].setPressedState(false);
				keyReleased(key);
			}
		}
	}
}

void Highway::handleGamepad(const SDL_Event &event) {
	static int key = -1;

	if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP) {
		key = -1;

		if (event.jbutton.button == 0) key = 0;
		if (event.jbutton.button == 1) key = 1;
		if (event.jbutton.button == 3) key = 2;
		if (event.jbutton.button == 2) key = 3;
		if (event.jbutton.button == 4) key = 4;

		if (key != -1) {
			if (event.type == SDL_JOYBUTTONDOWN) {
				m_frets[key].setPressedState(true);
			} else {
				m_frets[key].setPressedState(false);
				keyReleased(key);
			}
		}
	}
	else if (event.type == SDL_JOYAXISMOTION && event.jaxis.axis == 7 && event.jaxis.value) {
		int i;
		for (i = 4 ; i >= 0 ; i--) {
			if (m_frets[i].isPressed()) {
				keyPressed(i);
				return;
			}
		}
	}
}

void Highway::keyPressed(u8 key) {
	auto it = std::find_if(m_noteQueue.begin(), m_noteQueue.end(), [key](Note &note) {
		// DEBUG(note.note().position, note.note().type, key);
		return note.note().type == key;
	});

	if (it != m_noteQueue.end()) {
		u64 time = gk::GameClock::getTicks();
		// DEBUG((int)key, time, it->note().time, it->note().position);
		if (time < it->note().time + 150
		 && time > it->note().time - 150) {
			// DEBUG("lol", key, it->note().type);
			m_frets[key].setFireState(true);
			m_noteQueue.erase(it);
		}
	}
}

void Highway::keyReleased(u8) {
}

void Highway::update(u32 songTime) {
	for (u8 i = 0 ; i < 5 ; ++i)
		m_frets[i].update();

	// FIXME: Use note speed instead of an arbitrary value
	const ChartNote *nextNote = m_chart.getNextNote(songTime + 2000);
	if (nextNote && (m_noteQueue.empty() || m_noteQueue.back().note().id != nextNote->id)) {
		m_noteQueue.emplace_back(*nextNote);
	}

	// FIXME: Use note speed instead of an arbitrary value
	if (!m_noteQueue.empty() && m_noteQueue.front().note().time + 1000 < songTime) {
		// DEBUG(m_noteQueue.front().note().position);
		m_noteQueue.pop_front();
	}

	for (auto &it : m_noteQueue) {
		float y = 1000 + TickUtils::timeToWorldYPosition(((int)songTime - (int)it.note().time));
		it.setPosition(it.note().type * m_frets[0].width() + 32, y);
	}

	m_background1.setPosition(m_background1.getPosition().x, (int)TickUtils::timeToWorldYPosition(songTime) % m_background1.height());
	m_background2.setPosition(m_background2.getPosition().x, (int)TickUtils::timeToWorldYPosition(songTime) % m_background1.height() - m_background1.height());
}

void Highway::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_background1, states);
	target.draw(m_background2, states);
	target.draw(m_sideBars, states);
	target.draw(m_centerLines, states);

	for (auto &it : m_frets)
		target.draw(it, states);

	for (auto &it : m_noteQueue)
		target.draw(it, states);
}

