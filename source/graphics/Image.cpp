/*
 * =====================================================================================
 *
 *       Filename:  Image.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:46:44
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Image.hpp"
#include "ResourceHandler.hpp"

Image::Image(const std::string &textureName)
	: m_textureName(textureName), m_texture(&ResourceHandler::getInstance().get<sf::Texture>(textureName))
{
	m_vertices.setPrimitiveType(sf::Triangles);

	setTileCount(1);
	setClipRect(0, 0, width(), height());
	setPosRect(0, 0, width(), height());
}

void Image::load(const char *textureName) {
	m_textureName = textureName;
	m_texture = &ResourceHandler::getInstance().get<sf::Texture>(textureName);

	m_vertices.setPrimitiveType(sf::Triangles);

	setTileCount(1);
	setClipRect(0, 0, width(), height());
	setPosRect(0, 0, width(), height());
}

void Image::setTile(u16 id, float x, float y, u16 width, u16 height, float clipX, float clipY, u16 clipWidth, u16 clipHeight, sf::Color color) {
	if(id >= m_vertices.getVertexCount() / 6)
		throw EXCEPTION("Image tile id", id, "out of range. Texture:", m_textureName);

	setTilePosRect(id, x, y, width, height);
	setTileClipRect(id, clipX, clipY, clipWidth, clipHeight);
	setTileColor(id, color);
}

void Image::setTilePosRect(u16 id, float x, float y, u16 width, u16 height) {
	sf::Vertex *triangle = &m_vertices[id * 6];

	triangle[0].position = sf::Vector2f(x, y);
	triangle[1].position = sf::Vector2f(x + width, y);
	triangle[2].position = sf::Vector2f(x, y + height);
	triangle[3].position = triangle[1].position;
	triangle[4].position = triangle[2].position;
	triangle[5].position = sf::Vector2f(x + width, y + height);
}

void Image::setTileClipRect(u16 id, float clipX, float clipY, u16 clipWidth, u16 clipHeight) {
	sf::Vertex *triangle = &m_vertices[id * 6];

	triangle[0].texCoords = sf::Vector2f(clipX, clipY);
	triangle[1].texCoords = sf::Vector2f(clipX + clipWidth, clipY);
	triangle[2].texCoords = sf::Vector2f(clipX, clipY + clipHeight);
	triangle[3].texCoords = triangle[1].texCoords;
	triangle[4].texCoords = triangle[2].texCoords;
	triangle[5].texCoords = sf::Vector2f(clipX + clipWidth, clipY + clipHeight);
}

void Image::setTileColor(u16 id, sf::Color color) {
	sf::Vertex *triangle = &m_vertices[id * 6];

	for (int i = 0 ; i < 6 ; ++i)
		triangle[i].color = color;
}

void Image::setTileCount(u16 tileCount) {
	m_vertices.resize(tileCount * 6);
}

void Image::setClipRect(float x, float y, u16 width, u16 height) {
	setTileClipRect(0, x, y, width, height);
}

void Image::setPosRect(float x, float y, u16 width, u16 height) {
	setTilePosRect(0, x, y, width, height);
}

void Image::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.texture = m_texture;
	states.transform *= getTransform();

	target.draw(m_vertices, states);
}

