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

class Fret : public IDrawable, public Transformable {
	public:
		Fret(u16 id);

		void update();

		bool isPressed() const { return m_isPressed; }

		void setPressedState(bool isPressed);
		void setFireState(bool hasFire);

		float width() { return m_sprite.frameWidth(); }
		float height() { return m_sprite.frameHeight(); }

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		u16 m_id;

		bool m_isPressed = false;

		Sprite m_sprite{"texture-frets", 136, 82};
		Sprite m_flames{"texture-flames", 256, 128};
};

#endif // FRET_HPP_
