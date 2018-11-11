#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Transformable.hpp"
#include "View.hpp"

class Camera : public View {
	public:
		Camera(float fov, float near, float far);
		virtual ~Camera() = default;

		void setPosition(float x, float y, float z);
		void setPosition(const Vector3f& position);

		virtual const Vector3f& getPosition() const;

		void setDirection(float x, float y, float z);
		void setDirection(const Vector3f& direction);

		const Vector3f& getDirection() const;

		void setUpVector(float x, float y, float z);
		void setUpVector(const Vector3f& upVector);
		const Vector3f& getUpVector() const;

		void setScale(float factorX, float factorY, float factorZ);
		void setScale(const Vector3f& factors);

		const Vector3f& getScale() const;

		void setFieldOfView(float fov);

		float getFieldOfView() const;

		void setNearClippingPlane(float distance);
		float getNearClippingPlane() const;

		void setFarClippingPlane(float distance);
		float getFarClippingPlane() const;

		void scale(float factorX, float factorY, float factorZ);
		void scale(const Vector3f& factor);

		virtual const Transform& getTransform() const;
		virtual const Transform& getViewTransform() const;

	private:
		float    m_fieldOfView; ///< Field of view of this camera, in degrees
		float    m_nearPlane;   ///< The distance to the near clipping plane
		float    m_farPlane;    ///< The distance to the far clipping plane
		Vector3f m_direction;   ///< The direction the camera is facing in
		Vector3f m_upVector;    ///< The up vector of the camera
		Vector3f m_scale;       ///< The scaling that is applied after the perspective transform
};

#endif // CAMERA_HPP_
