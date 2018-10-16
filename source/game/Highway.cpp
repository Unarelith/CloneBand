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

#include "Debug.hpp"
#include "GameClock.hpp"
#include "Highway.hpp"

Highway::Highway(Chart &chart) : m_chart(chart) {
	m_border.setSize({508, 892});
	m_border.setPosition(-4, 4);
	m_border.setOutlineThickness(4);
	m_border.setOutlineColor(sf::Color::White);
	m_border.setFillColor(sf::Color::Black);

	m_strumBar.setSize({492, 100});
	m_strumBar.setPosition(4, 700);
	m_strumBar.setOutlineThickness(4);
	m_strumBar.setOutlineColor(sf::Color::White);
	m_strumBar.setFillColor(sf::Color::Black);

	for (u8 i = 0 ; i < 5 ; ++i) {
		m_keys[i].setPosition(i * 100 + 25, 725);
		m_keys[i].setSize({50, 50});
		m_keys[i].setOutlineThickness(4);
		m_keys[i].setOutlineColor(sf::Color::White);
		m_keys[i].setFillColor(sf::Color::Black);
	}
}

void Highway::onEvent(const sf::Event &event) {
	static int key = -1;
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
		key = -1;

		if (event.key.code == sf::Keyboard::H) key = 0;
		if (event.key.code == sf::Keyboard::J) key = 1;
		if (event.key.code == sf::Keyboard::K) key = 2;
		if (event.key.code == sf::Keyboard::L) key = 3;
		if (event.key.code == sf::Keyboard::M) key = 4;

		if (key != -1) {
			if (event.type == sf::Event::KeyPressed) {
				m_keys[key].setFillColor(sf::Color::White);
				keyPressed(key);
			} else {
				m_keys[key].setFillColor(sf::Color::Black);
				keyReleased(key);
			}
		}
	}
	// else if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickButtonReleased) {
	// 	key = -1;
    //
	// 	if (event.joystickButton.button == 0) key = 0;
	// 	if (event.joystickButton.button == 1) key = 1;
	// 	if (event.joystickButton.button == 2) key = 3;
	// 	if (event.joystickButton.button == 3) key = 2;
	// 	if (event.joystickButton.button == 4) key = 4;
    //
	// 	if (key != -1) {
	// 		if (event.type == sf::Event::JoystickButtonPressed) {
	// 			m_keys[key].setFillColor(sf::Color::White);
	// 		} else {
	// 			m_keys[key].setFillColor(sf::Color::Black);
	// 			keyReleased(key);
	// 		}
	// 	}
	// }
	// else if (event.type == sf::Event::JoystickMoved && event.joystickMove.axis == 7 && event.joystickMove.position) {
	// 	keyPressed(key);
	// }
}

void Highway::keyPressed(u8 key) {
	m_keys[key].setFillColor(sf::Color::White);
	auto it = std::find_if(m_noteQueue.begin(), m_noteQueue.end(), [key](Note &note) {
		// DEBUG(note.note().position, note.note().type, key);
		return note.note().type == key;
	});

	if (it != m_noteQueue.end()) {
		u64 time = GameClock::getTicks();
		// DEBUG(time, it->note().time, it->note().position);
		if (time < it->note().time + 200
		 && time > it->note().time - 200) {
			// DEBUG("lol", key, it->note().type);
			m_noteQueue.erase(it);
		}
	}
}

void Highway::keyReleased(u8 key) {
}

void Highway::update(u32 songTime) {
	const ChartNote *nextNote = m_chart.getNextNote(songTime + 1000);
	if (nextNote && (m_noteQueue.empty() || m_noteQueue.back().note().id != nextNote->id)) {
		m_noteQueue.emplace_back(*nextNote);
	}

	if (!m_noteQueue.empty() && m_noteQueue.front().note().time + 1000 < songTime) {
		// DEBUG(m_noteQueue.front().note().position);
		m_noteQueue.pop_front();
	}

	for (auto &it : m_noteQueue) {
		float y = m_strumBar.getPosition().y + songTime - it.note().time;
		it.setPosition(it.note().type * 100, y);
	}
}

void Highway::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_border, states);
	target.draw(m_strumBar, states);

	for (auto &it : m_keys)
		target.draw(it, states);

	for (auto &it : m_noteQueue)
		target.draw(it, states);
}

