#include <gtest/gtest.h>
#include "../../include/univers.hpp"

TEST(UniversTest, Setters) {
    Univers<3> univers(100.0, 10.0);

    univers.setCaracteristicLength(200.0);
    univers.setCutOffRadius(20.0);

    EXPECT_DOUBLE_EQ(univers.getCaracteristicLength(), 200.0);
    EXPECT_DOUBLE_EQ(univers.getCutOffRadius(), 20.0);
    EXPECT_EQ(univers.getCellLength(), static_cast<int>(std::ceil(200.0 / 20.0)));
}