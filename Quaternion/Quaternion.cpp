#include "Quaternion.h"

#include <glm/gtc/quaternion.hpp>

float Quaternion::Norm() const {
	return std::sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::Normalize() const {
	float norm = Norm();
	return Quaternion(w / norm, x / norm, y / norm, z / norm);
}

Quaternion Quaternion::Conjugate() const {
	return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::Inverse() const {
	Quaternion conjugate = Conjugate();
	float norm = Norm();

	return Quaternion(conjugate.w / (norm * norm), conjugate.x / (norm * norm),
		conjugate.y / (norm * norm), conjugate.z / (norm * norm));
}

Quaternion Quaternion::operator*(const Quaternion& q) const {
	float newW = w * q.w - x * q.x - y * q.y - z * q.z;
	float newX = w * q.x + x * q.w + y * q.z - z * q.y;
	float newY = w * q.y - x * q.z + y * q.w + z * q.x;
	float newZ = w * q.z + x * q.y - y * q.x + z * q.w;

	return Quaternion(newW, newX, newY, newZ);
}

Quaternion Quaternion::Rotate(const Quaternion& q) const {
	return q * (*this) * q.Inverse();
}

Quaternion Quaternion::RotateAngle(float vx, float vy, float vz) {
	Quaternion p(0, vx, vy, vz);
	Quaternion q_inv = Inverse();
	Quaternion rotated = (*this) * p * q_inv;

	return rotated;
}

void Quaternion::Print() const {
	std::cout << "Quaternion(" << w << ", " << x << ", " << y << ", " << z << ")\n";
}

glm::quat Quaternion::ToGLMQuat() const {
	return glm::quat(w, x, y, z);
}

Matrix3 Quaternion::ToRotationMatrix3() const
{
	float r00 = 2 * (w * w + x * x) - 1;
	float r01 = 2 * (x * y - w * z);
	float r02 = 2 * (x * z + w * y);

	float r10 = 2 * (x * y + w * z);
	float r11 = 2 * (w * w + y * y) - 1;
	float r12 = 2 * (y * z - w * x);

	float r20 = 2 * (x * z - w * y);
	float r21 = 2 * (y * z + w * x);
	float r22 = 2 * (w * w + z * z) - 1;

	float data[3][3] = { {r00, r01, r02}, {r10, r11, r12}, {r20, r21, r22} };
	return Matrix3(data);
}
