#include <gtest/gtest.h>
#include "../../include/univers.hpp"

TEST(UniversTest, Setters) {
    Univers<3> univers({100, 100, 100}, 10.0);

    univers.setCaracteristicLength({100, 100, 10});
    univers.setCutOffRadius(20.0);

    EXPECT_DOUBLE_EQ(univers.getCaracteristicLength()[2], 10.0);
    EXPECT_DOUBLE_EQ(univers.getCutOffRadius(), 20.0);
    EXPECT_EQ(univers.getCellLength()[0], static_cast<int>(std::ceil(100.0 / 20.0)));
}