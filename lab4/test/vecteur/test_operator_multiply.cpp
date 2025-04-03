#include <gtest/gtest.h>
#include "../include/vecteur.hpp"

TEST(VecteurTest, OperatorMultiply) {
    Vecteur<3> v1_3({1.0, 2.0, 3.0});
    Vecteur<3> v2_3({4.0, 5.0, 6.0});
    Vecteur<3> v3_3 = v1_3 * v2_3;
    EXPECT_EQ(v3_3.get(0), 4.0);
    EXPECT_EQ(v3_3.get(1), 10.0);
    EXPECT_EQ(v3_3.get(2), 18.0);

    Vecteur<3> v4_3 = v1_3 * 2.0;
    EXPECT_EQ(v4_3.get(0), 2.0);
    EXPECT_EQ(v4_3.get(1), 4.0);
    EXPECT_EQ(v4_3.get(2), 6.0);

    Vecteur<3> v5_3 = 2.0 * v1_3;
    EXPECT_EQ(v5_3.get(0), 2.0);
    EXPECT_EQ(v5_3.get(1), 4.0);
    EXPECT_EQ(v5_3.get(2), 6.0);
}