#include <gtest/gtest.h>
#include "../include/vecteur.hpp"

TEST(VecteurTest, Constructor) {
    Vecteur<3> v3({1.0, 2.0, 3.0});
    EXPECT_EQ(v3.get(0), 1.0);
    EXPECT_EQ(v3.get(1), 2.0);
    EXPECT_EQ(v3.get(2), 3.0);

    Vecteur<2> v2({1.0, 2.0});
    EXPECT_EQ(v2.get(0), 1.0);
    EXPECT_EQ(v2.get(1), 2.0);

    Vecteur<1> v1({1.0});
    EXPECT_EQ(v1.get(0), 1.0);
}

TEST(VecteurTest, DefaultConstructor) {
    Vecteur<3> v3;
    EXPECT_EQ(v3.get(0), 0.0);
    EXPECT_EQ(v3.get(1), 0.0);
    EXPECT_EQ(v3.get(2), 0.0);

    Vecteur<2> v2;
    EXPECT_EQ(v2.get(0), 0.0);
    EXPECT_EQ(v2.get(1), 0.0);

    Vecteur<1> v1;
    EXPECT_EQ(v1.get(0), 0.0);
}