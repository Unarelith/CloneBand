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
#ifndef TRANSFORMABLE_HPP_
#define TRANSFORMABLE_HPP_

#include <SFML/Graphics/Export.hpp>

#include "Transform.hpp"

class Transformable {
	public:
		Transformable();
		virtual ~Transformable();

		void setPosition(float x, float y, float z = 0);
		void setPosition(const Vector3f& position);

		void setRotation(float angle);
		void setRotation(float angle, const Vector3f& axis);

		void setScale(float factorX, float factorY, float factorZ = 1);
		void setScale(const Vector3f& factors);

		void setOrigin(float x, float y, float z = 0);
		void setOrigin(const Vector3f& origin);

		const Vector3f& getPosition() const;
		float getRotation() const;
		const Vector3f& getScale() const;
		const Vector3f& getOrigin() const;

		void move(float offsetX, float offsetY, float offsetZ = 0);
		void move(const Vector3f& offset);

		void rotate(float angle);
		void rotate(float angle, const Vector3f& axis);

		void scale(float factorX, float factorY, float factorZ = 1);
		void scale(const Vector3f& factor);

		const Transform& getTransform() const;
		const Transform& getInverseTransform() const;

	private:
		Vector3f          m_origin;                     ///< Origin of translation/rotation/scaling of the object
		Vector3f          m_position;                   ///< Position of the object in the 3D world
		float             m_rotation;                   ///< Orientation of the object, in degrees
		Vector3f          m_scale;                      ///< Scale of the object
		mutable Transform m_rotation_transform;         ///< Combined transformation of the object
		mutable Transform m_transform;                  ///< Combined transformation of the object
		mutable bool      m_transformNeedUpdate;        ///< Does the transform need to be recomputed?
		mutable Transform m_inverseTransform;           ///< Combined transformation of the object
		mutable bool      m_inverseTransformNeedUpdate; ///< Does the transform need to be recomputed?
};

#endif // TRANSFORMABLE_HPP_
