#include "../include/vecteur.h"

int main(){
    // Create two vectors
    Vecteur v1(1.0, 2.0, 3.0);
    Vecteur v2(4.0, 5.0, 6.0);

    // Test the output operator
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;


    // Test the scalar product
    Vecteur scalarProduct = v1 * v2;
    std::cout << "Scalar Product: " << scalarProduct << std::endl;

    // Test the cross product
    Vecteur crossProduct = v1 ^ v2;
    std::cout << "Cross Product: " << crossProduct << std::endl;

    // Test addition
    Vecteur sum = v1 + v2;
    std::cout << "Sum: " << sum << std::endl;

    // Test subtraction
    Vecteur difference = v1 - v2;
    std::cout << "Difference: " << difference << std::endl;

    // Test compound assignment operators
    v1 *= v2;
    std::cout << "v1 after *= v2: " << v1 << std::endl;

    v1 += v2;
    std::cout << "v1 after += v2: " << v1 << std::endl;

    v1 -= v2;
    std::cout << "v1 after -= v2: " << v1 << std::endl;


    return EXIT_SUCCESS;
}