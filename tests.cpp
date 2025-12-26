#include <gtest/gtest.h>
#include "circular_buffer.h"
#include <cstdio>

TEST(CircularBuffer, Create) {
CircularBuffer<int> buf(5);
EXPECT_TRUE(buf.empty());
EXPECT_FALSE(buf.full());
}

TEST(CircularBuffer, PushPop) {
CircularBuffer<int> buf(3);
buf.push(10);
buf.push(20);
EXPECT_EQ(buf.pop(), 10);
EXPECT_EQ(buf.pop(), 20);
EXPECT_TRUE(buf.empty());
}

TEST(CircularBuffer, Full) {
CircularBuffer<int> buf(2);
buf.push(1);
buf.push(2);
EXPECT_TRUE(buf.full());
EXPECT_THROW(buf.push(3), std::runtime_error);
}

TEST(CircularBuffer, EmptyError) {
CircularBuffer<int> buf(3);
EXPECT_THROW(buf.pop(), std::runtime_error);
}

TEST(CircularBuffer, Circular) {
CircularBuffer<int> buf(3);
buf.push(1);
buf.push(2);
buf.push(3);

buf.pop();
buf.push(4);

EXPECT_EQ(buf.pop(), 2);
EXPECT_EQ(buf.pop(), 3);
EXPECT_EQ(buf.pop(), 4);
EXPECT_TRUE(buf.empty());
}

TEST(CircularBuffer, SaveLoad) {
CircularBuffer<int> buf1(3);
buf1.push(100);
buf1.push(200);
buf1.save("test.bin");

CircularBuffer<int> buf2(3);
buf2.load("test.bin");

EXPECT_EQ(buf2.get_size(), 2);
EXPECT_EQ(buf2.pop(), 100);
EXPECT_EQ(buf2.pop(), 200);

std::remove("test.bin");
}

TEST(CircularBuffer, LoadEmpty) {
CircularBuffer<int> buf1(5);
buf1.save("empty.bin");

CircularBuffer<int> buf2(5);
buf2.load("empty.bin");

EXPECT_TRUE(buf2.empty());

std::remove("empty.bin");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}