/*
 * =====================================================================================
 *
 *       Filename:  Application.hpp
 *
 *    Description:
 *
 *        Created:  29/07/2018 12:27:15
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <gk/core/CoreApplication.hpp>

class Application : public gk::CoreApplication {
	public:
		Application(int argc, char **argv) : gk::CoreApplication(argc, argv) {}

		void init() override;

	private:
		void initOpenGL();

		void onEvent(const SDL_Event &event) override;
};

#endif // APPLICATION_HPP_
