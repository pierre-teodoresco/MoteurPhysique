#include "testMatrix3.hpp"
#include <iostream>
#include <cassert>

void testMatrixAddition() {
    float data1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float data2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3 m1(data1);
    Matrix3 m2(data2);
    Matrix3 m3 = m1 + m2;

    float data3[3][3] = {{10, 10, 10}, {10, 10, 10}, {10, 10, 10}};
    Matrix3 m3Expected(data3);
    assert(m3 == m3Expected);
    std::cout << "Test d'addition de matrices réussi.\n";
}

void testMatrixMultiplication() {
    float data1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    float data2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix3 m1(data1);
    Matrix3 m2(data2);
    Matrix3 m3 = m1 * m2;

    float data3[3][3] = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    Matrix3 m3Expected(data3);
    assert(m3 == m3Expected);
    std::cout << "Test de multiplication de matrices réussi.\n";
}

void testMatrixTranspose() {
    float data[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix3 m(data);
    Matrix3 mt = m.transpose();

    float dataT[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    Matrix3 mtExpected(dataT);
    assert(mt == mtExpected);
    std::cout << "Test de transposition réussi.\n";
}

void testMatrixDeterminant() {
    float data[3][3] = {{1, 2, 3}, {0, 1, 4}, {5, 6, 0}};
    Matrix3 m(data);
    float det = m.determinant();

    assert(det == 1); // Determinant calculation
    std::cout << "Test de déterminant réussi.\n";
}

void testInverseMatrix() {
    float data[3][3] = {{1, 2, 3}, {0, 1, 4}, {5, 6, 0}};
    Matrix3 m(data);
    Matrix3 inv = m.inverse();

    float invData[3][3] = {{-24, 18, 5}, {20, -15, -4}, {-5, 4, 1}};
    Matrix3 invExpected(invData);

    assert(inv == invExpected);
    std::cout << "Test d'inversion de matrice réussi.\n";
}

void test::startMatrix3Test() {
    std::cout << "Début des tests de la classe Matrix3 :\n";
    
    testMatrixAddition();
    testMatrixMultiplication();
    testMatrixTranspose();
    testMatrixDeterminant();
    testInverseMatrix();

    std::cout << "Tous les tests de Matrix3 sont réussis.\n\n";
}
