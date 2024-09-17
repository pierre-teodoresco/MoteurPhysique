//
//  testVector3D.cpp
//  MoteurPhysique
//
//  Created by Pierre Teodoresco on 17/09/2024.
//
#include "testVector3D.h"
#include "Vector3D.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

// Tester l'addition de deux vecteurs
void testAddition() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    Vector3D v3 = v1 + v2;

    assert(v3.x() == 5);
    assert(v3.y() == 7);
    assert(v3.z() == 9);
    std::cout << "Test d'addition réussi.\n";
}

// Tester l'opérateur +=
void testAdditionAssignment() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    v1 += v2;

    assert(v1.x() == 5);
    assert(v1.y() == 7);
    assert(v1.z() == 9);
    std::cout << "Test de l'opérateur += réussi.\n";
}

// Tester la soustraction de deux vecteurs
void testSubtraction() {
    Vector3D v1(4, 5, 6);
    Vector3D v2(1, 2, 3);
    Vector3D v3 = v1 - v2;

    assert(v3.x() == 3);
    assert(v3.y() == 3);
    assert(v3.z() == 3);
    std::cout << "Test de soustraction réussi.\n";
}

// Tester l'opérateur -=
void testSubtractionAssignment() {
    Vector3D v1(4, 5, 6);
    Vector3D v2(1, 2, 3);
    v1 -= v2;

    assert(v1.x() == 3);
    assert(v1.y() == 3);
    assert(v1.z() == 3);
    std::cout << "Test de l'opérateur -= réussi.\n";
}

// Tester la norme d'un vecteur
void testNorm() {
    Vector3D v(3, 4, 0);
    assert(v.norm() == 5); // sqrt(3^2 + 4^2)
    std::cout << "Test de norme réussi.\n";
}

// Tester le carré de la norme
void testSquaredNorm() {
    Vector3D v(3, 4, 0);
    assert(v.squaredNorm() == 25); // 3^2 + 4^2 = 9 + 16 = 25
    std::cout << "Test de norme au carré réussi.\n";
}

// Tester la multiplication par un scalaire
void testScalarMultiplication() {
    Vector3D v(1, 2, 3);
    Vector3D v2 = v * 2.0f;

    assert(v2.x() == 2);
    assert(v2.y() == 4);
    assert(v2.z() == 6);
    std::cout << "Test de multiplication par un scalaire réussi.\n";
}

// Tester l'opérateur *= avec un scalaire
void testScalarMultiplicationAssignment() {
    Vector3D v(1, 2, 3);
    v *= 2.0f;

    assert(v.x() == 2);
    assert(v.y() == 4);
    assert(v.z() == 6);
    std::cout << "Test de l'opérateur *= avec un scalaire réussi.\n";
}

// Tester le produit vectoriel
void testCrossProduct() {
    Vector3D v1(1, 0, 0);
    Vector3D v2(0, 1, 0);
    Vector3D v3 = v1 * v2; // Produit vectoriel

    assert(v3.x() == 0);
    assert(v3.y() == 0);
    assert(v3.z() == 1);
    std::cout << "Test de produit vectoriel réussi.\n";
}

// Tester l'opérateur *= pour le produit vectoriel
void testCrossProductAssignment() {
    Vector3D v1(1, 0, 0);
    Vector3D v2(0, 1, 0);
    v1 *= v2; // Produit vectoriel

    assert(v1.x() == 0);
    assert(v1.y() == 0);
    assert(v1.z() == 1);
    std::cout << "Test de l'opérateur *= pour le produit vectoriel réussi.\n";
}

// Tester le produit scalaire
void testDotProduct() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    float dotProduct = v1.dot(v2);

    assert(dotProduct == 32); // 1*4 + 2*5 + 3*6 = 32
    std::cout << "Test de produit scalaire réussi.\n";
}

// Tester le produit par composantes
void testComponentsProduct() {
    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);
    Vector3D v3 = v1.componentsProduct(v2);

    assert(v3.x() == 4); // 1 * 4
    assert(v3.y() == 10); // 2 * 5
    assert(v3.z() == 18); // 3 * 6
    std::cout << "Test de produit par composantes réussi.\n";
}

// Tester la normalisation
void testNormalize() {
    Vector3D v(3, 4, 0);
    Vector3D normalized = v.normalize();

    assert(std::abs(normalized.x() - 0.6) < 0.0001); // 3/5 = 0.6
    assert(std::abs(normalized.y() - 0.8) < 0.0001); // 4/5 = 0.8
    assert(std::abs(normalized.z()) < 0.0001);       // 0/5 = 0.0
    std::cout << "Test de normalisation réussi.\n";
}

// Tester la normalisation en place (modifie le vecteur actuel)
void testNormalizeInPlace() {
    Vector3D v(3, 4, 0);
    v.normalizeInPlace();

    assert(std::abs(v.x() - 0.6) < 0.0001); // 3/5 = 0.6
    assert(std::abs(v.y() - 0.8) < 0.0001); // 4/5 = 0.8
    assert(std::abs(v.z()) < 0.0001);       // 0/5 = 0.0
    std::cout << "Test de normalisation en place réussi.\n";
}

void test::startVector3DTest() {
    testAddition();
    testAdditionAssignment();
    testSubtraction();
    testSubtractionAssignment();
    testNorm();
    testSquaredNorm();
    testScalarMultiplication();
    testScalarMultiplicationAssignment();
    testCrossProduct();
    testCrossProductAssignment();
    testDotProduct();
    testComponentsProduct();
    testNormalize();
    testNormalizeInPlace();

    std::cout << "Tous les tests sont réussis.\n";
}
