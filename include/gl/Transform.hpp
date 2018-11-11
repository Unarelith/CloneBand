/*
 * =====================================================================================
 *
 *       Filename:  Transform.hpp
 *
 *    Description:
 *
 *        Created:  11/11/2018 17:39:49
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <glm/matrix.hpp>

#include "Box.hpp"
#include "Rect.hpp"
#include "Vector2.hpp"

#ifndef RADIANS_PER_DEGREES
# define RADIANS_PER_DEGREES (M_PI / 180.0f)
#endif

class Transform {
	public:
		Transform() = default;
		Transform(const glm::mat4 &matrix);

		Transform& combine(const Transform& transform);

		Transform& translate(float x, float y, float z = 0);
		Transform& translate(const Vector3f& offset) { return translate(offset.x, offset.y, offset.z); }

		Transform& rotate(float angle) { return rotate(angle, {0, 0, 1}); }
		Transform& rotate(float angle, const Vector3f& axis);

		Transform& scale(float scaleX, float scaleY, float scaleZ = 1);
		Transform& scale(const Vector3f& factors) { return scale(factors.x, factors.y, factors.z); }

		const float* getMatrix() const;

		Transform getInverse() const;
		Transform getTranspose() const;

		static const Transform Identity;

	private:
		glm::mat4 m_matrix{1};
};

Transform operator *(const Transform& left, const Transform& right);
Transform& operator *=(Transform& left, const Transform& right);

#endif // TRANSFORM_HPP_
