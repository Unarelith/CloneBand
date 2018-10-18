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

Fret::Fret(u16 id) {
	m_id = id;

	m_sprite.setPosition(-32, 0);
	m_sprite.setCurrentFrame(id);

	m_rect.setSize({64, 64});
	m_rect.setOutlineThickness(4);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setFillColor(sf::Color::Black);

	sf::Color color;
	switch (id) {
		case 0: color = sf::Color::Green;   break;
		case 1: color = sf::Color::Red;     break;
		case 2: color = sf::Color::Yellow;  break;
		case 3: color = sf::Color::Cyan;    break;
		case 4: color = sf::Color::Magenta; break;
		default: break;
	}
	m_flames.setTileColor(0, color);

	SpriteAnimation anim{20};
	anim.setRepeated(false);
	// for (int i = 2 ; i >= 0 ; --i) anim.addFrame(i);
	for (int i = 0 ; i < 8 ; ++i) {
		anim.addFrame(i);
	}

	m_flames.setScale(1.5, 1.5);
	m_flames.setPosition(-96 -64, -32 -32);
	m_flames.addAnimation(anim);
	m_flames.setAnimated(false);
}

void Fret::update() {
	m_flames.updateAnimations();

	if (m_flames.currentAnimation().isFinished())
		m_flames.setAnimated(false);
}

void Fret::setPressedState(bool isPressed) {
	if (isPressed) {
		m_rect.setFillColor(sf::Color::White);
		m_sprite.setCurrentFrame(5 + m_id);
	} else {
		m_rect.setFillColor(sf::Color::Black);
		m_sprite.setCurrentFrame(m_id);
	}
}

void Fret::setFireState(bool hasFire) {
	if (hasFire) {
		m_flames.currentAnimation().reset();
		m_flames.setAnimated(true);
	}
}

void Fret::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	if (m_skinEnabled)
		target.draw(m_sprite, states);
	else
		target.draw(m_rect, states);

	if (m_flames.isAnimated())
		target.draw(m_flames, states);
}

