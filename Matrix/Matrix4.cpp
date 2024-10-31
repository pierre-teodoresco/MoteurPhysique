#include "Matrix4.hpp"

/* CONSTRUCTORS */
Matrix4::Matrix4() {
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            m_data[i][j] = 0;
        }
    }
}

Matrix4::Matrix4(float data[4][4]) {
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            m_data[i][j] = data[i][j];
        }
    }
}

/* GETTERS */
float Matrix4::get(unsigned int row, unsigned int col) const {
    return m_data[row][col];
}

/* OPERATIONS */

// Scalar multiplication
Matrix4 Matrix4::operator*(float scalar) const {
    Matrix4 result;
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            result.m_data[i][j] = m_data[i][j] * scalar;
        }
    }
    return result;
}

Matrix4& Matrix4::operator*=(float scalar) {
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            m_data[i][j] *= scalar;
        }
    }
    return *this;
}

// Matrix multiplication
Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            float sum = 0;
            for (unsigned int k = 0; k < 4; ++k) {
                sum += m_data[i][k] * other.m_data[k][j];
            }
            result.m_data[i][j] = sum;
        }
    }
    return result;
}

Matrix4& Matrix4::operator*=(const Matrix4& other) {
    *this = *this * other;
    return *this;
}

// Addition
Matrix4 Matrix4::operator+(const Matrix4& other) const {
    Matrix4 result;
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            result.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
        }
    }
    return result;
}

Matrix4& Matrix4::operator+=(const Matrix4& other) {
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            m_data[i][j] += other.m_data[i][j];
        }
    }
    return *this;
}

// Subtraction
Matrix4 Matrix4::operator-(const Matrix4& other) const {
    Matrix4 result;
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            result.m_data[i][j] = m_data[i][j] - other.m_data[i][j];
        }
    }
    return result;
}

Matrix4& Matrix4::operator-=(const Matrix4& other) {
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            m_data[i][j] -= other.m_data[i][j];
        }
    }
    return *this;
}

// Transpose
Matrix4 Matrix4::transpose() const {
    Matrix4 result;
    for (unsigned int i = 0; i < 4; ++i) {
        for (unsigned int j = 0; j < 4; ++j) {
            result.m_data[i][j] = m_data[j][i];
        }
    }
    return result;
}

// Determinant (Simplified; this calculation may be complex for 4x4 matrices)
float Matrix4::determinant() const {
    // Determinant calculation for 4x4 matrices can be very complex;
    // here we use a simplified or placeholder approach.
    return 0; // Placeholder: You should implement the actual determinant logic if needed.
}

/* STATIC METHODS */
Matrix4 Matrix4::identity() {
    float id[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    return Matrix4(id);
}
