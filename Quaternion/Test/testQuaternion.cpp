#include <iostream>
#include <cassert>
#include "testQuaternion.hpp"


void TestNorm() {
    Quaternion q(1.f, 2.f, 3.f, 4.f);
    float expectedNorm = std::sqrt(1 * 1 + 2 * 2 + 3 * 3 + 4 * 4);
    assert(std::abs(q.Norm() - expectedNorm) < 1e-6);
}

void TestNormalize() {
    Quaternion q(1, 2, 3, 4);
    Quaternion normalized = q.Normalize();
    float expectedNorm = 1.0f; // Normalized quaternions have norm = 1
    assert(std::abs(normalized.Norm() - expectedNorm) < 1e-6);
}

void TestConjugate() {
    Quaternion q(1, 2, 3, 4);
    Quaternion conjugate = q.Conjugate();
    assert(conjugate.getW() == 1 && conjugate.getX() == -2 && conjugate.getY() == -3 && conjugate.getZ() == -4);
}

void TestInverse() {
    Quaternion q(1, 2, 3, 4);
    Quaternion inverse = q.Inverse();
    Quaternion identity = q * inverse;
    assert(std::abs(identity.getW() - 1.0f) < 1e-6);
    assert(std::abs(identity.getX()) < 1e-6);
    assert(std::abs(identity.getY()) < 1e-6);
    assert(std::abs(identity.getZ()) < 1e-6);
}

void TestMultiplication() {
    Quaternion q1(1, 0, 1, 0);
    Quaternion q2(1, 0.5, 0.5, 0.75);
    Quaternion result = q1 * q2;

    Quaternion expected(0.25, 1.25, 1.5, 0.25);
    assert(std::abs(result.getW() - expected.getW()) < 1e-6);
    assert(std::abs(result.getX() - expected.getX()) < 1e-6);
    assert(std::abs(result.getY() - expected.getY()) < 1e-6);
    assert(std::abs(result.getZ() - expected.getZ()) < 1e-6);
}

void TestRotate() {
    Quaternion q(0.92388, 0, 0.382683, 0); // Rotation of 45 degrees around Z-axis
    Quaternion vector(0, 1, 0, 0);         // Vector along X-axis
    Quaternion rotated = vector.Rotate(q);

    Quaternion expected(0, 0.707107, 0.707107, 0); // Rotated vector
    assert(std::abs(rotated.getW() - expected.getW()) < 1e-6);
    assert(std::abs(rotated.getX() - expected.getX()) < 1e-6);
    assert(std::abs(rotated.getY() - expected.getY()) < 1e-6);
    assert(std::abs(rotated.getZ() - expected.getZ()) < 1e-6);
}

void TestRotateAngle() {
    Quaternion q(0.92388, 0, 0.382683, 0); // Rotation of 45 degrees around Z-axis
    Quaternion rotated = q.RotateAngle(1, 0, 0);

    Quaternion expected(0, 0.707107, 0.707107, 0); // Rotated vector
    assert(std::abs(rotated.getW() - expected.getW()) < 1e-6);
    assert(std::abs(rotated.getX() - expected.getX()) < 1e-6);
    assert(std::abs(rotated.getY() - expected.getY()) < 1e-6);
    assert(std::abs(rotated.getZ() - expected.getZ()) < 1e-6);
}

void QuaternionTest::RunTests() {
    TestNorm();
    TestNormalize();
    TestConjugate();
    TestInverse();
    TestMultiplication();
    TestRotate();
    TestRotateAngle();
    std::cout << "All tests passed successfully!" << std::endl;
}
