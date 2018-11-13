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

#include "ApplicationState.hpp"
#include "Camera.hpp"
#include "Highway.hpp"
#include "Shader.hpp"
#include "SongController.hpp"

class GameState : public ApplicationState {
	public:
		GameState();

		void onEvent(const sf::Event &event) override;

		void update() override;

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		SongController m_songController;
		Highway m_highway{m_songController.chart()};

		Camera m_camera{90.0f, 0.1f, 1000.0f};
		Shader m_shader;
};

#endif // GAMESTATE_HPP_
