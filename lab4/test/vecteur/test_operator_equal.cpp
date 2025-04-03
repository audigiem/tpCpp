#include <gtest/gtest.h>
#include "../include/vecteur.hpp"

TEST(VecteurTest, OperatorEqual) {
    Vecteur<3> v1_3({1.0, 2.0, 3.0});
    Vecteur<3> v2_3({1.0, 2.0, 3.0});
    Vecteur<3> v3_3({4.0, 5.0, 6.0});

    EXPECT_TRUE(v1_3 == v2_3); // Test equality
    EXPECT_FALSE(v1_3 == v3_3); // Test inequality

    Vecteur<2> v1_2({1.0, 2.0});
    Vecteur<2> v2_2({1.0, 2.0});
    Vecteur<2> v3_2({3.0, 4.0});

    EXPECT_TRUE(v1_2 == v2_2); // Test equality
    EXPECT_FALSE(v1_2 == v3_2); // Test inequality

    Vecteur<1> v1_1({1.0});
    Vecteur<1> v2_1({1.0});
    Vecteur<1> v3_1({2.0});

    EXPECT_TRUE(v1_1 == v2_1); // Test equality
    EXPECT_FALSE(v1_1 == v3_1); // Test inequality
}