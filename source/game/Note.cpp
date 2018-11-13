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
	m_sprite.setPosition(-34, 80);
	m_sprite.setOrigin(0, 80);
	m_sprite.setRotation(50.0f, Vector3{1, 0, 0});

	if (!note.isHopo)
		m_sprite.setCurrentFrame(note.type);
	else
		m_sprite.setCurrentFrame(note.type + 5);

	Color color;
	switch (note.type) {
		case 0: color = Color::Green;   break;
		case 1: color = Color::Red;     break;
		case 2: color = Color::Yellow;  break;
		case 3: color = Color::Blue;    break;
		case 4: color = Color::Orange; break;
		default: break;
	}

	m_tail.setPosition(32 - m_tail.width() / 2, -note.length + 32);
	m_tail.setScale(1, (note.length + 16) / m_tail.height());
	m_tail.setColor(color);
}

void Note::draw(RenderTarget &target, RenderStates states) const {
	states.transform *= getTransform();

	if (m_note->length)
		target.draw(m_tail, states);
	target.draw(m_sprite, states);
}
