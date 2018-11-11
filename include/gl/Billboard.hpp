#ifndef BILLBOARD_HPP_
#define BILLBOARD_HPP_

#include <SFML/Graphics/Export.hpp>

#include "Rect.hpp"
#include "RenderTarget.hpp"
#include "RenderStates.hpp"
#include "Sprite.hpp"

class Camera;

class Billboard : public Sprite {
	public:
		Billboard(const std::string &textureName, u16 frameWidth, u16 frameHeight);

		void setCamera(const Camera& camera);
		const Camera* getCamera() const;

	private:
		void draw(RenderTarget& target, RenderStates states) const override;

		const Camera* m_camera = nullptr;
};

#endif // BILLBOARD_HPP_
