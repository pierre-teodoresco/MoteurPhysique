//
//  Vector3D.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
//

#ifndef Vector3D_hpp
#define Vector3D_hpp

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

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
    
    // Cross product (produit vectoriel)
    Vector3D operator*(const Vector3D& other) const;
    Vector3D& operator*=(const Vector3D& other);
    
    // Sum
    Vector3D operator+(const Vector3D& other) const;
    Vector3D& operator+=(const Vector3D& other);
    
    // Subtraction
    Vector3D operator-(const Vector3D& other) const;
    Vector3D& operator-=(const Vector3D& other);
    
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

#endif /* Vector3D_hpp */
