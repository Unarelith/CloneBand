/*
 * =====================================================================================
 *
 *       Filename:  GameState.hpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 12:36:29
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <gk/core/ApplicationState.hpp>

#include "Highway.hpp"
#include "SongController.hpp"

class GameState : public gk::ApplicationState {
	public:
		GameState();

		void onEvent(const sf::Event &event) override;

		void update() override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		SongController m_songController;
		Highway m_highway{m_songController.chart()};

		// gk::Camera m_camera{90.0f, 0.1f, 1000.0f};
		// gk::Shader m_shader;
};

#endif // GAMESTATE_HPP_
