#include "myvector.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>


struct StructUnderTest
{
	StructUnderTest()
	{
		std::cout << "Constructed " << this << '\n';
	}

	explicit StructUnderTest(size_t v) : value(v)
	{
		std::cout << "Constructed " << this << '\n';
	}


	StructUnderTest(const StructUnderTest& other)
		: value(other.value)
	{
		std::cout << "Copy from " << &other << " to " << this << '\n';
	}

	StructUnderTest& operator=(const StructUnderTest& other)
	{
		std::cout << "copy assign from " << &other << " to " << this << '\n';

		if (this == &other)
			return *this;
		value = other.value;
		return *this;
	}


	StructUnderTest(StructUnderTest&& other)
		: value(other.value)
	{
		std::cout << "Move from " << &other << " to " << this << '\n';
	}

	StructUnderTest& operator=(StructUnderTest&& other)
	{
		std::cout << "move assign from " << &other << " to " << this << '\n';

		if (this == &other)
			return *this;
		value = other.value;
		return *this;
	}

	~StructUnderTest()
	{
		std::cout << "Destroyed " << this << '\n';
	}

	size_t value = 0;
};

TEST_CASE( "My vector methods tests", "[myvector]")
{
	SECTION( "ctor POD" )
	{
		myvector<int> vec;
		REQUIRE( vec.size() == 0);
		REQUIRE( vec.capacity() == decltype(vec)::initial_capacity::value );
	}

	SECTION( "ctor non-POD" )
	{
		myvector<StructUnderTest> vec;
		REQUIRE( vec.size() == 0);
		REQUIRE( vec.capacity() == decltype(vec)::initial_capacity::value );
	}

	SECTION( "size and push_back POD" )
	{
		myvector<int> vec;
		REQUIRE( vec.size() == 0);

		vec.push_back(3);
		REQUIRE( vec.size() == 1);
		REQUIRE( vec[0] == 3);
	}

	SECTION( "size and push_back non-POD" )
	{
		myvector<StructUnderTest> vec;
		REQUIRE( vec.size() == 0);

		vec.push_back(StructUnderTest{3});
		REQUIRE( vec.size() == 1);
		REQUIRE( vec[0].value == 3);

		auto v = StructUnderTest{4};
		vec.push_back(v);
		REQUIRE( vec.size() == 2);
		REQUIRE( vec[1].value == 4);
	}

	SECTION( "empty reserve and capacity POD" )
	{
		myvector<int, 4> vec;
		REQUIRE( vec.size() == 0);
		REQUIRE( vec.capacity() == 4 );
		vec.reserve(20);
		REQUIRE( vec.size() == 0);
		REQUIRE( vec.capacity() >= 20 );
	}

	SECTION( "reserve with elements and capacity POD" )
	{
		myvector<int, 4> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		REQUIRE( vec.size() == 3);
		REQUIRE( vec[0] == 1);
		REQUIRE( vec[1] == 2);
		REQUIRE( vec[2] == 3);
		REQUIRE( vec.capacity() == 4 );
		vec.reserve(20);
		REQUIRE( vec.size() == 3);
		REQUIRE( vec[0] == 1);
		REQUIRE( vec[1] == 2);
		REQUIRE( vec[2] == 3);
		REQUIRE( vec.capacity() >= 20 );
	}

	SECTION( "reserve with elements and capacity non-POD" )
	{
		myvector<StructUnderTest, 4> vec;
		vec.push_back(StructUnderTest{1});
		vec.push_back(StructUnderTest{2});
		vec.push_back(StructUnderTest{3});
		REQUIRE( vec.size() == 3);
		REQUIRE( vec[0].value == 1);
		REQUIRE( vec[1].value == 2);
		REQUIRE( vec[2].value == 3);
		REQUIRE( vec.capacity() == 4 );
		vec.reserve(20);
		REQUIRE( vec.size() == 3);
		REQUIRE( vec[0].value == 1);
		REQUIRE( vec[1].value == 2);
		REQUIRE( vec[2].value == 3);
		REQUIRE( vec.capacity() >= 20 );
	}


	SECTION( "add(T)" )
	{
		
	}

	SECTION( "add()" )
	{
		
	}

	SECTION( "erase(int)" )
	{
		
	}


	SECTION( "erase(T*)" )
	{
		
	}

	SECTION( "[]" )
	{
		
	}

	SECTION( "[] const" )
	{
		
	}

	SECTION( "[] const" )
	{
		
	}

	SECTION( "begin" )
	{
		
	}

	SECTION( "end" )
	{
		
	}

	SECTION( "clear" )
	{
		
	}
	SECTION( "resize" )
	{
		
	}
	SECTION( "reserve" )
	{
		
	}
}
