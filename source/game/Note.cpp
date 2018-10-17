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
	m_sprite.setScale(4, 4);
	m_sprite.setPosition(-32, -64);
	m_sprite.setCurrentFrame(note.type);

	m_rect.setSize({64, 64});
	switch (note.type) {
		case 0: m_rect.setFillColor(sf::Color::Green);   break;
		case 1: m_rect.setFillColor(sf::Color::Red);     break;
		case 2: m_rect.setFillColor(sf::Color::Yellow);  break;
		case 3: m_rect.setFillColor(sf::Color::Blue);    break;
		case 4: m_rect.setFillColor(sf::Color::Magenta); break;
		default: break;
	}

	m_bar.setSize({8, note.length});
	m_bar.setPosition(32 - m_bar.getSize().x / 2, -m_bar.getSize().y + 4);
	m_bar.setOutlineThickness(8);
	m_bar.setOutlineColor(sf::Color::White);
	m_bar.setFillColor(sf::Color::Black);
}

void Note::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	if (m_skinEnabled)
		target.draw(m_sprite, states);
	else
		target.draw(m_rect, states);

	if (m_note->length)
		target.draw(m_bar, states);
}

