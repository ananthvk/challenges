#include "hashmap.hpp"
#include "gtest/gtest.h"

TEST(HashMapTest, Empty)
{
    HashMap<std::string, int> h;
    ASSERT_EQ(h.size(), 0);
    ASSERT_EQ(h.load_factor(), 0);
    ASSERT_NEAR(h.max_load_factor(), h.DEFAULT_MAX_LOAD_FACTOR, 1e-5);
}

TEST(HashMapTest, ModifyLoadFactor)
{
    HashMap<std::string, int> h;
    h.max_load_factor(0.3f);
    ASSERT_NEAR(h.max_load_factor(), 0.3, 1e-5);
    h.max_load_factor(0.5f);
    ASSERT_NEAR(h.max_load_factor(), 0.5, 1e-5);
    ASSERT_EQ(h.load_factor(), 0);
}

TEST(HashMapTest, InsertAndRetrieveValues)
{
    HashMap<std::string, int> h;
    h.insert("Hello there", 58);
    h.insert("Who are you?", 31);
    h.insert("C++", 198339);
    h.insert("XYZ", -88881);
    ASSERT_EQ(h.size(), 4);
    ASSERT_EQ(h.get("Hello there"), 58);
    ASSERT_EQ(h.get("Who are you?"), 31);
    ASSERT_EQ(h.get("C++"), 198339);
    ASSERT_EQ(h.get("XYZ"), -88881);
    ASSERT_EQ(h.size(), 4);
}

TEST(HashMapTest, LargeNumberOfValues)
{
    HashMap<int, long long int> h;
    for (int i = 0; i < 780000; i++)
        h.insert(i, static_cast<long long int>(i) * i);
    ASSERT_EQ(h.size(), 780000);
    for (int i = 0; i < 780000; i++)
        ASSERT_EQ(h.get(i), static_cast<long long int>(i) * i);
}

TEST(HashMapTest, ElementsThatAreNotPresent)
{
    HashMap<std::string, int> h;
    h.insert("Hello there", 58);
    h.insert("Who are you?", 31);
    ASSERT_EQ(h.get("SDFSDF"), std::nullopt);
    ASSERT_EQ(h.get(""), std::nullopt);
    ASSERT_EQ(h.get("Hello there "), std::nullopt);
}

TEST(HashMapTest, UpdateOperation)
{
    HashMap<int, long long int> h;
    for (int i = 0; i < 5000; i++)
        h.insert(i, static_cast<long long int>(i) * i);
    for (int i = 0; i < 5000; i++)
        h.insert(i, static_cast<long long int>(i) * i * i);
    for (int i = 0; i < 5000; i++)
        ASSERT_EQ(h.get(i), static_cast<long long int>(i) * i * i);

    HashMap<std::string, std::string> kv;
    kv.insert("Hello", "World");
    kv.insert("C+", "+");
    kv.insert("Empty", "");
    ASSERT_EQ(kv.get("Hello"), "World");
    ASSERT_EQ(kv.get("C+"), "+");
    ASSERT_EQ(kv.get("Empty"), "");

    kv.insert("Hello", "World New");
    kv.insert("C+", "New +");
    kv.insert("Empty", "Not anymore");
    ASSERT_EQ(kv.get("Hello"), "World New");
    ASSERT_EQ(kv.get("C+"), "New +");
    ASSERT_EQ(kv.get("Empty"), "Not anymore");
}

TEST(HashMapTest, CountNumberOfStrings)
{
    const char *alphabets = "abcdefghijklmnopqrstuvwxyz";

    // Get all two letter strings
    HashMap<std::string, int> hm;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            std::string s = {alphabets[i], alphabets[j]};
            hm.insert(s, hm.get(s).value_or(0) + 1);
        }
    }
    ASSERT_EQ(hm.size(), 26 * 26);
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            std::string s = {alphabets[i], alphabets[j]};
            ASSERT_EQ(hm.get(s), 1);
        }
    }
}

TEST(HashMapTest, CustomHashFunction)
{
    struct SimpleHasher
    {
        std::size_t operator()(const std::string &x) const
        {
            size_t hash = 0;
            for (auto ch : x)
                hash += ch;
            return hash;
        }
    };

    HashMap<std::string, std::string, SimpleHasher> hm;
    ASSERT_EQ(hm.size(), 0);
    ASSERT_EQ(hm.get("abc"), std::nullopt);

    hm.insert("abcd", "Value 1");
    hm.insert("abdc", "Value 2");
    hm.insert("acbd", "Some other value");
    hm.insert("acdb", "Value 3");
    hm.insert("adbc", "Val");
    hm.insert("adcb", "X");
    ASSERT_EQ(hm.size(), 6);

    hm.insert("bacd", "S");
    hm.insert("badc", "");
    hm.insert("cabd", "jhik");
    hm.insert("cadb", "adfa");
    hm.insert("dabc", "12345");
    hm.insert("dacb", "171");
    ASSERT_EQ(hm.size(), 12);

    ASSERT_EQ(hm.get("abcd"), "Value 1");
    ASSERT_EQ(hm.get("abdc"), "Value 2");
    ASSERT_EQ(hm.get("acbd"), "Some other value");
    ASSERT_EQ(hm.get("acdb"), "Value 3");
    ASSERT_EQ(hm.get("adbc"), "Val");
    ASSERT_EQ(hm.get("adcb"), "X");
    ASSERT_EQ(hm.get("bacd"), "S");
    ASSERT_EQ(hm.get("badc"), "");
    ASSERT_EQ(hm.get("cabd"), "jhik");
    ASSERT_EQ(hm.get("cadb"), "adfa");
    ASSERT_EQ(hm.get("dabc"), "12345");
    ASSERT_EQ(hm.get("dacb"), "171");

    hm.insert("abcd", "Value 9");
    hm.insert("abdc", "Value 10");
    hm.insert("acbd", "");
    hm.insert("acdb", "xyz123");
    hm.insert("adbc", "abcdef");
    hm.insert("adcb", "val");
    hm.insert("bacd", "S");
    hm.insert("badc", "");
    hm.insert("cabd", "kks");
    hm.insert("cadb", "asdfadfaf");
    hm.insert("dabc", "122222");
    hm.insert("dacb", "171");
    ASSERT_EQ(hm.size(), 12);

    ASSERT_EQ(hm.get("abcd"), "Value 9");
    ASSERT_EQ(hm.get("abdc"), "Value 10");
    ASSERT_EQ(hm.get("acbd"), "");
    ASSERT_EQ(hm.get("acdb"), "xyz123");
    ASSERT_EQ(hm.get("adbc"), "abcdef");
    ASSERT_EQ(hm.get("adcb"), "val");
    ASSERT_EQ(hm.get("bacd"), "S");
    ASSERT_EQ(hm.get("badc"), "");
    ASSERT_EQ(hm.get("cabd"), "kks");
    ASSERT_EQ(hm.get("cadb"), "asdfadfaf");
    ASSERT_EQ(hm.get("dabc"), "122222");
    ASSERT_EQ(hm.get("dacb"), "171");
}

TEST(HashMapTest, TestErase)
{
    struct SimpleHasher
    {
        std::size_t operator()(const std::string &x) const
        {
            size_t hash = 0;
            for (auto ch : x)
                hash += ch;
            return hash;
        }
    };

    HashMap<std::string, std::string, SimpleHasher> hm;
    ASSERT_EQ(hm.size(), 0);
    ASSERT_EQ(hm.get("abc"), std::nullopt);

    hm.insert("abcd", "Value 1");
    hm.insert("abdc", "Value 2");
    hm.insert("acbd", "Some other value");
    hm.insert("acdb", "Value 3");
    hm.insert("adbc", "Val");
    hm.insert("adcb", "X");
    ASSERT_EQ(hm.size(), 6);

    hm.insert("bacd", "S");
    hm.insert("badc", "");
    hm.insert("cabd", "jhik");
    hm.insert("cadb", "adfa");
    hm.insert("dabc", "12345");
    hm.insert("dacb", "171");
    ASSERT_EQ(hm.size(), 12);

    ASSERT_EQ(hm.get("abcd"), "Value 1");
    ASSERT_EQ(hm.get("abdc"), "Value 2");
    ASSERT_EQ(hm.get("acbd"), "Some other value");
    ASSERT_EQ(hm.get("acdb"), "Value 3");
    ASSERT_EQ(hm.get("adbc"), "Val");
    ASSERT_EQ(hm.get("adcb"), "X");
    ASSERT_EQ(hm.get("bacd"), "S");
    ASSERT_EQ(hm.get("badc"), "");
    ASSERT_EQ(hm.get("cabd"), "jhik");
    ASSERT_EQ(hm.get("cadb"), "adfa");
    ASSERT_EQ(hm.get("dabc"), "12345");
    ASSERT_EQ(hm.get("dacb"), "171");

    hm.insert("abcd", "Value 9");
    hm.insert("abdc", "Value 10");
    hm.insert("acbd", "");
    hm.insert("acdb", "xyz123");
    hm.insert("adbc", "abcdef");
    hm.insert("adcb", "val");
    hm.insert("bacd", "S");
    hm.insert("badc", "");
    hm.insert("cabd", "kks");
    hm.insert("cadb", "asdfadfaf");
    hm.insert("dabc", "122222");
    hm.insert("dacb", "171");
    ASSERT_EQ(hm.size(), 12);

    ASSERT_EQ(hm.get("abcd"), "Value 9");
    ASSERT_EQ(hm.get("abdc"), "Value 10");
    ASSERT_EQ(hm.get("acbd"), "");
    ASSERT_EQ(hm.get("acdb"), "xyz123");
    ASSERT_EQ(hm.get("adbc"), "abcdef");
    ASSERT_EQ(hm.get("adcb"), "val");
    ASSERT_EQ(hm.get("bacd"), "S");
    ASSERT_EQ(hm.get("badc"), "");
    ASSERT_EQ(hm.get("cabd"), "kks");
    ASSERT_EQ(hm.get("cadb"), "asdfadfaf");
    ASSERT_EQ(hm.get("dabc"), "122222");
    ASSERT_EQ(hm.get("dacb"), "171");

    ASSERT_TRUE(hm.erase("abcd"));
    ASSERT_EQ(hm.size(), 11);
    ASSERT_EQ(hm.get("abcd"), std::nullopt);

    ASSERT_TRUE(hm.erase("dacb"));
    ASSERT_EQ(hm.size(), 10);
    ASSERT_EQ(hm.get("dacb"), std::nullopt);

    ASSERT_FALSE(hm.erase("notfound"));
    ASSERT_EQ(hm.size(), 10);

    std::vector<std::string> keys = {"abdc", "acbd", "acdb", "adbc", "adcb",
                                     "bacd", "badc", "cabd", "cadb", "dabc"};
    for (const auto &key : keys)
    {
        ASSERT_TRUE(hm.erase(key));
    }
    ASSERT_EQ(hm.size(), 0);

    for (const auto &key : keys)
    {
        ASSERT_EQ(hm.get(key), std::nullopt);
    }
    ASSERT_EQ(hm.get("abcd"), std::nullopt);
    ASSERT_EQ(hm.get("dacb"), std::nullopt);

    // Insert again
    ASSERT_EQ(hm.size(), 0);
    ASSERT_EQ(hm.get("abc"), std::nullopt);

    hm.insert("abcd", "Value 1");
    hm.insert("abdc", "Value 2");
    hm.insert("acbd", "Some other value");
    hm.insert("acdb", "Value 3");
    hm.insert("adbc", "Val");
    hm.insert("adcb", "X");
    ASSERT_EQ(hm.size(), 6);

    hm.insert("bacd", "S");
    hm.insert("badc", "");
    hm.insert("cabd", "jhik");
    hm.insert("cadb", "adfa");
    hm.insert("dabc", "12345");
    hm.insert("dacb", "171");
    ASSERT_EQ(hm.size(), 12);

    ASSERT_EQ(hm.get("abcd"), "Value 1");
    ASSERT_EQ(hm.get("abdc"), "Value 2");
    ASSERT_EQ(hm.get("acbd"), "Some other value");
    ASSERT_EQ(hm.get("acdb"), "Value 3");
    ASSERT_EQ(hm.get("adbc"), "Val");
    ASSERT_EQ(hm.get("adcb"), "X");
    ASSERT_EQ(hm.get("bacd"), "S");
    ASSERT_EQ(hm.get("badc"), "");
    ASSERT_EQ(hm.get("cabd"), "jhik");
    ASSERT_EQ(hm.get("cadb"), "adfa");
    ASSERT_EQ(hm.get("dabc"), "12345");
    ASSERT_EQ(hm.get("dacb"), "171");

    hm.insert("abcd", "Value 9");
    hm.insert("abdc", "Value 10");
    hm.insert("acbd", "");
    hm.insert("acdb", "xyz123");
    hm.insert("adbc", "abcdef");
    hm.insert("adcb", "val");
    hm.insert("bacd", "S");
    hm.insert("badc", "");
    hm.insert("cabd", "kks");
    hm.insert("cadb", "asdfadfaf");
    hm.insert("dabc", "122222");
    hm.insert("dacb", "171");
    ASSERT_EQ(hm.size(), 12);
}

TEST(HashMapTest, InterleavingSetGetErase)
{
    struct SimpleHasher
    {
        std::size_t operator()(const std::string &x) const
        {
            size_t hash = 0;
            for (auto ch : x)
                hash += ch;
            return hash;
        }
    };

    HashMap<std::string, std::string, SimpleHasher> hm;

    std::vector<std::string> keys = {"abcd", "dacb", "bcad", "cbad", "adbc", "badc", "cdab",
                                     "dbac", "acbd", "bdac", "cabd", "dabc", "abdc", "cdba",
                                     "bacd", "dcab", "acdb", "bcda", "cadb", "dbca"};
    std::vector<std::string> values = {
        "String 0",  "String 1",  "String 2",  "String 3",  "String 4",  "String 5",  "String 6",
        "String 7",  "String 8",  "String 9",  "String 10", "String 11", "String 12", "String 13",
        "String 14", "String 15", "String 16", "String 17", "String 18", "String 19"};

    // Interleave insert, get, erase
    int count = 0;
    for (int i = 0; i < 20; ++i)
    {
        // Insert
        count++;
        ASSERT_TRUE(hm.insert(keys[i], values[i]));
        ASSERT_EQ(hm.size(), count);
        // Get
        ASSERT_EQ(hm.get(keys[i]), values[i]);
        // Erase every 3rd key (except the first)
        if (i > 0 && i % 3 == 0)
        {
            count--;
            ASSERT_TRUE(hm.erase(keys[i]));
            ASSERT_EQ(hm.get(keys[i]), std::nullopt);
            ASSERT_EQ(hm.size(), count);
        }
    }

    for (int i = 0; i < 20; ++i)
    {
        if (i > 0 && i % 3 == 0)
        {
            ASSERT_EQ(hm.get(keys[i]), std::nullopt);
        }
        else
        {
            ASSERT_EQ(hm.get(keys[i]), values[i]);
        }
    }

    int remaining = hm.size();
    for (int i = 0; i < 20; ++i)
    {
        if (hm.get(keys[i]) != std::nullopt)
        {
            ASSERT_TRUE(hm.erase(keys[i]));
            --remaining;
            ASSERT_EQ(hm.get(keys[i]), std::nullopt);
            ASSERT_EQ(hm.size(), remaining);
        }
    }
    ASSERT_EQ(hm.size(), 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}