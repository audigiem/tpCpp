#include <gtest/gtest.h>
#include "../include/vecteur.hpp"

TEST(VecteurTest, OperatorPlus) {
    Vecteur<3> v1_3({1.0, 2.0, 3.0});
    Vecteur<3> v2_3({4.0, 5.0, 6.0});
    Vecteur<3> v3_3 = v1_3 + v2_3;
    EXPECT_EQ(v3_3.get(0), 5.0);
    EXPECT_EQ(v3_3.get(1), 7.0);
    EXPECT_EQ(v3_3.get(2), 9.0);

    Vecteur<2> v1_2({1.0, 2.0});
    Vecteur<2> v2_2({4.0, 5.0});
    Vecteur<2> v3_2 = v1_2 + v2_2;
    EXPECT_EQ(v3_2.get(0), 5.0);
    EXPECT_EQ(v3_2.get(1), 7.0);

    Vecteur<1> v1_1({1.0});
    Vecteur<1> v2_1({4.0});
    Vecteur<1> v3_1 = v1_1 + v2_1;
    EXPECT_EQ(v3_1.get(0), 5.0);
}