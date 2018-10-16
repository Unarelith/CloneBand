/*
 * =====================================================================================
 *
 *       Filename:  Image.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:46:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <SFML/Graphics.hpp>

#include "IntTypes.hpp"

class Image : public sf::Drawable, public sf::Transformable {
	public:
		Image() = default;
		Image(const std::string &textureName);

		void load(const char *textureName);

		void setTile(u16 id, float x, float y, u16 width, u16 height, float clipX, float clipY, u16 clipWidth, u16 clipHeight, sf::Color color = sf::Color::White);
		void setTilePosRect(u16 id, float x, float y, u16 width, u16 height);
		void setTileClipRect(u16 id, float x, float y, u16 clipWidth, u16 clipHeight);
		void setTileColor(u16 id, sf::Color color);

		void setTileCount(u16 tileCount);

		void setClipRect(float x, float y, u16 width, u16 height);
		void setPosRect(float x, float y, u16 width, u16 height);

		u16 width() const { return m_texture->getSize().x; }
		u16 height() const { return m_texture->getSize().y; }

		const sf::Texture *texture() const { return m_texture; }

	protected:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		std::string m_textureName;

	private:
		sf::Texture *m_texture;

		sf::VertexArray m_vertices;
};

#endif // IMAGE_HPP_
