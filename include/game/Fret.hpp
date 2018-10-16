/*
 * =====================================================================================
 *
 *       Filename:  Fret.hpp
 *
 *    Description:
 *
 *        Created:  16/10/2018 22:42:39
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef FRET_HPP_
#define FRET_HPP_

#include "Sprite.hpp"

class Fret : public sf::Drawable, public sf::Transformable {
	public:
		Fret(u16 id);

		void setPressedState(bool isPressed);

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		u16 m_id;

		bool m_skinEnabled = true;
		Sprite m_sprite;
		sf::RectangleShape m_rect;
};

#endif // FRET_HPP_
