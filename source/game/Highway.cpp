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
	m_background1.setScale(8, 8);
	m_background2.setScale(8, 8);

	m_backgroundWidth = m_background1.width() * m_background1.getScale().x;
	m_backgroundHeight = m_background1.height() * m_background1.getScale().y;

	m_background1.setPosition(128 * 5 / 2 - m_backgroundWidth / 2, 0);
	m_background2.setPosition(128 * 5 / 2 - m_backgroundWidth / 2, -m_backgroundHeight);

	m_border.setSize({128 * 5 + 8, 892});
	m_border.setPosition(-4, 4);
	m_border.setOutlineThickness(4);
	m_border.setOutlineColor(sf::Color::White);
	m_border.setFillColor(sf::Color::Black);

	m_strumBar.setSize({128 * 5 - 8, 128 - 8});
	m_strumBar.setPosition(4, 700);
	m_strumBar.setOutlineThickness(4);
	m_strumBar.setOutlineColor(sf::Color::White);
	m_strumBar.setFillColor(sf::Color::Black);

	for (u8 i = 0 ; i < 5 ; ++i) {
		m_frets[i].setPosition(i * 128 + 32, 725);
	}
}

void Highway::onEvent(const sf::Event &event) {
	handleKeyboard(event);
	handleGamepad(event);
}

void Highway::handleKeyboard(const sf::Event &event) {
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
		int key = -1;

		if (event.key.code == sf::Keyboard::H) key = 0;
		if (event.key.code == sf::Keyboard::J) key = 1;
		if (event.key.code == sf::Keyboard::K) key = 2;
		if (event.key.code == sf::Keyboard::L) key = 3;
		if (event.key.code == sf::Keyboard::M) key = 4;

		if (key != -1) {
			if (event.type == sf::Event::KeyPressed) {
				m_frets[key].setPressedState(true);
				keyPressed(key);
			} else {
				m_frets[key].setPressedState(false);
				keyReleased(key);
			}
		}
	}
}

void Highway::handleGamepad(const sf::Event &event) {
	static int key = -1;

	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickButtonReleased) {
		key = -1;

		if (event.joystickButton.button == 0) key = 0;
		if (event.joystickButton.button == 1) key = 1;
		if (event.joystickButton.button == 2) key = 3;
		if (event.joystickButton.button == 3) key = 2;
		if (event.joystickButton.button == 4) key = 4;

		if (key != -1) {
			if (event.type == sf::Event::JoystickButtonPressed) {
				m_frets[key].setPressedState(true);
			} else {
				m_frets[key].setPressedState(false);
				keyReleased(key);
			}
		}
	}
	else if (event.type == sf::Event::JoystickMoved && event.joystickMove.axis == 7 && event.joystickMove.position) {
		keyPressed(key);
	}
}

void Highway::keyPressed(u8 key) {
	auto it = std::find_if(m_noteQueue.begin(), m_noteQueue.end(), [key](Note &note) {
		// DEBUG(note.note().position, note.note().type, key);
		return note.note().type == key;
	});

	if (it != m_noteQueue.end()) {
		u64 time = GameClock::getTicks();
		// DEBUG(time, it->note().time, it->note().position);
		if (time < it->note().time + 150
		 && time > it->note().time - 150) {
			// DEBUG("lol", key, it->note().type);
			m_frets[key].setFireState(true);
			m_noteQueue.erase(it);
		}
	}
}

void Highway::keyReleased(u8 key) {
}

void Highway::update(u32 songTime) {
	for (u8 i = 0 ; i < 5 ; ++i)
		m_frets[i].update();

	const ChartNote *nextNote = m_chart.getNextNote(songTime + 2000);
	if (nextNote && (m_noteQueue.empty() || m_noteQueue.back().note().id != nextNote->id)) {
		m_noteQueue.emplace_back(*nextNote);
	}

	if (!m_noteQueue.empty() && m_noteQueue.front().note().time + 1000 < songTime) {
		// DEBUG(m_noteQueue.front().note().position);
		m_noteQueue.pop_front();
	}

	for (auto &it : m_noteQueue) {
		float y = m_strumBar.getPosition().y + ((int)songTime - (int)it.note().time) / 2.0f;
		it.setPosition(it.note().type * 128 + 32, y);
	}

	m_background1.setPosition(m_background1.getPosition().x, (songTime / 2) % m_backgroundHeight);
	m_background2.setPosition(m_background2.getPosition().x, ((int)songTime / 2) % m_backgroundHeight - m_backgroundHeight);
}

void Highway::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_background1, states);
	target.draw(m_background2, states);

	// target.draw(m_border, states);
	// target.draw(m_strumBar, states);

	for (auto &it : m_frets)
		target.draw(it, states);

	for (auto &it : m_noteQueue)
		target.draw(it, states);
}

