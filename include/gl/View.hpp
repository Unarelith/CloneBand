////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////
#ifndef VIEW_HPP_
#define VIEW_HPP_

#include <SFML/Graphics/Export.hpp>

#include "Rect.hpp"
#include "Transform.hpp"
#include "Vector3.hpp"

class View {
	public:
		View();
		explicit View(const FloatRect& rectangle);
		View(const Vector3f& center, const Vector2f& size);
		virtual ~View();

		void setCenter(float x, float y, float z = 0);
		void setCenter(const Vector3f& center);

		void setSize(float width, float height);
		void setSize(const Vector2f& size);

		void setRotation(float angle);

		void setViewport(const FloatRect& viewport);

		void reset(const FloatRect& rectangle);

		const Vector3f& getCenter() const;
		const Vector2f& getSize() const;

		float getRotation() const;

		const FloatRect& getViewport() const;

		void move(float offsetX, float offsetY, float offsetZ = 0);
		void move(const Vector3f& offset);

		void rotate(float angle);

		void zoom(float factor);

		virtual const Transform& getTransform() const;
		const Transform& getInverseTransform() const;

		virtual const Transform& getViewTransform() const;
		const Transform& getInverseViewTransform() const;

		virtual const Vector3f& getPosition() const;

	protected:
		mutable Transform m_transform;               ///< Precomputed projection transform corresponding to the view
		mutable bool      m_transformUpdated;        ///< Internal state telling if the transform needs to be updated
		mutable Transform m_inverseTransform;        ///< Precomputed inverse projection transform corresponding to the view
		mutable bool      m_invTransformUpdated;     ///< Internal state telling if the inverse transform needs to be updated
		mutable Transform m_viewTransform;           ///< Precomputed view transform
		mutable bool      m_viewTransformUpdated;    ///< Internal state telling if the view transform needs to be updated
		mutable Transform m_inverseViewTransform;    ///< Precomputed inverse view transform
		mutable bool      m_invViewTransformUpdated; ///< Internal state telling if the inverse view transform needs to be updated

	private :
		Vector3f  m_position; ///< Center of the view, in scene coordinates
		Vector2f  m_size;     ///< Size of the view, in scene coordinates
		float     m_rotation; ///< Angle of rotation of the view rectangle, in degrees
		FloatRect m_viewport; ///< Viewport rectangle, expressed as a factor of the render-target's size
};

#endif // VIEW_HPP_
