/*
 * =====================================================================================
 *
 *       Filename:  Fret.cpp
 *
 *    Description:
 *
 *        Created:  17/10/2018 00:39:04
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Fret.hpp"

Fret::Fret(u16 id) : m_sprite("texture-frets", 32, 32) {
	m_id = id;

	m_sprite.setScale(4, 4);
	m_sprite.setPosition(-32, -64);
	m_sprite.setCurrentFrame(5 + id);

	m_rect.setSize({64, 64});
	m_rect.setOutlineThickness(4);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setFillColor(sf::Color::Black);
}

void Fret::setPressedState(bool isPressed) {
	if (isPressed) {
		m_rect.setFillColor(sf::Color::White);
		m_sprite.setCurrentFrame(10 + m_id);
	} else {
		m_rect.setFillColor(sf::Color::Black);
		m_sprite.setCurrentFrame(5 + m_id);
	}
}

void Fret::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	if (m_skinEnabled)
		target.draw(m_sprite, states);
	else
		target.draw(m_rect, states);
}

