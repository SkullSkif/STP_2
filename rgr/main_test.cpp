#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <cstring>
#include "string.cpp"

TEST(COWStringTest, Constructors) {
    string s1;
    EXPECT_TRUE(s1.empty());
    EXPECT_EQ(s1.size(), 0);
    
    string s2("hello");
    EXPECT_EQ(s2.size(), 5);
    EXPECT_STREQ(s2.c_str(), "hello");
    
    string s3(s2);
    EXPECT_EQ(s3.size(), 5);
    EXPECT_STREQ(s3.c_str(), "hello");
}

TEST(COWStringTest, AssignmentAndCOW) {
    string s1("original");
    string s2 = s1;
    
    EXPECT_STREQ(s1.c_str(), s2.c_str());
    
    s2[0] = 'O';
    EXPECT_STREQ(s1.c_str(), "original");
    EXPECT_STREQ(s2.c_str(), "Original");
}

TEST(COWStringTest, OperatorBracketAndAt) {
    string s("test");
    EXPECT_EQ(s[0], 't');
    EXPECT_EQ(s.at(1), 'e');
    
    s[0] = 'T';
    EXPECT_STREQ(s.c_str(), "Test");
    
    EXPECT_THROW(s.at(10), std::out_of_range);
}

TEST(COWStringTest, Iterators) {
    string s("hello");
    
    std::vector<char> chars(s.begin(), s.end());
    std::vector<char> expected = {'h', 'e', 'l', 'l', 'o'};
    EXPECT_EQ(chars, expected);
    
    std::vector<char> reverse_chars(s.rbegin(), s.rend());
    std::vector<char> expected_reverse = {'o', 'l', 'l', 'e', 'h'};
    EXPECT_EQ(reverse_chars, expected_reverse);
    
    *s.begin() = 'H';
    EXPECT_STREQ(s.c_str(), "Hello");
}

TEST(COWStringTest, ResizeAndReserve) {
    string s;
    s.reserve(100);
    EXPECT_GE(s.capacity(), 100);
    EXPECT_TRUE(s.empty());
    
    s.resize(5, 'a');
    EXPECT_EQ(s.size(), 5);
    EXPECT_STREQ(s.c_str(), "aaaaa");
    
    s.resize(3);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], 'a');
    EXPECT_EQ(s[1], 'a');
    EXPECT_EQ(s[2], 'a');
    EXPECT_EQ(std::strlen(s.c_str()), 3); 
}

TEST(COWStringTest, InsertAndErase) {
    string s("world");
    s.insert(s.cbegin(), 'H');
    EXPECT_STREQ(s.c_str(), "Hworld");
    
    s.insert(s.cbegin() + 1, 'e');
    EXPECT_STREQ(s.c_str(), "Heworld");
    
    s.insert(s.cbegin() + 2, 'l');
    s.insert(s.cbegin() + 3, 'l');
    s.insert(s.cbegin() + 4, 'o');
    s.insert(s.cbegin() + 5, ' ');
    EXPECT_STREQ(s.c_str(), "Hello world");
    
    s.erase(s.cbegin() + 5, s.cend());
    EXPECT_STREQ(s.c_str(), "Hello");
    
    s.erase(s.cbegin() + 1);
    EXPECT_STREQ(s.c_str(), "Hllo");
}

TEST(COWStringTest, PushBack) {
    string s;
    s.push_back('h');
    s.push_back('e');
    s.push_back('l');
    s.push_back('l');
    s.push_back('o');
    EXPECT_STREQ(s.c_str(), "hello");
}

TEST(COWStringTest, ShrinkToFit) {
    string s("test");
    s.reserve(100);
    EXPECT_GE(s.capacity(), 100);
    
    std::string old_data = s.c_str();
    size_t old_size = s.size();
    
    s.shrink_to_fit();
    EXPECT_GE(s.capacity(), old_size); 
    EXPECT_STREQ(s.c_str(), old_data.c_str()); 
}

TEST(COWStringTest, OperatorsPlus) {
    string s1("hello");
    string s2(" world");
    string s3 = s1 + s2;
    EXPECT_STREQ(s3.c_str(), "hello world");
    
    string s4 = s1 + '!';
    EXPECT_STREQ(s4.c_str(), "hello!");
    
    string s5 = '!' + s1;
    EXPECT_STREQ(s5.c_str(), "!hello");
}

TEST(COWStringTest, Comparison) {
    string s1("hello");
    string s2("hello");
    string s3("world");
    
    EXPECT_TRUE(s1 == s2);
    EXPECT_TRUE(s1 != s3);
}

TEST(COWStringTest, Clear) {
    string s("hello");
    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
    EXPECT_STREQ(s.c_str(), "");
}

TEST(COWStringTest, MoveSemantics) {
    string s1("hello");
    string s2 = std::move(s1);
    EXPECT_STREQ(s2.c_str(), "hello");
    EXPECT_TRUE(s1.empty() || std::strcmp(s1.c_str(), "") == 0);
}

TEST(COWStringTest, COWSemantics) {
    string s1("shared");
    string s2 = s1;
    string s3 = s1;
    
    EXPECT_EQ(s1.c_str(), s2.c_str());
    EXPECT_EQ(s1.c_str(), s3.c_str());
    
    s2[0] = 'S';
    EXPECT_NE(s1.c_str(), s2.c_str());
    EXPECT_EQ(s1.c_str(), s3.c_str()); 
    EXPECT_STREQ(s1.c_str(), "shared");
    EXPECT_STREQ(s2.c_str(), "Shared");
    EXPECT_STREQ(s3.c_str(), "shared");
}

TEST(COWStringTest, CapacityAndEmpty) {
    string s1;
    EXPECT_TRUE(s1.empty());
    EXPECT_GE(s1.capacity(), 0);
    
    string s2("non-empty");
    EXPECT_FALSE(s2.empty());
    EXPECT_GE(s2.capacity(), s2.size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}