//
//  Vector3D.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
//

#include "Vector3D.hpp"
#include <cmath>

/* CONSTRUCTORS */
Vector3D::Vector3D(float x, float y, float z): m_x(x), m_y(y), m_z(z) {}

/* GETTERS */

// Computed values
float Vector3D::norm() const {
    return sqrt(squaredNorm());
}

float Vector3D::squaredNorm() const {
    return m_x*m_x + m_y*m_y + m_z*m_z;
}

/* OPERATIONS */

// Scalar multiplication
Vector3D Vector3D::operator*(float scalar) const {
    // RVO (return value optimization) to avoid useless Constructor call
    return {m_x*scalar, m_y*scalar, m_z*scalar};
}

Vector3D& Vector3D::operator*=(float scalar) {
    m_x *= scalar;
    m_y *= scalar;
    m_z *= scalar;
    return *this;
}

// Cross product (produit vectoriel)
Vector3D Vector3D::operator*(const Vector3D& other) const {
    return {
        m_y * other.z() - m_z * other.y(),
        m_z * other.x() - m_x * other.z(),
        m_x * other.y() - m_y * other.x()
    };
}

Vector3D& Vector3D::operator*=(const Vector3D& other) {
    // keep track of current components
    float oldX = m_x, oldY = m_y, oldZ = m_z;
    
    m_x = oldY * other.z() - oldZ * other.y();
    m_y = oldZ * other.x() - oldX * other.z();
    m_z = oldX * other.y() - oldY * other.x();
    return *this;
}

// Sum
Vector3D Vector3D::operator+(const Vector3D& other) const {
    return {m_x + other.x(), m_y + other.y(), m_z + other.z()};
}

Vector3D& Vector3D::operator+=(const Vector3D& other) {
    m_x += other.x();
    m_y += other.y();
    m_z += other.z();
    return *this;
}

// Subtraction
Vector3D Vector3D::operator-(const Vector3D& other) const {
    return {m_x - other.x(), m_y - other.y(), m_z - other.z()};
}

Vector3D& Vector3D::operator-=(const Vector3D& other) {
    m_x -= other.x();
    m_y -= other.y();
    m_z -= other.z();
    return *this;
}

// Dot product (produit scalaire)
float Vector3D::dot(const Vector3D& other) const {
    return m_x * other.x() + m_y * other.y() + m_z * other.z();
}

// Components product
Vector3D Vector3D::componentsProduct(const Vector3D& other) const {
    return {m_x * other.x(), m_y * other.y(), m_z * other.z()};
}

// Normalization
Vector3D Vector3D::normalize() const {
    float normValue = norm();
    if (normValue == 0) return Vector3D();
    return {m_x / normValue, m_y / normValue, m_z / normValue};
}

void Vector3D::normalizeInPlace() {
    float normValue = norm();
    if (normValue != 0) {
        m_x /= normValue;
        m_y /= normValue;
        m_z /= normValue;
    }
}

/* OPEN FRAMEWORK */

glm::vec2 Vector3D::v2() const {
    return glm::vec2(m_x, m_y);
}

glm::vec3 Vector3D::v3() const {
    return glm::vec3(m_x, m_y, m_z);
}
