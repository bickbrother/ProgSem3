#include "gtest/gtest.h"
#include "WordCont.h"

TEST(simple, 1) {
    EXPECT_EQ(19, WordCont("-l", "C:/Users/ignat/CLionProjects/ProgSem3/testCK.txt"));
}
TEST(simple, 2) {
    EXPECT_EQ(19, WordCont("-w","C:/Users/ignat/CLionProjects/ProgSem3/testCK.txt"));
}
TEST(simple, 3) {
    EXPECT_EQ(151, WordCont("-c","C:/Users/ignat/CLionProjects/ProgSem3/testCK.txt"));
}