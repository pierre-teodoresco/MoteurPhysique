//
//  Vector3D.hpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 16/09/2024.
// OK
//

#ifndef Vector3D_hpp
#define Vector3D_hpp

class Vector3D {

private:
    float m_x, m_y ,m_z;
    
public:
    /* CONSTRUCTORS */
    Vector3D(float x = 0.f, float y = 0.f, float z = 0.f);
    
    /* DESTRUCTOR */
    ~Vector3D();
    
    /* GETTERS */
    
    // Attributes
    float x() const;
    float y() const;
    float z() const;
    
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
    void normalize();
};

#endif /* Vector3D_hpp */
