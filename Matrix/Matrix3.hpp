#pragma once

#include "Vector/Vector3D.hpp"

class Matrix3 {
private:
    float m_data[3][3];

public:
    /* CONSTRUCTORS */
    Matrix3();
    Matrix3(float data[3][3]);

    /* DESTRUCTOR */
    ~Matrix3() = default;

    /* GETTERS */
    float get(unsigned int row, unsigned int col) const;

    /* OPERATIONS */
    
    // Scalar multiplication
    Matrix3 operator*(float scalar) const;
    Matrix3& operator*=(float scalar);

    // Matrix multiplication
    Matrix3 operator*(const Matrix3& other) const;
    Matrix3& operator*=(const Matrix3& other);

    // Vector multiplication (Matrix-Vector product)
    Vector3D operator*(const Vector3D& vector) const;

    // Addition
    Matrix3 operator+(const Matrix3& other) const;
    Matrix3& operator+=(const Matrix3& other);

    // Subtraction
    Matrix3 operator-(const Matrix3& other) const;
    Matrix3& operator-=(const Matrix3& other);

    // Transpose
    Matrix3 transpose() const;

    // Determinant
    float determinant() const;
    
    /* COMPARISONS */
    bool operator==(const Matrix3& other) const;

    /* STATIC METHODS */
    static Matrix3 identity();
};
