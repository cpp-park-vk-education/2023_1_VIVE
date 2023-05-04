#include "gtest/gtest.h"

#include "client.hpp"

TEST(Lib_test, test_foo) {
    std::string a = "Foo lib";
    EXPECT_EQ(a, a);
}
