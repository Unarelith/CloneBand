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
#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Box.hpp"
#include "Vector2.hpp"

class Transform {
	public:
		Transform();
		Transform(float a00, float a01, float a02, float a03,
		          float a10, float a11, float a12, float a13,
		          float a20, float a21, float a22, float a23,
		          float a30, float a31, float a32, float a33);

		const float* getMatrix() const;
		Transform getInverse() const;
		Transform getTranspose() const;

		Vector3f transformPoint(float x, float y, float z = 0) const;
		Vector3f transformPoint(const Vector3f& point) const;

		sf::FloatRect transformRect(const sf::FloatRect& rectangle) const;

		FloatBox transformBox(const FloatBox& box) const;

		Transform& combine(const Transform& transform);

		Transform& translate(float x, float y, float z = 0);
		Transform& translate(const Vector3f& offset);

		Transform& rotate(float angle);
		Transform& rotate(float angle, float centerX, float centerY);
		Transform& rotate(float angle, const Vector2f& center);
		Transform& rotate(float angle, const Vector3f& axis);

		Transform& scale(float scaleX, float scaleY, float scaleZ = 1);
		Transform& scale(float scaleX, float scaleY, float centerX, float centerY);
		Transform& scale(float scaleX, float scaleY, float scaleZ, float centerX, float centerY, float centerZ);
		Transform& scale(const Vector3f& factors);
		Transform& scale(const Vector3f& factors, const Vector3f& center);

		static const Transform Identity; ///< The identity transform (does nothing)

	private:
		float m_matrix[16]; ///< 4x4 matrix defining the transformation
};

Transform operator *(const Transform& left, const Transform& right);
Transform& operator *=(Transform& left, const Transform& right);
Vector3f operator *(const Transform& left, const Vector3f& right);

#endif // TRANSFORM_HPP_
