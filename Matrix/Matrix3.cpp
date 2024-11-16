#include "Matrix3.hpp"

/* CONSTRUCTORS */
Matrix3::Matrix3() {
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            m_data[i][j] = 0;
        }
    }
}

Matrix3::Matrix3(float data[3][3]) {
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            m_data[i][j] = data[i][j];
        }
    }
}

/* GETTERS */
float Matrix3::get(unsigned int row, unsigned int col) const {
    return m_data[row][col];
}

/* OPERATIONS */

// Scalar multiplication
Matrix3 Matrix3::operator*(float scalar) const {
    Matrix3 result;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            result.m_data[i][j] = m_data[i][j] * scalar;
        }
    }
    return result;
}

Matrix3& Matrix3::operator*=(float scalar) {
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            m_data[i][j] *= scalar;
        }
    }
    return *this;
}

// Matrix multiplication
Matrix3 Matrix3::operator*(const Matrix3& other) const {
    Matrix3 result;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            result.m_data[i][j] = 0;
            for (unsigned int k = 0; k < 3; ++k) {
                result.m_data[i][j] += m_data[i][k] * other.m_data[k][j];
            }
        }
    }
    return result;
}

Matrix3& Matrix3::operator*=(const Matrix3& other) {
    *this = *this * other;
    return *this;
}

// Vector multiplication
Vector3D Matrix3::operator*(const Vector3D& vector) const {
    return {
        m_data[0][0] * vector.x() + m_data[0][1] * vector.y() + m_data[0][2] * vector.z(),
        m_data[1][0] * vector.x() + m_data[1][1] * vector.y() + m_data[1][2] * vector.z(),
        m_data[2][0] * vector.x() + m_data[2][1] * vector.y() + m_data[2][2] * vector.z()
    };
}

// Addition
Matrix3 Matrix3::operator+(const Matrix3& other) const {
    Matrix3 result;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            result.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
        }
    }
    return result;
}

Matrix3& Matrix3::operator+=(const Matrix3& other) {
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            m_data[i][j] += other.m_data[i][j];
        }
    }
    return *this;
}

// Subtraction
Matrix3 Matrix3::operator-(const Matrix3& other) const {
    Matrix3 result;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            result.m_data[i][j] = m_data[i][j] - other.m_data[i][j];
        }
    }
    return result;
}

Matrix3& Matrix3::operator-=(const Matrix3& other) {
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            m_data[i][j] -= other.m_data[i][j];
        }
    }
    return *this;
}

// Transpose
Matrix3 Matrix3::transpose() const {
    Matrix3 result;
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            result.m_data[i][j] = m_data[j][i];
        }
    }
    return result;
}

// Determinant
float Matrix3::determinant() const {
    return m_data[0][0] * (m_data[1][1] * m_data[2][2] - m_data[1][2] * m_data[2][1]) -
           m_data[0][1] * (m_data[1][0] * m_data[2][2] - m_data[1][2] * m_data[2][0]) +
           m_data[0][2] * (m_data[1][0] * m_data[2][1] - m_data[1][1] * m_data[2][0]);
}

/* COMPARISONS */
bool Matrix3::operator==(const Matrix3& other) const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (m_data[i][j] != other.m_data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

/* STATIC METHODS */
Matrix3 Matrix3::identity() {
    float id[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    return Matrix3(id);
}
