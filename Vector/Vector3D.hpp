#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <string>
class Vector3D {

private:
    float m_x, m_y ,m_z;
    
public:
    /* CONSTRUCTORS */
    Vector3D(float x = 0.f, float y = 0.f, float z = 0.f);
    
    /* DESTRUCTOR */
    ~Vector3D() = default;
    
    /* GETTERS */
    
    // Attributes
    inline float x() const { return m_x; }
    inline float y() const { return m_y; }
    inline float z() const { return m_z; }
    
    // Computed values
    float norm() const;
    float squaredNorm() const;
    
    /* OPERATIONS */
    
    // Scalar multiplication
    Vector3D operator*(float scalar) const;
    Vector3D& operator*=(float other);
    
    // Scalar division
    Vector3D operator/(float scalar) const;
    Vector3D& operator/=(float other);
    
    // Cross product (produit vectoriel)
    Vector3D operator*(const Vector3D& other) const;
    Vector3D& operator*=(const Vector3D& other);
    
    // Sum
    Vector3D operator+(const Vector3D& a) const;
    Vector3D& operator+=(const Vector3D& other);
    
    // Subtraction
    Vector3D operator-(const Vector3D& other) const;
    Vector3D& operator-=(const Vector3D& other);


    bool operator==(const Vector3D& a) const {
        return m_x == a.x() && m_y == a.y() && m_z == a.z();
    }
    
    // Dot product (produit scalaire)
    float dot(const Vector3D& other) const;
    
    // Components product
    Vector3D componentsProduct(const Vector3D& other) const;
    
    // Normalization
    Vector3D normalize() const;
    void normalizeInPlace();
    
    /* OPEN FRAMEWORK */
    glm::vec2 v2() const;
    glm::vec3 v3() const;
    
};
