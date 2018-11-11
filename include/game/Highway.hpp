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

#include <SFML/Window/Event.hpp>

#include "Camera.hpp"
#include "Note.hpp"
#include "Fret.hpp"

class Highway : public IDrawable, public Transformable {
	public:
		Highway(Chart &chart);

		void onEvent(const sf::Event &event);

		void update(u32 songTime);

	private:
		void handleKeyboard(const sf::Event &event);
		void handleGamepad(const sf::Event &event);

		void keyPressed(u8 key);
		void keyReleased(u8 key);

		void draw(RenderTarget &target, RenderStates states) const override;

		Chart &m_chart;

		std::deque<Note> m_noteQueue;

		std::array<Fret, 5> m_frets{0, 1, 2, 3, 4};

		Image m_background1{"texture-highway"};
		Image m_background2{"texture-highway"};
		u16 m_backgroundWidth = 0;
		u16 m_backgroundHeight = 0;

		Image m_sideBars{"texture-side_bars"};
		Image m_centerLines{"texture-center_lines"};

		bool m_skinEnabled = true;
};

#endif // HIGHWAY_HPP_
