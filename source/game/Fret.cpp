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
#include <SFML/Graphics/RenderTarget.hpp>

#include "Color.hpp"
#include "Fret.hpp"

Fret::Fret(u16 id) {
	m_id = id;

	m_sprite.setPosition(-32, 0);
	m_sprite.setCurrentFrame(id);

	sf::Color color;
	switch (id) {
		case 0: color = Color::Green;  break;
		case 1: color = Color::Red;    break;
		case 2: color = Color::Yellow; break;
		case 3: color = Color::Blue;   break;
		case 4: color = Color::Orange; break;
		default: break;
	}
	m_flames.setColor(color);

	gk::SpriteAnimation anim{20};
	anim.setRepeated(false);
	// for (int i = 2 ; i >= 0 ; --i) anim.addFrame(i);
	for (int i = 0 ; i < 8 ; ++i) {
		anim.addFrame(i);
	}

	m_flames.setScale(1.5, 1.5);
	m_flames.setPosition(-96 -56, -32 -32);
	m_flames.addAnimation(anim);
	m_flames.setAnimated(false);
}

void Fret::update() {
	m_flames.updateAnimations();

	if (m_flames.currentAnimation().isFinished()) {
		m_flames.setAnimated(false);
	}
}

void Fret::setPressedState(bool isPressed) {
	m_isPressed = isPressed;

	if (isPressed) {
		m_sprite.setCurrentFrame(5 + m_id);
	} else {
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

	target.draw(m_sprite, states);
	if (m_flames.isAnimated())
		target.draw(m_flames, states);
}

