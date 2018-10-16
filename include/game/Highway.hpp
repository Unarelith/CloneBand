/*
 * =====================================================================================
 *
 *       Filename:  Highway.hpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 13:04:09
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef HIGHWAY_HPP_
#define HIGHWAY_HPP_

#include <deque>

#include "Note.hpp"

class Highway : public sf::Drawable, public sf::Transformable {
	public:
		Highway(Chart &chart);

		void onEvent(const sf::Event &event);

		void update(u32 songTime);

	private:
		void keyPressed(u8 key);
		void keyReleased(u8 key);

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		Chart &m_chart;

		std::deque<Note> m_noteQueue;

		sf::RectangleShape m_strumBar;
		sf::RectangleShape m_border;

		std::array<sf::RectangleShape, 5> m_keys;
};

#endif // HIGHWAY_HPP_
