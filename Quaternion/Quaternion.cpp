#include "Quaternion.h"

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
