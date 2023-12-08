#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D() {
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vector3D::Vector3D(float vector_x, float vector_y, float vector_z) {
	x = vector_x;
	y = vector_y;
	z = vector_z;
}

Vector3D::Vector3D(const Vector3D& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

Vector3D Vector3D::lerp(const Vector3D& vector_a, const Vector3D& vector_b, float coefficient) {
	Vector3D resultVector;

	resultVector.x = vector_a.x * (1.f - coefficient) + vector_b.x * coefficient; 
	resultVector.y = vector_a.y * (1.f - coefficient) + vector_b.y * coefficient;
	resultVector.z = vector_a.z * (1.f - coefficient) + vector_b.z * coefficient;

	return resultVector;
}

Vector3D Vector3D::QuaterionToEuler(const float& x, const float& y, const float& z, const float& w)
{
	Vector3D euler;

	double pitch = 2.0 * (w * x + y * z);
	euler.x = asin(pitch);

	double yaw = std::atan2(2.0 * (w * y - z * x),1.0 - 2.0 * (x * x + y * y));
	euler.y = yaw;

	double roll = std::atan2(2.0 * (w * z + x * y),1.0 - 2.0 * (y * y + z * z));
	euler.z = roll;

	return euler;

}

void Vector3D::operator=(const Vector3D& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Vector3D::operator+=(const Vector3D& vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

Vector3D Vector3D::operator+(Vector3D vector) {
	return Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Vector3D Vector3D::operator*(float scalar) {
	return Vector3D(scalar * x, scalar * y, scalar * z);
}