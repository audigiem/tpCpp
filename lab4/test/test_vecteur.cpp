#include <iostream>
#include <cassert>
#include "../include/vecteur.hpp"

void test_constructor() {
    Vecteur<3> v3({1.0, 2.0, 3.0});
    std::cout << "Constructor test passed for 3D: " << v3 << std::endl;

    Vecteur<2> v2({1.0, 2.0});
    std::cout << "Constructor test passed for 2D: " << v2 << std::endl;

    Vecteur<1> v1({1.0});
    std::cout << "Constructor test passed for 1D: " << v1 << std::endl;
}

void test_default_constructor() {
    Vecteur<3> v3;
    assert(v3.get(0) == 0 && v3.get(1) == 0 && v3.get(2) == 0);
    std::cout << "Default constructor test passed for 3D: " << v3 << std::endl;

    Vecteur<2> v2;
    assert(v2.get(0) == 0 && v2.get(1) == 0);
    std::cout << "Default constructor test passed for 2D: " << v2 << std::endl;

    Vecteur<1> v1;
    assert(v1.get(0) == 0);
    std::cout << "Default constructor test passed for 1D: " << v1 << std::endl;
}

void test_operator_plus() {
    Vecteur<3> v1_3({1.0, 2.0, 3.0});
    Vecteur<3> v2_3({4.0, 5.0, 6.0});
    Vecteur<3> v3_3 = v1_3 + v2_3;
    assert(v3_3.get(0) == 5.0 && v3_3.get(1) == 7.0 && v3_3.get(2) == 9.0);
    std::cout << "Operator+ test passed for 3D: " << v3_3 << std::endl;

    Vecteur<2> v1_2({1.0, 2.0});
    Vecteur<2> v2_2({4.0, 5.0});
    Vecteur<2> v3_2 = v1_2 + v2_2;
    assert(v3_2.get(0) == 5.0 && v3_2.get(1) == 7.0);
    std::cout << "Operator+ test passed for 2D: " << v3_2 << std::endl;

    Vecteur<1> v1_1({1.0});
    Vecteur<1> v2_1({4.0});
    Vecteur<1> v3_1 = v1_1 + v2_1;
    assert(v3_1.get(0) == 5.0);
    std::cout << "Operator+ test passed for 1D: " << v3_1 << std::endl;
}

void test_operator_minus() {
    Vecteur<3> v1_3({4.0, 5.0, 6.0});
    Vecteur<3> v2_3({1.0, 2.0, 3.0});
    Vecteur<3> v3_3 = v1_3 - v2_3;
    assert(v3_3.get(0) == 3.0 && v3_3.get(1) == 3.0 && v3_3.get(2) == 3.0);
    std::cout << "Operator- test passed for 3D: " << v3_3 << std::endl;

    Vecteur<2> v1_2({4.0, 5.0});
    Vecteur<2> v2_2({1.0, 2.0});
    Vecteur<2> v3_2 = v1_2 - v2_2;
    assert(v3_2.get(0) == 3.0 && v3_2.get(1) == 3.0);
    std::cout << "Operator- test passed for 2D: " << v3_2 << std::endl;

    Vecteur<1> v1_1({4.0});
    Vecteur<1> v2_1({1.0});
    Vecteur<1> v3_1 = v1_1 - v2_1;
    assert(v3_1.get(0) == 3.0);
    std::cout << "Operator- test passed for 1D: " << v3_1 << std::endl;
}

void test_operator_multiply() {
    Vecteur<3> v1_3({1.0, 2.0, 3.0});
    Vecteur<3> v2_3({4.0, 5.0, 6.0});
    Vecteur<3> v3_3 = v1_3 * v2_3;
    assert(v3_3.get(0) == 4.0 && v3_3.get(1) == 10.0 && v3_3.get(2) == 18.0);
    std::cout << "Operator* (Vecteur) test passed for 3D: " << v3_3 << std::endl;

    Vecteur<3> v4_3 = v1_3 * 2.0;
    assert(v4_3.get(0) == 2.0 && v4_3.get(1) == 4.0 && v4_3.get(2) == 6.0);
    std::cout << "Operator* (float) test passed for 3D: " << v4_3 << std::endl;

    Vecteur<3> v5_3 = 2.0 * v1_3;
    assert(v5_3.get(0) == 2.0 && v5_3.get(1) == 4.0 && v5_3.get(2) == 6.0);
    std::cout << "Operator* (float, Vecteur) test passed for 3D: " << v5_3 << std::endl;

    Vecteur<2> v1_2({1.0, 2.0});
    Vecteur<2> v2_2({4.0, 5.0});
    Vecteur<2> v3_2 = v1_2 * v2_2;
    assert(v3_2.get(0) == 4.0 && v3_2.get(1) == 10.0);
    std::cout << "Operator* (Vecteur) test passed for 2D: " << v3_2 << std::endl;

    Vecteur<2> v4_2 = v1_2 * 2.0;
    assert(v4_2.get(0) == 2.0 && v4_2.get(1) == 4.0);
    std::cout << "Operator* (float) test passed for 2D: " << v4_2 << std::endl;

    Vecteur<2> v5_2 = 2.0 * v1_2;
    assert(v5_2.get(0) == 2.0 && v5_2.get(1) == 4.0);
    std::cout << "Operator* (float, Vecteur) test passed for 2D: " << v5_2 << std::endl;

    Vecteur<1> v1_1({1.0});
    Vecteur<1> v2_1({4.0});
    Vecteur<1> v3_1 = v1_1 * v2_1;
    assert(v3_1.get(0) == 4.0);
    std::cout << "Operator* (Vecteur) test passed for 1D: " << v3_1 << std::endl;

    Vecteur<1> v4_1 = v1_1 * 2.0;
    assert(v4_1.get(0) == 2.0);
    std::cout << "Operator* (float) test passed for 1D: " << v4_1 << std::endl;

    Vecteur<1> v5_1 = 2.0 * v1_1;
    assert(v5_1.get(0) == 2.0);
    std::cout << "Operator* (float, Vecteur) test passed for 1D: " << v5_1 << std::endl;
}

int main() {
    test_constructor();
    test_default_constructor();
    test_operator_plus();
    test_operator_minus();
    test_operator_multiply();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}