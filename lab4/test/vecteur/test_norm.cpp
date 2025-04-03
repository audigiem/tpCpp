#include <gtest/gtest.h>
#include <cmath>
#include "../../include/vecteur.hpp"

TEST(VecteurTest, Norm) {
    Vecteur<3> v({3.0, 4.0, 0.0});
    double result = v.norm();

    EXPECT_DOUBLE_EQ(result, 5.0); // sqrt(3^2 + 4^2 + 0^2) = 5
}

TEST(VecteurTest, NormZeroVector) {
    Vecteur<3> v({0.0, 0.0, 0.0});
    double result = v.norm();

    EXPECT_DOUBLE_EQ(result, 0.0);
}