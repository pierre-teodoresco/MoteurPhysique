#include "testMatrix4.hpp"
#include <iostream>
#include <cassert>

void testMatrix4Addition() {
    float data1[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    float data2[4][4] = {{16, 15, 14, 13}, {12, 11, 10, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}};
    Matrix4 m1(data1);
    Matrix4 m2(data2);
    Matrix4 m3 = m1 + m2;

    assert(m3.get(0, 0) == 17);
    assert(m3.get(1, 1) == 17);
    assert(m3.get(2, 2) == 17);
    assert(m3.get(3, 3) == 17);
    std::cout << "Test d'addition de matrices 4x4 réussi.\n";
}

void testMatrix4Multiplication() {
    float data1[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    float data2[4][4] = {{16, 15, 14, 13}, {12, 11, 10, 9}, {8, 7, 6, 5}, {4, 3, 2, 1}};
    Matrix4 m1(data1);
    Matrix4 m2(data2);
    Matrix4 m3 = m1 * m2;

    assert(m3.get(0, 0) == 80); // Verify calculation
    assert(m3.get(1, 0) == 240);
    assert(m3.get(1, 2) == 188);
    assert(m3.get(3, 1) == 502);
    std::cout << "Test de multiplication de matrices 4x4 réussi.\n";
}

void testMatrix4Transpose() {
    float data[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    Matrix4 m(data);
    Matrix4 mt = m.transpose();

    assert(mt.get(0, 1) == 5);
    assert(mt.get(1, 0) == 2);
    std::cout << "Test de transposition 4x4 réussi.\n";
}

void testMatrix4Determinant() {
    float data[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    Matrix4 m(data);
    float det = m.determinant();

    assert(det == 0); // Placeholder value; actual determinant logic needed
    std::cout << "Test de déterminant 4x4 réussi.\n";
}

void test::startMatrix4Test() {
    std::cout << "Début des tests de la classe Matrix4 :\n";

    testMatrix4Addition();
    testMatrix4Multiplication();
    testMatrix4Transpose();
    testMatrix4Determinant();

    std::cout << "Tous les tests de la classe Matrix4 sont réussis.\n";
}
