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

#include <list>

// #include <gk/gl/Camera.hpp>

#include <SFML/Window/Event.hpp>

#include "Note.hpp"
#include "Fret.hpp"

class Highway : public sf::Drawable, public sf::Transformable {
	public:
		Highway(const Chart &chart);

		void onEvent(const sf::Event &event);

		void update(u32 songTime);

	private:
		void handleKeyboard(const sf::Event &event);
		void handleGamepad(const sf::Event &event);

		void keyPressed(u8 key);
		void keyReleased(u8 key);

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		const Chart &m_chart;

		std::list<Note> m_noteQueue;

		std::array<Fret, 5> m_frets{0, 1, 2, 3, 4};

		gk::Image m_background1{"texture-highway"};
		gk::Image m_background2{"texture-highway"};

		gk::Image m_sideBars{"texture-side_bars"};
		gk::Image m_centerLines{"texture-center_lines"};
};

#endif // HIGHWAY_HPP_
