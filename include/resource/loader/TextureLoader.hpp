/*
 * =====================================================================================
 *
 *       Filename:  TextureLoader.hpp
 *
 *    Description:
 *
 *        Created:  09/04/2018 01:37:23
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TEXTURELOADER_HPP_
#define TEXTURELOADER_HPP_

#include "ResourceLoader.hpp"

class TextureLoader {
	public:
		void load(const char *xmlFilename, ResourceHandler &handler);
};

#endif // TEXTURELOADER_HPP_
