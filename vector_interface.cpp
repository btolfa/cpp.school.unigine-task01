#include "gtest\gtest.h"

#include <vector>
#include "myvector.hpp"

template<typename T>
class VectorInterfacePodTest : public ::testing::Test {};

using PodTestTypes = ::testing::Types<std::vector<int>, myvector<int>>;
TYPED_TEST_CASE(VectorInterfacePodTest, PodTestTypes);

TYPED_TEST(VectorInterfacePodTest, EmptyVectTest)
{
    TypeParam vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(std::distance(vec.begin(), vec.end()), 0);
}

TYPED_TEST(VectorInterfacePodTest, PushBackTest)
{
    TypeParam vec;
    EXPECT_EQ(0, vec.size());

    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_GE(vec.capacity(), 1);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(*vec.begin(), 1);
    EXPECT_EQ(std::distance(vec.begin(), vec.end()), 1);
}

TYPED_TEST(VectorInterfacePodTest, EraseTest)
{
    TypeParam vec;
    EXPECT_EQ(0, vec.size());

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[3], 4);

    vec.erase(vec.begin());
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[2], 4);
}

TYPED_TEST(VectorInterfacePodTest, ClearTest)
{
    TypeParam vec;
    EXPECT_EQ(0, vec.size());

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    EXPECT_EQ(vec.size(), 4);

    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}

TYPED_TEST(VectorInterfacePodTest, ResizeTest)
{
    TypeParam vec;
    EXPECT_EQ(0, vec.size());

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    EXPECT_EQ(vec.size(), 4);

    vec.resize(10);
    EXPECT_EQ(vec.size(), 10);
    EXPECT_EQ(vec[9], 0);

    vec.resize(2);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 2);
}

TYPED_TEST(VectorInterfacePodTest, ReserveTest)
{
    TypeParam vec;
    EXPECT_EQ(0, vec.size());

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    EXPECT_EQ(vec.size(), 4);

    vec.reserve(10);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_GE(vec.capacity(), 10);

    vec.reserve(100);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_GE(vec.capacity(), 100);
}


class ClassWithAllCtors
{
public:
    ClassWithAllCtors()
    {
        GetOStrStream() << "Default ctor\n";
    }

    explicit ClassWithAllCtors(int v) : value(v)
    {
        GetOStrStream() << "Ctor " << value << '\n';
    }

    ClassWithAllCtors(const ClassWithAllCtors& other)
        : value(other.value)
    {
        GetOStrStream() << "Copy ctor\n";
    }

    ClassWithAllCtors(ClassWithAllCtors&& other)
        : value(other.value)
    {
        GetOStrStream() << "Move ctor\n";
    }

    ClassWithAllCtors& operator=(const ClassWithAllCtors& other)
    {
        GetOStrStream() << "Copy assign operator\n";

        if (this == &other)
            return *this;
        value = other.value;
        return *this;
    }

    ClassWithAllCtors& operator=(ClassWithAllCtors&& other)
    {
        GetOStrStream() << "Move assign operator\n";

        if (this == &other)
            return *this;
        value = other.value;
        return *this;
    }

    ~ClassWithAllCtors()
    {
        GetOStrStream() << "Dtor\n";
    }

    int value = 0;

    static std::ostringstream& GetOStrStream()
    {
        static std::ostringstream ostr;
        return ostr;
    }
};

TEST(ClassWithAllCtorsTest, TestCtorsAndDtors)
{
    using CUT = ClassWithAllCtors;
    std::ostringstream& ostr = ClassWithAllCtors::GetOStrStream();
    ostr.str("");
    ASSERT_EQ(ostr.str(), "");

    {
        CUT v;
    }
    EXPECT_EQ(ostr.str(), "Default ctor\nDtor\n");

    ostr.str("");
    {
        CUT v(1);
    }
    EXPECT_EQ(ostr.str(), "Ctor 1\nDtor\n");

    ostr.str("");
    {
        CUT v;
        CUT v1(v);
    }
    EXPECT_EQ(ostr.str(), "Default ctor\nCopy ctor\nDtor\nDtor\n");

    ostr.str("");
    {
        CUT v;
        CUT v1(std::move(v));
    }
    EXPECT_EQ(ostr.str(), "Default ctor\nMove ctor\nDtor\nDtor\n");
}

template<typename T>
class VectorInterfaceComplexTest : public ::testing::Test {};

using ComplexTestTypes = ::testing::Types<std::vector<ClassWithAllCtors>, myvector<ClassWithAllCtors>>;
TYPED_TEST_CASE(VectorInterfaceComplexTest, ComplexTestTypes);

TYPED_TEST(VectorInterfaceComplexTest, EmptyVectTest)
{
}