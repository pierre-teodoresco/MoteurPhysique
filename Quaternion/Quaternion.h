#pragma once
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include "Matrix\Matrix3.hpp"

class Quaternion {
public:
	// Constructors
	Quaternion() : w(1), x(0), y(0), z(0) {}
	Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
	Quaternion(Vector3D vec) : w(0), x(vec.x()), y(vec.y()), z(vec.z()) {};

	float Norm() const;

	Quaternion Normalize() const;
	Quaternion Conjugate() const;
	Quaternion Inverse() const;
	Quaternion Rotate(const Quaternion& q) const;
	Quaternion RotateAngle(float vx, float vy, float vz);

	Quaternion operator*(const Quaternion& q) const;
	Quaternion operator*(const float scalar) const;

	// Addition
	Quaternion operator+(const Quaternion& other) const;

	void Print() const;
	glm::quat ToGLMQuat() const;
	Matrix3 ToRotationMatrix3() const;

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	float getW() const { return w; }

private:
	float x, y, z, w;
};