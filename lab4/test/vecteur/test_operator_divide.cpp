#include <gtest/gtest.h>
#include "../../include/vecteur.hpp"

TEST(VecteurTest, ScalarDivision) {
    Vecteur<3> v({6.0, 9.0, 12.0});
    Vecteur<3> result = v / 3.0;

    EXPECT_EQ(result.get(0), 2.0);
    EXPECT_EQ(result.get(1), 3.0);
    EXPECT_EQ(result.get(2), 4.0);
}