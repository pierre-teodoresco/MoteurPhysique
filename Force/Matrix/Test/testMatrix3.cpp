#include "testMatrix3.hpp"
#include <iostream>
#include <cassert>

void testMatrixAddition() {
    float data1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float data2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3 m1(data1);
    Matrix3 m2(data2);
    Matrix3 m3 = m1 + m2;

    assert(m3.get(0, 0) == 10);
    assert(m3.get(1, 1) == 10);
    assert(m3.get(2, 2) == 10);
    std::cout << "Test d'addition de matrices réussi.\n";
}

void testMatrixMultiplication() {
    float data1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float data2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3 m1(data1);
    Matrix3 m2(data2);
    Matrix3 m3 = m1 * m2;

    assert(m3.get(0, 0) == 30);
    assert(m3.get(1, 1) == 84);
    assert(m3.get(2, 2) == 138);
    std::cout << "Test de multiplication de matrices réussi.\n";
}

void testMatrixTranspose() {
    float data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3 m(data);
    Matrix3 mt = m.transpose();

    assert(mt.get(0, 1) == 4);
    assert(mt.get(1, 0) == 2);
    std::cout << "Test de transposition réussi.\n";
}

void testMatrixDeterminant() {
    float data[3][3] = {{1, 2, 3}, {0, 1, 4}, {5, 6, 0}};
    Matrix3 m(data);
    float det = m.determinant();

    assert(det == 1); // Determinant calculation
    std::cout << "Test de déterminant réussi.\n";
}

void test::startMatrix3Test() {
    testMatrixAddition();
    testMatrixMultiplication();
    testMatrixTranspose();
    testMatrixDeterminant();

    std::cout << "Tous les tests de matrices sont réussis.\n";
}
