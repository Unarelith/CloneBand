/*
 * =====================================================================================
 *
 *       Filename:  Note.hpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 13:06:25
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NOTE_HPP_
#define NOTE_HPP_

#include <SFML/Graphics.hpp>

#include "Chart.hpp"
#include "Sprite.hpp"

class Note : public sf::Drawable, public sf::Transformable {
	public:
		Note(const ChartNote &note);

		const ChartNote &note() const { return *m_note; }

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		bool m_skinEnabled = true;
		Sprite m_sprite{"texture-frets", 32, 32};
		sf::RectangleShape m_rect;

		sf::RectangleShape m_bar;

		const ChartNote *m_note;
};

#endif // NOTE_HPP_
