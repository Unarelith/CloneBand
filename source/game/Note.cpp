/*
 * =====================================================================================
 *
 *       Filename:  Note.cpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 13:06:36
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Note.hpp"

Note::Note(const ChartNote &note) : m_note(&note) {
	m_sprite.setPosition(-34, 0);

	if (!note.isHopo)
		m_sprite.setCurrentFrame(note.type);
	else
		m_sprite.setCurrentFrame(note.type + 5);

	sf::Color color;
	switch (note.type) {
		case 0: color = sf::Color::Green;   break;
		case 1: color = sf::Color::Red;     break;
		case 2: color = sf::Color::Yellow;  break;
		case 3: color = sf::Color::Blue;    break;
		case 4: color = sf::Color::Magenta; break;
		default: break;
	}

	m_tail.setPosRect(32 - m_tail.width() / 2, -note.length + 32, m_tail.width(), note.length + 16);
	m_tail.setTileColor(0, color);

	m_rect.setSize({64, 64});
	m_rect.setFillColor(color);

	m_bar.setSize({8, (float)note.length});
	m_bar.setPosition(32 - m_bar.getSize().x / 2, -m_bar.getSize().y + 8);
	m_bar.setOutlineThickness(8);
	m_bar.setOutlineColor(sf::Color::White);
	m_bar.setFillColor(sf::Color::Black);
}

void Note::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	if (m_skinEnabled) {
		if (m_note->length)
			target.draw(m_tail, states);
		target.draw(m_sprite, states);
	}
	else {
		if (m_note->length)
			target.draw(m_bar, states);
		target.draw(m_rect, states);
	}
}

