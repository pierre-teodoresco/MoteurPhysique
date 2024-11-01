#pragma once

#include "Vector3D.hpp" // Assuming Vector3D may be used in future extensions

class Matrix4 {
private:
    float m_data[4][4];

public:
    /* CONSTRUCTORS */
    Matrix4();
    Matrix4(float data[4][4]);

    /* DESTRUCTOR */
    ~Matrix4() = default;

    /* GETTERS */
    float get(unsigned int row, unsigned int col) const;

    /* OPERATIONS */

    // Scalar multiplication
    Matrix4 operator*(float scalar) const;
    Matrix4& operator*=(float scalar);

    // Matrix multiplication
    Matrix4 operator*(const Matrix4& other) const;
    Matrix4& operator*=(const Matrix4& other);

    // Addition
    Matrix4 operator+(const Matrix4& other) const;
    Matrix4& operator+=(const Matrix4& other);

    // Subtraction
    Matrix4 operator-(const Matrix4& other) const;
    Matrix4& operator-=(const Matrix4& other);

    // Transpose
    Matrix4 transpose() const;

    // Determinant (simplified for 4x4 matrices)
    float determinant() const;
    
    /* COMPARISONS */
    bool operator==(const Matrix4& other) const;

    /* STATIC METHODS */
    static Matrix4 identity();
};
