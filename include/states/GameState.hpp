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

#include <SFML/Audio.hpp>

#include "ApplicationState.hpp"
#include "Camera.hpp"
#include "Highway.hpp"
#include "Shader.hpp"

class GameState : public ApplicationState {
	public:
		GameState();

		void onEvent(const sf::Event &event) override;

		void update() override;

	private:
		void draw(RenderTarget &target, RenderStates states) const override;

		sf::Music m_music;
		Chart m_chart{"charts/WakingTheDemon/notes.chart"};
		Highway m_highway{m_chart};

		u32 m_previousFrameTime = 0;
		u32 m_lastReportedPlayheadPosition = 0;
		u32 m_songTime = 0;

		Camera m_camera{90.0f, 0.1f, 1000.0f};
		Shader m_shader;

		glm::mat4 m_projectionMatrix2d;
		glm::mat4 m_projectionMatrix3d;
		glm::mat4 m_viewMatrix;
};

#endif // GAMESTATE_HPP_
