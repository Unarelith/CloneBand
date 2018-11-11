/*
 * =====================================================================================
 *
 *       Filename:  Window.cpp
 *
 *    Description:
 *
 *        Created:  20/12/2014 00:17:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "OpenGL.hpp"
#include "Exception.hpp"
#include "Window.hpp"

void Window::open(const std::string &caption, u16 width, u16 height) {
	create(sf::VideoMode(width, height), caption, sf::Style::Close);
	setKeyRepeatEnabled(false);
	setActive(true);

	initGL();
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::initGL() {
#ifdef __MINGW32__
	if(glewInit() != GLEW_OK) {
		throw EXCEPTION("glew init failed");
	}
#endif

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// glEnable(GL_POLYGON_OFFSET_FILL);
	// glPolygonOffset(1, 1);
    //
	// glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);

	glClearColor(0, 0, 0, 1.0);
}

