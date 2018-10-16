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
	m_rect.setPosition(25, 25);
	m_rect.setSize({50, 50});
	// m_rect.setOutlineThickness(10);

	switch (note.type) {
		case 0: m_rect.setFillColor(sf::Color::Green);   break;
		case 1: m_rect.setFillColor(sf::Color::Red);     break;
		case 2: m_rect.setFillColor(sf::Color::Yellow);  break;
		case 3: m_rect.setFillColor(sf::Color::Blue);    break;
		case 4: m_rect.setFillColor(sf::Color::Magenta); break;
		default: break;
	}
}

void Note::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_rect, states);
}

