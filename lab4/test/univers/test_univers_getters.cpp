#include <gtest/gtest.h>
#include "../../include/univers.hpp"

TEST(UniversTest, Getters) {

    Univers<3> univers({100.0, 100.0, 100.0}, 10.0);

    EXPECT_DOUBLE_EQ(univers.getCaracteristicLength()[0], 100.0);
    EXPECT_DOUBLE_EQ(univers.getCutOffRadius(), 10.0);
    EXPECT_EQ(univers.getCellLength()[0], static_cast<int>(std::ceil(100.0 / 10.0)));
    EXPECT_TRUE(univers.getCells().empty());
}