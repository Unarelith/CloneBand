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

		void update();

		void setPressedState(bool isPressed);
		void setFireState(bool hasFire);

		float width() { return m_sprite.frameWidth(); }
		float height() { return m_sprite.frameHeight(); }

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		u16 m_id;

		bool m_skinEnabled = true;
		Sprite m_sprite{"texture-frets", 136, 82};
		// Sprite m_sprite{"texture-frets", 150, 58};
		sf::RectangleShape m_rect;

		// Sprite m_flames{"texture-flames", 32, 32};
		Sprite m_flames{"texture-flames", 256, 128};
};

#endif // FRET_HPP_
